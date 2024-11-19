cmake_minimum_required(VERSION 3.16)
project(kdegraphics-thumbnailers)

set(QT_MIN_VERSION "5.15.2")
set(KF_MIN_VERSION "5.92.0")
set(KDE_COMPILERSETTINGS_LEVEL "5.82")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMOptionalAddSubdirectory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(ECMDeprecationSettings)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF${QT_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS KIO)
add_definitions(-DQT_USE_QSTRINGBUILDER)

option(DISABLE_BLENDER "Disable the blender thumbnailer." OFF)
option(DISABLE_MOBIPOCKET "Disable the mobipocket thumbnailer." OFF)

if(QT_MAJOR_VERSION STREQUAL "6")
    set(KExiv2PackageName KExiv2Qt6)
else()
    set(KExiv2PackageName KF5KExiv2)
endif()
find_package(${KExiv2PackageName})
set_package_properties(${KExiv2PackageName}    PROPERTIES
                       DESCRIPTION "A library for reading and writing image metadata"
                       URL         "www.kde.org"
                       TYPE        OPTIONAL
                       PURPOSE     "Required to build the RAW thumbnailer"
)

if(QT_MAJOR_VERSION STREQUAL "6")
    set(KDcrawPackageName KDcrawQt6)
else()
    set(KDcrawPackageName KF5KDcraw)
endif()
find_package(${KDcrawPackageName})
set_package_properties(${KDcrawPackageName}    PROPERTIES
                       DESCRIPTION "A library for accessing raw files"
                       URL         "www.kde.org"
                       TYPE        OPTIONAL
                       PURPOSE     "Required to build the RAW thumbnailer"
)

if (DISABLE_MOBIPOCKET)
    set(MOBIPOCKET_REQUIRED_TYPE "OPTIONAL")
    set(DISABLE_MOBIPOCKET_TEXT "")
else()
    set(MOBIPOCKET_REQUIRED_TYPE "REQUIRED")
    set(DISABLE_MOBIPOCKET_TEXT "Disable with DISABLE_MOBIPOCKET")
endif()

if(QT_MAJOR_VERSION STREQUAL "6")
    find_package(QMobipocket6)
    set_package_properties("QMobipocket6"    PROPERTIES
                        DESCRIPTION "A library for accessing mobipocket files"
                        URL         "www.kde.org"
                        TYPE        ${MOBIPOCKET_REQUIRED_TYPE}
                        PURPOSE     "Required to build the mobipocket thumbnailer. ${DISABLE_MOBIPOCKET_TEXT}"
    )
else()
    find_package(QMobipocket)
    set_package_properties("QMobipocket"    PROPERTIES
                        DESCRIPTION "A library for accessing mobipocket files"
                        URL         "www.kde.org"
                        TYPE        ${MOBIPOCKET_REQUIRED_TYPE}
                        PURPOSE     "Required to build the mobipocket thumbnailer. ${DISABLE_MOBIPOCKET_TEXT}"
    )
endif()


ecm_set_disabled_deprecation_versions(QT 5.15.2 KF 5.100.0
    )

ecm_optional_add_subdirectory(ps)

if(${KExiv2PackageName}_FOUND AND ${KDcrawPackageName}_FOUND)
ecm_optional_add_subdirectory(raw)
endif()

if (NOT DISABLE_BLENDER)
    find_package(KF${QT_MAJOR_VERSION}Archive ${KF_MIN_VERSION} REQUIRED)
    ecm_optional_add_subdirectory(blend)
endif()

if(QMobipocket6_FOUND OR QMobipocket_FOUND)
ecm_optional_add_subdirectory(mobipocket)
endif()

install(FILES org.kde.kdegraphics-thumbnailers.metainfo.xml
        DESTINATION ${KDE_INSTALL_METAINFODIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
