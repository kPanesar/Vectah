# - Try to find GObject 2.0
# Once done, this will define
#
#  GObject_FOUND - system has GObject
#  GObject_INCLUDE_DIRS - the GObject include directories
#  GObject_LIBRARIES - link these to use GObject

if (GOBJECT_INCLUDE_DIRS AND GOBJECT_LIBRARIES)
    set(GOBJECT_FOUND TRUE) # in-cache

else (GOBJECT_INCLUDE_DIRS AND GOBJECT_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_GOBJECT QUIET gobject)
        set(GOBJECT_DEFINITIONS ${PC_GOBJECT_CFLAGS_OTHER})

        find_path(GOBJECT_INCLUDE_DIR glib-2.0/gobject/gobject.h
                HINTS ${PC_GOBJECT_INCLUDEDIR} ${PC_GOBJECT_INCLUDE_DIRS}
                PATH_SUFFIXES gobject)

        find_library(GOBJECT_LIBRARY NAMES gobject-2.0 libgobject-2.0
                HINTS ${PC_GOBJECT_LIBDIR} ${PC_GOBJECT_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        # Handle the QUIETLY and REQUIRED arguments and set GOBJECT_FOUND to TRUE if all listed variables are TRUE
        find_package_handle_standard_args(GOBJECT DEFAULT_MSG GOBJECT_LIBRARY GOBJECT_INCLUDE_DIR)

        mark_as_advanced(GOBJECT_INCLUDE_DIR GOBJECT_LIBRARY)

        set(GOBJECT_LIBRARIES ${GOBJECT_LIBRARY})
        set(GOBJECT_INCLUDE_DIRS ${GOBJECT_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(GOBJECT_FOUND TRUE)
    endif (NOT WIN32)
endif (GOBJECT_INCLUDE_DIRS AND GOBJECT_LIBRARIES)


