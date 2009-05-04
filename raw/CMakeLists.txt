project(rawthumbnail)

## includes and linking
include_directories(${KEXIV2_INCLUDE_DIR} ${KDCRAW_INCLUDE_DIR})


#sources
set(rawthumbnail_SRCS rawcreator.cpp)
kde4_add_plugin(rawthumbnail ${rawthumbnail_SRCS})


## includes and linking
target_link_libraries(rawthumbnail ${KDE4_KIO_LIBS} ${KDCRAW_LIBRARIES} ${KEXIV2_LIBRARIES} ${QT_QTGUI_LIBRARY} ${KDE4_KDECORE_LIBS})

## install the plugin
install(TARGETS rawthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES rawthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})


