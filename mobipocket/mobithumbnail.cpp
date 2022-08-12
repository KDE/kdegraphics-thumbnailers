/***************************************************************************
 *   Copyright (C) 2008 by Jakub Stachowski <qbast@go2.pl>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "mobithumbnail.h"
#include <qmobipocket/mobipocket.h>
#include <qmobipocket/qfilestream.h>

#include <QFile>

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new MobiThumbnail;
    }
}

class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "KIOPluginForMetaData" FILE "mobithumbnail.json")
};


bool MobiThumbnail::create(const QString &path, int width, int height, QImage &img)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
    
    Mobipocket::QFileStream f(path);
    Mobipocket::Document doc(&f);
    if (!doc.isValid()) return false;
    img=doc.thumbnail();
    return !img.isNull();
}

ThumbCreator::Flags MobiThumbnail::flags() const
{
    return static_cast<Flags>(None);
}

#include "mobithumbnail.moc"
