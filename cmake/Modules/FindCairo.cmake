# - Try to find Cairo
# Once done this will define
#  CAIRO_FOUND - System has Cairo
#  CAIRO_INCLUDE_DIRS - The Cairo include directories
#  CAIRO_LIBRARIES - The libraries needed to use Cairo
#  CAIRO_DEFINITIONS - Compiler switches required for using Cairo


if (CAIRO_INCLUDE_DIRS AND CAIRO_LIBRARIES)
    set(CAIRO_FOUND TRUE) # in-cache

else (CAIRO_INCLUDE_DIRS AND CAIRO_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_CAIRO QUIET cairo)
        set(CAIRO_DEFINITIONS ${PC_CAIRO_CFLAGS_OTHER})

        find_path(CAIRO_INCLUDE_DIR cairo.h
                HINTS ${PC_CAIRO_INCLUDEDIR} ${PC_CAIRO_INCLUDE_DIRS}
                PATH_SUFFIXES cairo)

        find_library(CAIRO_LIBRARY NAMES cairo libcairo
                HINTS ${PC_CAIRO_LIBDIR} ${PC_CAIRO_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(Cairo DEFAULT_MSG CAIRO_LIBRARY CAIRO_INCLUDE_DIR)

        mark_as_advanced(CAIRO_INCLUDE_DIR CAIRO_LIBRARY)

        set(CAIRO_LIBRARIES ${CAIRO_LIBRARY})
        set(CAIRO_INCLUDE_DIRS ${CAIRO_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(CAIRO_FOUND TRUE)
    endif (NOT WIN32)
endif (CAIRO_INCLUDE_DIRS AND CAIRO_LIBRARIES)