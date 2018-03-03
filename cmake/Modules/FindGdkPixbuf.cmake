# Try to find gdk-pixbuf 2.0
# Once done, this will define :
#   GDKPIXBUF_FOUND
#   GDKPIXBUF_INCLUDE_DIRS
#   GDKPIXBUF_LIBRARIES


if (GDKPIXBUF_INCLUDE_DIRS AND GDKPIXBUF_LIBRARIES)
    set(GDKPIXBUF_FOUND TRUE) # in-cache

else (GDKPIXBUF_INCLUDE_DIRS AND GDKPIXBUF_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)

        pkg_check_modules(PC_GDKPIXBUF QUIET gdk-pixbuf-2)
        set(GDKPIXBUF_DEFINITIONS ${PC_GDKPIXBUF_CFLAGS_OTHER})

        find_path(GDKPIXBUF_INCLUDE_DIR gdk-pixbuf/gdk-pixbuf.h
                HINTS ${PC_GDKPIXBUF_INCLUDEDIR} ${PC_GDKPIXBUF_INCLUDE_DIRS}
                PATH_SUFFIXES gdk-pixbuf-2.0)

        find_library(GDKPIXBUF_LIBRARY NAMES gdk_pixbuf-2.0 libgdk_pixbuf-2.0
                HINTS ${PC_GDKPIXBUF_LIBDIR} ${PC_GDKPIXBUF_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(GDKPixbuf DEFAULT_MSG GDKPIXBUF_LIBRARY GDKPIXBUF_INCLUDE_DIR)

        mark_as_advanced(GDKPIXBUF_INCLUDE_DIR GDKPIXBUF_LIBRARY)

        set(GDKPIXBUF_LIBRARIES ${GDKPIXBUF_LIBRARY})
        set(GDKPIXBUF_INCLUDE_DIRS ${GDKPIXBUF_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(GDKPIXBUF_FOUND TRUE)
    endif (NOT WIN32)
endif (GDKPIXBUF_INCLUDE_DIRS AND GDKPIXBUF_LIBRARIES)