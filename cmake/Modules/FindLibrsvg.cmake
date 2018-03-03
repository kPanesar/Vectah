# - Try to find Librsvg
# Once done this will define
#  LIBRSVG_FOUND - System has Librsvg
#  LIBRSVG_INCLUDE_DIRS - The Librsvg include directories
#  LIBRSVG_LIBRARIES - The libraries needed to use Librsvg
#  LIBRSVG_DEFINITIONS - Compiler switches required for using Librsvg


if (LIBRSVG_INCLUDE_DIRS AND LIBRSVG_LIBRARIES)
    set(LIBRSVG_FOUND TRUE) # in-cache

else (LIBRSVG_INCLUDE_DIRS AND LIBRSVG_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        find_package(GLib REQUIRED gobject gio)
        find_package(Cairo REQUIRED)
        find_package(GdkPixbuf REQUIRED)

        pkg_check_modules(PC_LIBRSVG QUIET librsvg-2)
        set(LIBRSVG_DEFINITIONS ${PC_LIBRSVG_CFLAGS_OTHER})

        find_path(LIBRSVG_INCLUDE_DIR librsvg/rsvg.h
                HINTS ${PC_LIBRSVG_INCLUDEDIR} ${PC_LIBRSVG_INCLUDE_DIRS}
                PATH_SUFFIXES librsvg-2.0)

        find_library(LIBRSVG_LIBRARY NAMES rsvg-2 librsvg-2
                HINTS ${PC_LIBRSVG_LIBDIR} ${PC_LIBRSVG_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(Librsvg DEFAULT_MSG LIBRSVG_LIBRARY LIBRSVG_INCLUDE_DIR)

        mark_as_advanced(LIBRSVG_INCLUDE_DIR LIBRSVG_LIBRARY)

        set(LIBRSVG_LIBRARIES ${LIBRSVG_LIBRARY} ${CAIRO_LIBRARY} ${GDKPIXBUF_LIBRARY} ${GLIB_LIBRARY})
        set(LIBRSVG_INCLUDE_DIRS ${LIBRSVG_INCLUDE_DIR} ${CAIRO_INCLUDE_DIR} ${GDKPIXBUF_INCLUDE_DIR} ${GLIB_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(LIBRSVG_FOUND TRUE)
    endif (NOT WIN32)
endif (LIBRSVG_INCLUDE_DIRS AND LIBRSVG_LIBRARIES)