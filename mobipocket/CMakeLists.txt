kcoreaddons_add_plugin(mobithumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(mobithumbnail PRIVATE mobithumbnail.cpp)

target_link_libraries(mobithumbnail KF5::KIOCore KF5::KIOWidgets Qt::Gui qmobipocket)
