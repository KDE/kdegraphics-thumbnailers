add_library(mobithumbnail MODULE)

target_sources(mobithumbnail PRIVATE mobithumbnail.cpp)

target_link_libraries(mobithumbnail KF5::KIOCore KF5::KIOWidgets Qt::Gui qmobipocket)
install(TARGETS mobithumbnail DESTINATION ${KDE_INSTALL_PLUGINDIR})

install( FILES mobithumbnail.desktop  DESTINATION  ${KDE_INSTALL_KSERVICESDIR} )
