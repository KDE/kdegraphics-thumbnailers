add_library(blenderthumbnail MODULE)

#sources
target_sources(blenderthumbnail PRIVATE
    blendercreator.cpp
)

kcoreaddons_desktop_to_json(blenderthumbnail blenderthumbnail.desktop)

## includes and linking
target_link_libraries(blenderthumbnail
    KF5::KIOGui
    KF5::Archive
    Qt::Core
)

## install the plugin
install(TARGETS blenderthumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES blenderthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICESDIR})
