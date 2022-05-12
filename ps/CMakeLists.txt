add_library(gsthumbnail MODULE)

target_sources(gsthumbnail PRIVATE
    gscreator.cpp
    dscparse.cpp
    dscparse_adapter.cpp
)

target_link_libraries(gsthumbnail
    KF5::KIOWidgets
    Qt::Gui
)

install(TARGETS gsthumbnail  DESTINATION ${KDE_INSTALL_PLUGINDIR} )
install(FILES gsthumbnail.desktop  DESTINATION  ${KDE_INSTALL_KSERVICESDIR})

