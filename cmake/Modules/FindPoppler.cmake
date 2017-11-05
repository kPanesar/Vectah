# - Try to find Poppler
# Once done this will define
#  POPPLER_FOUND - System has Poppler
#  POPPLER_INCLUDE_DIRS - The Poppler include directories
#  POPPLER_LIBRARIES - The libraries needed to use Poppler
#  POPPLER_DEFINITIONS - Compiler switches required for using Poppler


if (POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)
    set(POPPLER_FOUND TRUE) # in-cache

else (POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_POPPLER QUIET poppler-glib)
        set(POPPLER_DEFINITIONS ${PC_POPPLER_CFLAGS_OTHER})

        find_path(POPPLER_INCLUDE_DIR poppler/cpp/poppler-global.h
                HINTS ${PC_POPPLER_INCLUDEDIR} ${PC_POPPLER_INCLUDE_DIRS}
                PATH_SUFFIXES poppler-glib)

        find_library(POPPLER_LIBRARY NAMES poppler-glib libpoppler-glib
                HINTS ${PC_POPPLER_LIBDIR} ${PC_POPPLER_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        # Handle the QUIETLY and REQUIRED arguments and set POPPLER_FOUND to TRUE if all listed variables are TRUE
        find_package_handle_standard_args(Poppler DEFAULT_MSG POPPLER_LIBRARY POPPLER_INCLUDE_DIR)

        mark_as_advanced(POPPLER_INCLUDE_DIR POPPLER_LIBRARY)

        set(POPPLER_LIBRARIES ${POPPLER_LIBRARY})
        set(POPPLER_INCLUDE_DIRS ${POPPLER_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(POPPLER_FOUND TRUE)
    endif (NOT WIN32)
endif (POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)