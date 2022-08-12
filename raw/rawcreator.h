/**
 SPDX-FileCopyrightText: 2008 Unai Garro <ugarro@gmail.com>

 SPDX-License-Identifier: GPL-2.0-or-later
**/

#ifndef RAWCREATOR_H
#define RAWCREATOR_H

#include <KIO/ThumbnailCreator>

class RAWCreator : public KIO::ThumbnailCreator
{
public:
    RAWCreator(QObject *parent, const QVariantList &args);
    ~RAWCreator() override;
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
};

#endif
