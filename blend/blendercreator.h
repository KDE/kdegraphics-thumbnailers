/*
 * SPDX-FileCopyrightText: 2019 Chinmoy Ranjan Pradhan <chinmoyrp65@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#ifndef _BLENDCREATOR_H_
#define _BLENDCREATOR_H_

#include <KIO/ThumbCreator>

class BlenderCreator : public ThumbCreator
{
public:
    BlenderCreator();
    ~BlenderCreator() override;

    bool create(const QString &path, int width, int height, QImage &img) override;
};

#endif
