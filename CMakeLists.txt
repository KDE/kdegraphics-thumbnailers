find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

include_directories(${KSANE_INCLUDE_DIR})
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

#TODO find exiv2 and lcms

macro_optional_add_subdirectory(ps)
#add_subdirectory(mobi)

if(EXIV2_FOUND AND LCMS_FOUND)
macro_optional_add_subdirectory(raw)
endif(EXIV2_FOUND AND LCMS_FOUND)
