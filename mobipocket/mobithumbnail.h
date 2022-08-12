/*
 *   SPDX-FileCopyrightText: 2008 Jakub Stachowski <qbast@go2.pl>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MOBITHUMBNAIL_H
#define MOBITHUMBNAIL_H

#include <kio/thumbcreator.h>

class MobiThumbnail : public ThumbCreator
{
public:
    MobiThumbnail() {}
    bool create(const QString &path, int, int, QImage &img) override;
    Flags flags() const override;
};

#endif
