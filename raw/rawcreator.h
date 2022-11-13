/**
 Copyright (C) 2008  Unai Garro <ugarro@gmail.com>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
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
