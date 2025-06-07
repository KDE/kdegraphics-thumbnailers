kcoreaddons_add_plugin(mobithumbnail INSTALL_NAMESPACE "kf6/thumbcreator")

target_sources(mobithumbnail PRIVATE mobithumbnail.cpp)

target_link_libraries(mobithumbnail KF6::KIOCore KF6::KIOGui Qt::Gui)

target_link_libraries(mobithumbnail QMobipocket6)
