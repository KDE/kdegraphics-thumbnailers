cmake_minimum_required(VERSION 3.16)
project(kdegraphics-thumbnailers)

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.90.0")
set(KDE_COMPILERSETTINGS_LEVEL "5.82")
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMOptionalAddSubdirectory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS KIO)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Archive)
add_definitions(-DQT_USE_QSTRINGBUILDER)

option(DISABLE_MOBIPOCKET "Disable the mobipocket thumbnailer." OFF)

find_package(KF5KExiv2)
set_package_properties("KF5KExiv2"    PROPERTIES
                       DESCRIPTION "A library for reading and writing image metadata"
                       URL         "www.kde.org"
                       TYPE        OPTIONAL
                       PURPOSE     "Required to build the RAW thumbnailer"
)

find_package(KF5KDcraw)
set_package_properties("KF5KDcraw"    PROPERTIES
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

find_package(QMobipocket)
set_package_properties("QMobipocket"    PROPERTIES
                       DESCRIPTION "A library for accessing mobipocket files"
                       URL         "www.kde.org"
                       TYPE        ${MOBIPOCKET_REQUIRED_TYPE}
                       PURPOSE     "Required to build the mobipocket thumbnailer. ${DISABLE_MOBIPOCKET_TEXT}"
)


ecm_optional_add_subdirectory(ps)

if(KF5KExiv2_FOUND AND KF5KDcraw_FOUND)
ecm_optional_add_subdirectory(raw)
endif()

ecm_optional_add_subdirectory(blend)

if(QMobipocket_FOUND)
ecm_optional_add_subdirectory(mobipocket)
endif()

install(FILES org.kde.kdegraphics-thumbnailers.metainfo.xml
        DESTINATION ${KDE_INSTALL_METAINFODIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
