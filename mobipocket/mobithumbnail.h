/*
 *   SPDX-FileCopyrightText: 2008 Jakub Stachowski <qbast@go2.pl>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MOBITHUMBNAIL_H
#define MOBITHUMBNAIL_H

#include <KIO/ThumbnailCreator>

class MobiThumbnail : public KIO::ThumbnailCreator
{
public:
    MobiThumbnail(QObject *parent, const QVariantList &args);
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
};

#endif
