kcoreaddons_add_plugin(blenderthumbnail INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(blenderthumbnail PRIVATE
    blendercreator.cpp
)

target_link_libraries(blenderthumbnail
    KF${QT_MAJOR_VERSION}::KIOGui
    KF${QT_MAJOR_VERSION}::Archive
    Qt::Core
)
