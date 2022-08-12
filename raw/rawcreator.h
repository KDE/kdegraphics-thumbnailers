/**
 SPDX-FileCopyrightText: 2008 Unai Garro <ugarro@gmail.com>

 SPDX-License-Identifier: GPL-2.0-or-later
**/

#ifndef RAWCREATOR_H
#define RAWCREATOR_H

#include <KIO/ThumbCreator>

class RAWCreator : public ThumbCreator
{
public:
    RAWCreator();
    ~RAWCreator() override;
    bool create(const QString &path, int width, int height, QImage &img) override;
    Flags flags() const override;
};

#endif
