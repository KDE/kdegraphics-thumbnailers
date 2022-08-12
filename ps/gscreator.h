/*  This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2000 Malte Starostik <malte@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef _GSCREATOR_H_
#define _GSCREATOR_H_

#include <KIO/ThumbnailCreator>
#include "dscparse_adapter.h"

class GSCreator : public KIO::ThumbnailCreator, public KDSCCommentHandler
{
public:
    GSCreator(QObject *parent, const QVariantList &args);
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
    void comment(Name name) override;

private:
    static KIO::ThumbnailResult getEPSIPreview(const QString &path,
                               long start, long end,
                               int imgwidth, int imgheight);
    bool endComments;
};

#endif
