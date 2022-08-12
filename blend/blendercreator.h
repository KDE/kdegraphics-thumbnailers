/*
 * SPDX-FileCopyrightText: 2019 Chinmoy Ranjan Pradhan <chinmoyrp65@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#ifndef _BLENDCREATOR_H_
#define _BLENDCREATOR_H_

#include <KIO/ThumbnailCreator>

class BlenderCreator : public KIO::ThumbnailCreator
{
public:
    BlenderCreator(QObject *parent, const QVariantList &args);
    ~BlenderCreator() override;

    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
};

#endif
