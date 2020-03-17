cmake_minimum_required(VERSION 3.0)
project(kdegraphics-thumbnailers)

set(QT_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMOptionalAddSubdirectory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO)
find_package(KF5 REQUIRED COMPONENTS Archive)

add_definitions(-DQT_USE_QSTRINGBUILDER)


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


ecm_optional_add_subdirectory(ps)

if(KF5KExiv2_FOUND AND KF5KDcraw_FOUND)
ecm_optional_add_subdirectory(raw)
endif()

ecm_optional_add_subdirectory(blend)

install(FILES org.kde.kdegraphics-thumbnailers.metainfo.xml
        DESTINATION ${KDE_INSTALL_METAINFODIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
