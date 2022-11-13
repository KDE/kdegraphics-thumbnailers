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

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(MobiThumbnail, "mobithumbnail.json")

MobiThumbnail::MobiThumbnail(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

KIO::ThumbnailResult MobiThumbnail::create(const KIO::ThumbnailRequest &request)
{
    Mobipocket::QFileStream f(request.url().toLocalFile());
    Mobipocket::Document doc(&f);
    if (!doc.isValid()) {
        return KIO::ThumbnailResult::fail();
    }
    QImage img = doc.thumbnail();
    return !img.isNull() ? KIO::ThumbnailResult::pass(img) : KIO::ThumbnailResult::fail();
}

#include "mobithumbnail.moc"
