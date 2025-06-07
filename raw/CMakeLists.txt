kcoreaddons_add_plugin(rawthumbnail INSTALL_NAMESPACE "kf6/thumbcreator")

target_sources(rawthumbnail PRIVATE
    rawcreator.cpp
)

target_link_libraries(rawthumbnail
    KF6::KIOGui
    Qt::Gui
)

target_link_libraries(rawthumbnail
    KDcrawQt6
    KExiv2Qt6
)
