kcoreaddons_add_plugin(gsthumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(gsthumbnail PRIVATE
    gscreator.cpp
    dscparse.cpp
    dscparse_adapter.cpp
)

target_link_libraries(gsthumbnail
    KF5::KIOWidgets
    Qt::Gui
)
