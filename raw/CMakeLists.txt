project(rawthumbnail)

#sources
set(rawthumbnail_SRCS rawcreator.cpp)
add_library(rawthumbnail MODULE ${rawthumbnail_SRCS})


## includes and linking
target_link_libraries(rawthumbnail Qt5::Gui KF5::KIOWidgets KF5::Kdcraw KF5::Kexiv2)

## install the plugin
install(TARGETS rawthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES rawthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})


