/*  This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2000 Malte Starostik <malte@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef _GSCREATOR_H_
#define _GSCREATOR_H_

#include <KIO/ThumbCreator>
#include "dscparse_adapter.h"

class GSCreator : public ThumbCreator, public KDSCCommentHandler
{
public:
    GSCreator() {}
    bool create(const QString &path, int, int, QImage &img) override;
    Flags flags() const override;
    void comment(Name name) override;

private:
    static bool getEPSIPreview(const QString &path,
                               long start, long end,
                               QImage &outimg,
                               int imgwidth, int imgheight);
    bool endComments;
};

#endif
