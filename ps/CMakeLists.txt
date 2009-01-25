include_directories( ${CMAKE_SOURCE_DIR}/kghostview  )

add_definitions (-DQT3_SUPPORT -DQT3_SUPPORT_WARNINGS)
include_directories(${STRIGI_INCLUDE_DIR})

########### next target ###############

set(gsthumbnail_PART_SRCS gscreator.cpp dscparse.cpp dscparse_adapter.cpp)


kde4_add_plugin(gsthumbnail ${gsthumbnail_PART_SRCS})


target_link_libraries(gsthumbnail  ${KDE4_KDECORE_LIBS} ${KDE4_KIO_LIBS} ${QT_QTGUI_LIBRARY} )

install(TARGETS gsthumbnail  DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES gsthumbnail.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

