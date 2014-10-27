########### next target ###############

set(gsthumbnail_PART_SRCS gscreator.cpp dscparse.cpp dscparse_adapter.cpp)


add_library(gsthumbnail MODULE ${gsthumbnail_PART_SRCS})


target_link_libraries(gsthumbnail  Qt5::Gui KF5::KIOWidgets )

install(TARGETS gsthumbnail  DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES gsthumbnail.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

