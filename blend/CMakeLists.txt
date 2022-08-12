kcoreaddons_add_plugin(blenderthumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(blenderthumbnail PRIVATE
    blendercreator.cpp
)

target_link_libraries(blenderthumbnail
    KF5::KIOWidgets
    KF5::Archive
    Qt::Core
)
