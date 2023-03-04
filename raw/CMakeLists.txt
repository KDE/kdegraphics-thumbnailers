kcoreaddons_add_plugin(rawthumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(rawthumbnail PRIVATE
    rawcreator.cpp
)

target_link_libraries(rawthumbnail
    KF${QT_MAJOR_VERSION}::KIOGui
    KF${QT_MAJOR_VERSION}::KDcraw
    KF${QT_MAJOR_VERSION}::KExiv2
    Qt::Gui
)
