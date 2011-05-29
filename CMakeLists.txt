find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

include_directories(${KSANE_INCLUDE_DIR})
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})


macro_optional_find_package(Kexiv2)
macro_optional_find_package(Kdcraw)
macro_optional_find_package(LCMS)
macro_optional_add_subdirectory(ps)

macro_log_feature(KEXIV2_FOUND "libkexiv2" "A library for reading and writing image metadata" "www.kde.org" FALSE "" "Required to build the RAW thumbnailer")
macro_log_feature(KDCRAW_FOUND "libkdcraw" "A library for accessing raw files" "www.kde.org" FALSE "" "Required to build the RAW thumbnailer")
macro_log_feature(LCMS_FOUND "lcms" "A library for color management" "www.littlecms.org" FALSE "" "Required to build the RAW thumbnailer")
macro_display_feature_log()

if(KEXIV2_FOUND AND KDCRAW_FOUND AND LCMS_FOUND)
macro_optional_add_subdirectory(raw)
endif()
