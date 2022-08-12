/*
 *   SPDX-FileCopyrightText: 2008 Jakub Stachowski <qbast@go2.pl>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mobithumbnail.h"
#include <qmobipocket/mobipocket.h>

#include <QFile>

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(MobiThumbnail, "mobithumbnail.json")

MobiThumbnail::MobiThumbnail(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

KIO::ThumbnailResult MobiThumbnail::create(const KIO::ThumbnailRequest &request)
{
    QFile file(request.url().toLocalFile());
    if (file.open(QFile::ReadOnly)) {
        return KIO::ThumbnailResult::fail();
    }
    Mobipocket::Document doc(&file);
    if (!doc.isValid()) {
        return KIO::ThumbnailResult::fail();
    }
    QImage img = doc.thumbnail();
    return !img.isNull() ? KIO::ThumbnailResult::pass(img) : KIO::ThumbnailResult::fail();
}

#include "mobithumbnail.moc"
