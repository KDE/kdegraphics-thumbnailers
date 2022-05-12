add_library(rawthumbnail MODULE)

#sources
target_sources(rawthumbnail PRIVATE
    rawcreator.cpp
)

## includes and linking
target_link_libraries(rawthumbnail
    KF5::KIOWidgets
    KF5::KDcraw
    KF5::KExiv2
    Qt::Gui
)

## install the plugin
install(TARGETS rawthumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES rawthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICESDIR})


