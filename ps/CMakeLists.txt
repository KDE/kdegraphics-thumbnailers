add_library(gsthumbnail MODULE)

target_sources(gsthumbnail PRIVATE
    gscreator.cpp
    dscparse.cpp
    dscparse_adapter.cpp
)

kcoreaddons_desktop_to_json(gsthumbnail gsthumbnail.desktop)

target_link_libraries(gsthumbnail
    KF5::KIOGui
    Qt::Gui
)

install(TARGETS gsthumbnail  DESTINATION ${KDE_INSTALL_PLUGINDIR} )
install(FILES gsthumbnail.desktop  DESTINATION  ${KDE_INSTALL_KSERVICESDIR})

