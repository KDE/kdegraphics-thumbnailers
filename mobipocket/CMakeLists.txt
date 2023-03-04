kcoreaddons_add_plugin(mobithumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(mobithumbnail PRIVATE mobithumbnail.cpp)

target_link_libraries(mobithumbnail KF${QT_MAJOR_VERSION}::KIOCore KF${QT_MAJOR_VERSION}::KIOGui Qt::Gui)

if (QT_MAJOR_VERSION STREQUAL "5")
    target_link_libraries(mobithumbnail qmobipocket)
else()
    target_link_libraries(mobithumbnail QMobipocket6)
endif()
