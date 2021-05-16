add_library(blenderthumbnail MODULE)

#sources
target_sources(blenderthumbnail PRIVATE
    blendercreator.cpp
)

## includes and linking
target_link_libraries(blenderthumbnail
    KF5::KIOWidgets
    KF5::Archive
    Qt5::Core
)

## install the plugin
install(TARGETS blenderthumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES blenderthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
