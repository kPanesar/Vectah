# - Try to find GIO 2.0
# Once done, this will define
#
#  GIO_FOUND - system has GIO
#  GIO_INCLUDE_DIRS - the GIO include directories
#  GIO_LIBRARIES - link these to use GIO

if (GIO_INCLUDE_DIRS AND GIO_LIBRARIES)
    set(GIO_FOUND TRUE) # in-cache

else (GIO_INCLUDE_DIRS AND GIO_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_GIO QUIET gio)
        set(GIO_DEFINITIONS ${PC_GIO_CFLAGS_OTHER})

        find_path(GIO_INCLUDE_DIR glib-2.0/gio/gio.h
                HINTS ${PC_GIO_INCLUDEDIR} ${PC_GIO_INCLUDE_DIRS}
                PATH_SUFFIXES gio)

        find_library(GIO_LIBRARY NAMES gio-2.0 libgio-2.0
                HINTS ${PC_GIO_LIBDIR} ${PC_GIO_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        # Handle the QUIETLY and REQUIRED arguments and set GIO_FOUND to TRUE if all listed variables are TRUE
        find_package_handle_standard_args(GIO DEFAULT_MSG GIO_LIBRARY GIO_INCLUDE_DIR)

        mark_as_advanced(GIO_INCLUDE_DIR GIO_LIBRARY)

        set(GIO_LIBRARIES ${GIO_LIBRARY})
        set(GIO_INCLUDE_DIRS ${GIO_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(GIO_FOUND TRUE)
    endif (NOT WIN32)
endif (GIO_INCLUDE_DIRS AND GIO_LIBRARIES)

