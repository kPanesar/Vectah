# - Try to find GLib
# Once done this will define
#  GLIB_FOUND - System has GLib
#  GLIB_INCLUDE_DIRS - The GLib include directories
#  GLIB_LIBRARIES - The libraries needed to use GLib
#  GLIB_DEFINITIONS - Compiler switches required for using GLib


if (GLIB_INCLUDE_DIRS AND GLIB_LIBRARIES)
    set(GLIB_FOUND TRUE) # in-cache

else (GLIB_INCLUDE_DIRS AND GLIB_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)

        pkg_check_modules(PC_GLIB QUIET glib-2)
        set(GLIB_DEFINITIONS ${PC_GLIB_CFLAGS_OTHER})

        find_path(GLIB_INCLUDE_DIR glib.h
                HINTS ${PC_GLIB_INCLUDEDIR} ${PC_GLIB_INCLUDE_DIRS}
                PATH_SUFFIXES glib-2.0)

        find_path(GLIBCONFIG_INCLUDE_DIR glibconfig.h
                HINTS ${PC_GLIB_INCLUDEDIR} ${PC_GLIB_INCLUDE_DIRS})

        find_library(GLIB_LIBRARY NAMES glib-2.0 libglib-2.0
                HINTS ${PC_GLIB_LIBDIR} ${PC_GLIB_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(GLib DEFAULT_MSG GLIB_LIBRARY GLIB_INCLUDE_DIR GLIBCONFIG_INCLUDE_DIR)

        mark_as_advanced(GLIB_INCLUDE_DIR GLIB_LIBRARY GLIBCONFIG_INCLUDE_DIR)

        set(GLIB_LIBRARIES ${GLIB_LIBRARY})
        set(GLIB_INCLUDE_DIRS ${GLIB_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(GLIB_FOUND TRUE)
    endif (NOT WIN32)
endif (GLIB_INCLUDE_DIRS AND GLIB_LIBRARIES)