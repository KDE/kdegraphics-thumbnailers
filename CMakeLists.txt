find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

include_directories(${KSANE_INCLUDE_DIR})
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})


macro_optional_find_package(Kexiv2)
macro_optional_find_package(Kdcraw)
macro_optional_add_subdirectory(ps)

macro_log_feature(KEXIV2_FOUND "libkexiv2" "Required to build the RAW thumbnailer" "www.kde.org" FALSE "" "")
macro_log_feature(KDCRAW_FOUND "libkdcraw" "Required to build the RAW thumbnailer" "www.kde.org" FALSE "" "")
macro_display_feature_log()

if(KEXIV2_FOUND AND KDCRAW_FOUND)
macro_optional_add_subdirectory(raw)
endif()
