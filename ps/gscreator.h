/*  This file is part of the KDE libraries
    Copyright (C) 2000 Malte Starostik <malte@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
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
