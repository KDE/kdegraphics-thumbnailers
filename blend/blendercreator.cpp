/*
 * Copyright (c) 2019 Chinmoy Ranjan Pradhan <chinmoyrp65@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "blendercreator.h"

#include <QFile>
#include <QImage>
#include <QPointer>
#include <QtEndian>
#include <KCompressionDevice>

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new BlenderCreator;
    }
}

class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "KIOPluginForMetaData" FILE "blenderthumbnail.json")
};


BlenderCreator::BlenderCreator() = default;

BlenderCreator::~BlenderCreator() = default;

// For more info. see https://developer.blender.org/diffusion/B/browse/master/release/bin/blender-thumbnailer.py

bool BlenderCreator::create(const QString &path, int width , int height, QImage &img)
{
    QFile file (path);
    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream blendStream;
    blendStream.setDevice(&file);
    // Blender has an option to save files with gzip compression. First check if we are dealing with such files.
    QPointer<KCompressionDevice> gzFile;
    if(file.peek(2).startsWith("\x1F\x8B")) { // gzip magic (each gzip member starts with ID1(0x1f) and ID2(0x8b))
        file.close();
        gzFile = new KCompressionDevice(path, KCompressionDevice::GZip);
        if (gzFile->open(QIODevice::ReadOnly)) {
            blendStream.setDevice(gzFile);
        } else {
            return false;
        }
    }

    // First to check is file header.
    // BLEND file header format
    // Reference      Content                                     Size
    // id             "BLENDER"                                    7
    // pointer-size   _ (underscore)(32 bit)/ - (minus)(64 bit)    1
    // endianness     v (little) / V (big)                         1
    // version        "248" = 2.48 etc.                            3

    // Example header: "BLENDER-v257"

    QByteArray head(12, '\0');
    blendStream.readRawData(head.data(), 12);
    if(!head.startsWith("BLENDER") || head.right(3).toInt() < 250 /*blender pre 2.5 had no thumbs*/) {
        blendStream.device()->close();
        return false;
    }

    // Next is file block. This we have to skip.
    // File block header format
    //    Reference      Content                                               Size
    // 1. id             "REND","TEST", etc.                                    4
    // 2. size           Total length of the data after the file-block-header   4
    // 3. old mem. addr  Mem. address.                                          pointer-size i.e, 4(32bit)/8(64bit)
    // 4. SDNA index     Index of SDNA struct                                   4
    // 5. count          No. of struct in file-block                            4

    const bool isLittleEndian = head[8] == 'v';
    auto toInt32 = [isLittleEndian](const QByteArray &bytes) {
        return isLittleEndian ? qFromLittleEndian<qint32>(bytes.constData())
                              : qFromBigEndian<qint32>(bytes.constData());
    };

    const bool is64Bit = head[7] == '-';
    const int fileBlockHeaderSize = is64Bit ? 24 : 20; // size of file block header fields 1 to 5
    QByteArray fileBlockHeader(fileBlockHeaderSize, '\0');
    qint32 fileBlockSize = 0;
    while (true) {
        const int read = blendStream.readRawData(fileBlockHeader.data(), fileBlockHeaderSize);
        if (read != fileBlockHeaderSize) {
            return false;
        }
        fileBlockSize = toInt32(fileBlockHeader.mid(4, 4)); // second header field
        // skip actual file-block data.
        if (fileBlockHeader.startsWith("REND")) {
            blendStream.skipRawData(fileBlockSize);
        } else {
            break;
        }
    }

    if(!fileBlockHeader.startsWith("TEST")) {
        blendStream.device()->close();
        return false;
    }

    // Now comes actual thumbnail image data.
    QByteArray xy(8, '\0');
    blendStream.readRawData(xy.data(), 8);
    const qint32 x = toInt32(xy.left(4));
    const qint32 y = toInt32(xy.right(4));

    qint32 imgSize = fileBlockSize - 8;
    if (imgSize != x * y * 4) {
        blendStream.device()->close();
        return false;
    }

    QByteArray imgBuffer(imgSize, '\0');
    blendStream.readRawData(imgBuffer.data(), imgSize);
    QImage thumbnail((const uchar*)imgBuffer.constData(), x, y, QImage::Format_ARGB32);
    if(width != 128) {
        thumbnail = thumbnail.scaledToWidth(width, Qt::SmoothTransformation);
    }
    if(height != 128) {
        thumbnail = thumbnail.scaledToHeight(height, Qt::SmoothTransformation);
    }
    thumbnail = thumbnail.rgbSwapped();
    thumbnail = thumbnail.mirrored();
    img = thumbnail.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    blendStream.device()->close();
    return true;
}

#include "blendercreator.moc"
