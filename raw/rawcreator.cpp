/**
 SPDX-FileCopyrightText: 2008 Unai Garro <ugarro@gmail.com>

 SPDX-License-Identifier: GPL-2.0-or-later
**/

#include "rawcreator.h"

#include <QImage>

#include <kdcraw/kdcraw.h>
#include <kexiv2/kexiv2.h>

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new RAWCreator;
    }
}

RAWCreator::RAWCreator()
{
}

RAWCreator::~RAWCreator()
{
}

bool RAWCreator::create(const QString &path, int width, int height, QImage &img)
{
    //load the image into the QByteArray
    QByteArray data;
    bool loaded=KDcrawIface::KDcraw::loadEmbeddedPreview(data,path);

    if (loaded)
    {

        //Load the image into a QImage
        QImage preview;
        if (!preview.loadFromData(data) || preview.isNull())
           return false;

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
        img=preview.scaled(width,height,Qt::KeepAspectRatio);

    }
    return loaded;
}

ThumbCreator::Flags RAWCreator::flags() const
{
    return (Flags)(0);
}
