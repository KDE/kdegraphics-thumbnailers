kcoreaddons_add_plugin(gsthumbnail INSTALL_NAMESPACE "kf6/thumbcreator")

target_sources(gsthumbnail PRIVATE
    gscreator.cpp
    dscparse.cpp
    dscparse_adapter.cpp
)

target_link_libraries(gsthumbnail
    KF6::KIOGui
    Qt::Gui
)
