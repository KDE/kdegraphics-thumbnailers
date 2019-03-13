project(blenderthumbnail)

#sources
set(blenderthumbnail_SRCS blendercreator.cpp)
add_library(blenderthumbnail MODULE ${blenderthumbnail_SRCS})

## includes and linking
target_link_libraries(blenderthumbnail Qt5::Core KF5::KIOWidgets KF5::Archive)

## install the plugin
install(TARGETS blenderthumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES blenderthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
