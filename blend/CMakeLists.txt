kcoreaddons_add_plugin(blenderthumbnail INSTALL_NAMESPACE "kf6/thumbcreator")

target_sources(blenderthumbnail PRIVATE
    blendercreator.cpp
)

target_link_libraries(blenderthumbnail
    KF6::KIOGui
    KF6::Archive
    Qt::Core
)
