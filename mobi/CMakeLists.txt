include_directories(${KDE4_INCLUDES} ${QT_INCLUDES}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/libs/mobipocket
                   )

########### next target ###############

set(mobithumbnail_SRCS
  ${PROJECT_SOURCE_DIR}/libs/mobipocket/mobipocket.cpp
  ${PROJECT_SOURCE_DIR}/libs/mobipocket/decompressor.cpp
  mobithumbnail.cpp
)

kde4_add_plugin(mobithumbnail ${mobithumbnail_SRCS})
target_link_libraries(mobithumbnail  ${KDE4_KDECORE_LIBS} ${KDE4_KIO_LIBS} ${QT_QTGUI_LIBRARY} )
install(TARGETS mobithumbnail DESTINATION ${PLUGIN_INSTALL_DIR})

########### install files ###############

install( FILES mobithumbnail.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
