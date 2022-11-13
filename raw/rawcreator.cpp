/**
 Copyright (C) 2008  Unai Garro <ugarro@gmail.com>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
**/

#include "rawcreator.h"

#include <QImage>

#include <kdcraw/kdcraw.h>
#include <kexiv2/kexiv2.h>

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(RAWCreator, "rawthumbnail.json")

RAWCreator::RAWCreator(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

RAWCreator::~RAWCreator()
{
}

KIO::ThumbnailResult RAWCreator::create(const KIO::ThumbnailRequest &request)
{
    //load the image into the QByteArray
    QByteArray data;
    bool loaded=KDcrawIface::KDcraw::loadEmbeddedPreview(data,request.url().toLocalFile());

    if (!loaded) {
        return KIO::ThumbnailResult::fail();
    }
    //Load the image into a QImage
    QImage preview;
    if (!preview.loadFromData(data) || preview.isNull())
        return KIO::ThumbnailResult::fail();

    //And its EXIF info
    KExiv2Iface::KExiv2 exiv;
    if (exiv.loadFromData(data))
    {
        //We managed reading the EXIF info, rotate the image
        //according to the EXIF orientation flag
        KExiv2Iface::KExiv2::ImageOrientation orient=exiv.getImageOrientation();

        //Rotate according to the EXIF orientation flag
        switch(orient)
        {
            case KExiv2Iface::KExiv2::ORIENTATION_UNSPECIFIED:
            case KExiv2Iface::KExiv2::ORIENTATION_NORMAL:
                break; //we do nothing
            case KExiv2Iface::KExiv2::ORIENTATION_HFLIP:
                preview = preview.mirrored(true,false);
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_ROT_180:
                preview = preview.transformed(QTransform().rotate(180));
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_VFLIP:
                preview = preview.mirrored(false,true);
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_ROT_90_HFLIP:
                preview = preview.mirrored(true,false);
                preview = preview.transformed(QTransform().rotate(90));
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_ROT_90:
                preview = preview.transformed(QTransform().rotate(90));
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_ROT_90_VFLIP:
                preview = preview.mirrored(false,true);
                preview = preview.transformed(QTransform().rotate(90));
                break;
            case KExiv2Iface::KExiv2::ORIENTATION_ROT_270:
                preview = preview.transformed(QTransform().rotate(270));
                break;
            default:
                break;
        }
    }

    //Scale the image as requested by the thumbnailer
    QImage img=preview.scaled(request.targetSize(),Qt::KeepAspectRatio);

    return KIO::ThumbnailResult::pass(img);
}

#include "rawcreator.moc"
