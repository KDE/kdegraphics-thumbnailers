project(kdegraphics-thumbnailers)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
include_directories(${KDE4_INCLUDES})

macro_optional_find_package(Kexiv2)
macro_optional_find_package(Kdcraw)

macro_log_feature(KEXIV2_FOUND "libkexiv2" "A library for reading and writing image metadata" "www.kde.org" FALSE "" "Required to build the RAW thumbnailer")
macro_log_feature(KDCRAW_FOUND "libkdcraw" "A library for accessing raw files" "www.kde.org" FALSE "" "Required to build the RAW thumbnailer")

macro_optional_add_subdirectory(ps)

if(KEXIV2_FOUND AND KDCRAW_FOUND)
macro_optional_add_subdirectory(raw)
endif()

macro_display_feature_log()
