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

#include <libkdcraw/kdcraw.h>
#include <libkexiv2/kexiv2.h>

extern "C"
{
    KDE_EXPORT ThumbCreator *new_creator()
    {
        return new RAWCreator;
    }
}

RAWCreator::RAWCreator()
{
    m_dcr=new KDcrawIface::KDcraw();
    m_exiv=new KExiv2Iface::KExiv2();
    m_preview=new QImage();
    m_data=new QByteArray();
    m_matrix=new QMatrix();
}

RAWCreator::~RAWCreator()
{
    delete m_matrix;
    delete m_data;
    delete m_preview;
    delete m_exiv;
    delete m_dcr;
}

bool RAWCreator::create(const QString &path, int width, int height, QImage &img)
{
    //reset and load the image into the QByteArray
    m_data->clear();  
    bool loaded=m_dcr->loadEmbeddedPreview(*m_data,path);

    if (loaded)
    {

        //Load the image into a QImage
        m_preview->loadFromData(*m_data);
        if (m_preview->isNull()) 
           return false;

        //And its EXIF info
        if (m_exiv->load(*m_data))
        {
            //We managed reading the EXIF info, rotate the image
            //according to the EXIF orientation flag
            KExiv2Iface::KExiv2::ImageOrientation orient=m_exiv->getImageOrientation();
            m_matrix->reset();

            //Rotate according to the EXIF orientation flag
            switch(orient)
            {
                case KExiv2Iface::KExiv2::ORIENTATION_UNSPECIFIED:
                case KExiv2Iface::KExiv2::ORIENTATION_NORMAL:
                    break; //we do nothing
                case KExiv2Iface::KExiv2::ORIENTATION_HFLIP:
                    *m_preview = m_preview->mirrored(true,false);
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_ROT_180:
                    *m_preview = m_preview->transformed(m_matrix->rotate(180));
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_VFLIP:
                    *m_preview = m_preview->mirrored(false,true);
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_ROT_90_HFLIP:
                    *m_preview = m_preview->mirrored(true,false);
                    *m_preview = m_preview->transformed(m_matrix->rotate(90));
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_ROT_90:
                    *m_preview = m_preview->transformed(m_matrix->rotate(90));
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_ROT_90_VFLIP:
                    *m_preview = m_preview->mirrored(false,true);
                    *m_preview = m_preview->transformed(m_matrix->rotate(90));
                    break;
                case KExiv2Iface::KExiv2::ORIENTATION_ROT_270:
                    *m_preview = m_preview->transformed(m_matrix->rotate(270));
                    break;
                default:
                    break;
            }
        }

        //Scale the image as requested by the thumbnailer
        img=m_preview->scaled(width,height,Qt::KeepAspectRatio);

    }
    return loaded;
}


ThumbCreator::Flags RAWCreator::flags() const
{
    return (Flags)(0);
}

#include "rawcreator.moc"
