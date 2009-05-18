macro_optional_add_subdirectory(ps)
add_subdirectory(mobi)

if(EXIV2_FOUND)
macro_optional_add_subdirectory(raw)
endif(EXIV2_FOUND)
