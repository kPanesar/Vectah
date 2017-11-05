# - Try to find FreeType2
# Once done this will define
#  FREETYPE2_FOUND - System has FreeType2
#  FREETYPE2_INCLUDE_DIRS - The FreeType2 include directories
#  FREETYPE2_LIBRARIES - The libraries needed to use FreeType2
#  FREETYPE2_DEFINITIONS - Compiler switches required for using FreeType2


if (FREETYPE2_INCLUDE_DIRS AND FREETYPE2_LIBRARIES)
    set(FREETYPE2_FOUND TRUE) # in-cache

else (FREETYPE2_INCLUDE_DIRS AND FREETYPE2_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_FREETYPE2 QUIET freetype2)
        set(FREETYPE2_DEFINITIONS ${PC_FREETYPE2_CFLAGS_OTHER})

        find_path(FREETYPE2_INCLUDE_DIR ft2build.h
                HINTS ${PC_FREETYPE2_INCLUDEDIR} ${PC_FREETYPE2_INCLUDE_DIRS})

        find_library(FREETYPE2_LIBRARY NAMES freetype libfreetype
                HINTS ${PC_FREETYPE2_LIBDIR} ${PC_FREETYPE2_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(FreeType2 DEFAULT_MSG FREETYPE2_LIBRARY FREETYPE2_INCLUDE_DIR)

        mark_as_advanced(FREETYPE2_INCLUDE_DIR FREETYPE2_LIBRARY)

        set(FREETYPE2_LIBRARIES ${FREETYPE2_LIBRARY})
        set(FREETYPE2_INCLUDE_DIRS ${FREETYPE2_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(FREETYPE2_FOUND TRUE)
    endif (NOT WIN32)
endif (FREETYPE2_INCLUDE_DIRS AND FREETYPE2_LIBRARIES)