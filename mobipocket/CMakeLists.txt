add_library(mobithumbnail MODULE)

target_sources(mobithumbnail PRIVATE mobithumbnail.cpp)

kcoreaddons_desktop_to_json(mobithumbnail mobithumbnail.desktop)

target_link_libraries(mobithumbnail KF5::KIOCore KF5::KIOGui Qt::Gui qmobipocket)
install(TARGETS mobithumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})

install( FILES mobithumbnail.desktop  DESTINATION  ${KDE_INSTALL_KSERVICESDIR} )
