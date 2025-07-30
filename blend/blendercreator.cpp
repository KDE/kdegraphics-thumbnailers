/*
 * SPDX-FileCopyrightText: 2019 Chinmoy Ranjan Pradhan <chinmoyrp65@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "blendercreator.h"

#include <QFile>
#include <QImage>
#include <QPointer>
#include <QtEndian>

#include <KCompressionDevice>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(BlenderCreator, "blenderthumbnail.json")

BlenderCreator::BlenderCreator(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

BlenderCreator::~BlenderCreator() = default;

// For more info. see https://developer.blender.org/diffusion/B/browse/master/release/bin/blender-thumbnailer.py

KIO::ThumbnailResult BlenderCreator::create(const KIO::ThumbnailRequest &request)
{
    std::unique_ptr<QIODevice> device = std::make_unique<QFile>(request.url().toLocalFile());
    if(!device->open(QIODevice::ReadOnly)) {
        return KIO::ThumbnailResult::fail();
    }

    // Blender has an option to save files with zstd or gzip compression. First check if we are dealing with such files.
    QByteArray header = device->peek(4);
    if (header.size() == 4) {
        const uint8_t *h = reinterpret_cast<const uint8_t *>(header.constData());
        uint32_t magic = h[0] | (h[1] << 8) | (h[2] << 16) | (h[3] << 24);
        // A zstd archive may start with a regular or skippable frame
        // - 0xFD2FB528 is the magic number for zstd regular frame
        // - 0x184D2A5 is used to detect skippable frames by checking the top 28 bits (ignoring the lower 4 bits)
        //   skippable frame magic values are in the range 0x184D2A50..0x184D2A5F, so shifting right by 4 masks them all
        //   see:
        // - https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md#zstandard-frames
        // - https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md#skippable-frames
        if (magic == 0xFD2FB528 || (magic >> 4) == 0x184D2A5) {
            device = std::make_unique<KCompressionDevice>(std::move(device), KCompressionDevice::Zstd);
            if (!device->open(QIODevice::ReadOnly)) {
                return KIO::ThumbnailResult::fail();
            }
        }
        // In earlier versions of Blender, files were compressed using gzip.
        else if (header.startsWith("\x1F\x8B")) { // gzip magic (each gzip member starts with ID1(0x1f) and ID2(0x8b))
            device = std::make_unique<KCompressionDevice>(std::move(device), KCompressionDevice::GZip);
            if (!device->open(QIODevice::ReadOnly)) {
                return KIO::ThumbnailResult::fail();
            }
        }
    }

    QDataStream blendStream;
    blendStream.setDevice(device.get());

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
        return KIO::ThumbnailResult::fail();
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
            return KIO::ThumbnailResult::fail();
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
        return KIO::ThumbnailResult::fail();
    }

    // Now comes actual thumbnail image data.
    QByteArray xy(8, '\0');
    blendStream.readRawData(xy.data(), 8);
    const qint32 x = toInt32(xy.left(4));
    const qint32 y = toInt32(xy.right(4));

    qint32 imgSize = fileBlockSize - 8;
    if (imgSize != x * y * 4) {
        return KIO::ThumbnailResult::fail();
    }

    QByteArray imgBuffer(imgSize, '\0');
    blendStream.readRawData(imgBuffer.data(), imgSize);
    QImage thumbnail((const uchar*)imgBuffer.constData(), x, y, QImage::Format_ARGB32);
    if(request.targetSize().width() != 128) {
        thumbnail = thumbnail.scaledToWidth(request.targetSize().width(), Qt::SmoothTransformation);
    }
    if(request.targetSize().height() != 128) {
        thumbnail = thumbnail.scaledToHeight(request.targetSize().height(), Qt::SmoothTransformation);
    }
    thumbnail = thumbnail.rgbSwapped();
    thumbnail = thumbnail.mirrored();
    QImage img = thumbnail.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    return !img.isNull() ? KIO::ThumbnailResult::pass(img) : KIO::ThumbnailResult::fail();
}

#include "blendercreator.moc"
