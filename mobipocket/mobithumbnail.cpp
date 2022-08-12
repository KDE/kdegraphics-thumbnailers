/*
 *   SPDX-FileCopyrightText: 2008 Jakub Stachowski <qbast@go2.pl>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mobithumbnail.h"
#include <qmobipocket/mobipocket.h>
#include <qmobipocket/qfilestream.h>

#include <QFile>

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new MobiThumbnail;
    }
}

bool MobiThumbnail::create(const QString &path, int width, int height, QImage &img)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
    
    Mobipocket::QFileStream f(path);
    Mobipocket::Document doc(&f);
    if (!doc.isValid()) return false;
    img=doc.thumbnail();
    return !img.isNull();
}

ThumbCreator::Flags MobiThumbnail::flags() const
{
    return static_cast<Flags>(None);
}

