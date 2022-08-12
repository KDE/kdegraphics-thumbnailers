kcoreaddons_add_plugin(rawthumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(rawthumbnail PRIVATE
    rawcreator.cpp
)

target_link_libraries(rawthumbnail
    KF5::KIOWidgets
    KF5::KDcraw
    KF5::KExiv2
    Qt::Gui
)
