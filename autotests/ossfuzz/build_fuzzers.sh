#!/bin/bash -eu
#
# SPDX-FileCopyrightText: 2025 Azhar Momin <azhar.momin@kdemail.net>
# SPDX-License-Identifier: LGPL-2.0-or-later
#
# This script must be run after kio-extras/thumbnail/autotests/ossfuzz/build_fuzzers.sh

export PATH="$WORK/bin:$WORK/libexec:$PATH"
export PKG_CONFIG="$(which pkg-config) --static"
export PKG_CONFIG_PATH="$WORK/lib/pkgconfig:$WORK/share/pkgconfig:$WORK/lib/x86_64-linux-gnu/pkgconfig"
if [[ $FUZZING_ENGINE == "afl" ]]; then
    export LDFLAGS="-fuse-ld=lld"
fi

# For MobiThumbnail
cd $SRC/kdegraphics-mobipocket
sed -i '/add_subdirectory(tools)/d' CMakeLists.txt
cmake . -G Ninja \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTING=OFF \
  -DCMAKE_INSTALL_PREFIX=$WORK
ninja install -j$(nproc)

# For GSCreator

CFLAGS_SAVE="$CFLAGS"
CXXFLAGS_SAVE="$CXXFLAGS"
PKG_CONFIG_PATH_SAVE="$PKG_CONFIG_PATH"

export CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -Wno-error=implicit-function-declaration -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
export CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -Wno-error=implicit-function-declaration -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION $CXXFLAGS_EXTRA"
unset PKG_CONFIG_PATH

# Build gs binary
cd $SRC/ghostpdl
./autogen.sh
make -j$(nproc)
cp bin/gs $OUT

# Build dvips binary
cd $SRC/texlive-source/texk/kpathsea
./configure --disable-shared --enable-static
make -j$(nproc)

cd $SRC/texlive-source/texk/dvipsk
./configure --disable-shared --enable-static
make -j$(nproc)
cp dvips $OUT

export CFLAGS="$CFLAGS_SAVE"
export CXXFLAGS="$CXXFLAGS_SAVE"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH_SAVE"

# For RAWCreator
cd $SRC/LibRaw
CFLAGS_SAVE=$CFLAGS
CXXFLAGS_SAVE=$CXXFLAGS
CFLAGS="$CFLAGS -fno-sanitize=function,vptr"
CXXFLAGS="$CXXFLAGS -fno-sanitize=function,vptr"
autoreconf --install
./configure --disable-examples --disable-shared --enable-static
make -j$(nproc)
make install -j$(nproc)
CFLAGS=$CFLAGS_SAVE
CXXFLAGS=$CXXFLAGS_SAVE

cd $SRC/libkdcraw
cmake . -G Ninja \
    -DCMAKE_INSTALL_PREFIX=$WORK \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DQT_MAJOR_VERSION=6
ninja install -j$(nproc)
# This is later required for building kdegraphics-thumbnailers
# Ideally we should be passing CMAKE_MODULE_PATH but for some reason that doesn't work
cp cmake/modules/FindLibRaw.cmake $WORK/share/ECM/find-modules/

cd $SRC/kdegraphics-thumbnailers
cmake -B build -G Ninja \
    -DCMAKE_PREFIX_PATH=$WORK \
    -DCMAKE_INSTALL_PREFIX=$WORK \
    -DBUILD_FUZZERS=ON \
    -DFUZZERS_USE_QT_MINIMAL_INTEGRATION_PLUGIN=ON \
    -DBUILD_SHARED_LIBS=OFF
ninja -C build -j$(nproc)

EXTENSIONS="blenderthumbnail_fuzzer blend
            mobithumbnail_fuzzer mobi
            gsthumbnail_fuzzer dvi ps pdf eps
            rawthumbnail_fuzzer cr2 cr3 nef nrw arw srf orf rw2 raf dng pef srw kdc erf"

echo "$EXTENSIONS" | while read fuzzer_name extensions; do
    # copy the fuzzer binary
    cp build/bin/fuzzers/$fuzzer_name $OUT

    # create seed corpus
    for extension in $extensions; do
        find . -name "*.$extension" -exec zip -q "$OUT/${fuzzer_name}_seed_corpus.zip" {} +
    done
done
