#!/bin/bash -eu
#
# SPDX-FileCopyrightText: 2025 Azhar Momin <azhar.momin@kdemail.net>
# SPDX-License-Identifier: LGPL-2.0-or-later

# For MobiCreator
git clone --depth 1 https://invent.kde.org/graphics/kdegraphics-mobipocket.git
# For GSCreator
git clone --depth 1 https://github.com/ArtifexSoftware/ghostpdl.git
git clone --depth 1 https://github.com/TeX-Live/texlive-source.git
# For RAWCreator
git clone --depth 1 https://github.com/LibRaw/LibRaw.git
git clone --depth 1 https://invent.kde.org/graphics/libkdcraw.git
