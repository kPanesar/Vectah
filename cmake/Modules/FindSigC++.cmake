# - Try to find SigC++
# Once done this will define
#  SIGC++_FOUND - System has SigC++
#  SIGC++_INCLUDE_DIRS - The SigC++ include directories
#  SIGC++_LIBRARIES - The libraries needed to use SigC++
#  SIGC++_DEFINITIONS - Compiler switches required for using SigC++


if (SIGC++_INCLUDE_DIRS AND SIGC++_LIBRARIES)
    set(SIGC++_FOUND TRUE) # in-cache

else (SIGC++_INCLUDE_DIRS AND SIGC++_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_SIGC++ QUIET sigc++-2.0)
        set(SIGC++_DEFINITIONS ${PC_SIGC++_CFLAGS_OTHER})

        find_path(SIGC++_INCLUDE_DIR sigc++/sigc++.h
                HINTS ${PC_SIGC++_INCLUDEDIR} ${PC_SIGC++_INCLUDE_DIRS}
                PATH_SUFFIXES sigc++)

        find_path(SIGC++CONFIG_INCLUDE_DIR sigc++config.h
                HINTS ${PC_SIGC++_INCLUDEDIR} ${PC_SIGC++_INCLUDE_DIRS})

        find_library(SIGC++_LIBRARY NAMES sigc-2.0 libsigc-2.0
                HINTS ${PC_SIGC++_LIBDIR} ${PC_SIGC++_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(SigC++ DEFAULT_MSG SIGC++_LIBRARY SIGC++_INCLUDE_DIR SIGC++CONFIG_INCLUDE_DIR)

        mark_as_advanced(SIGC++_INCLUDE_DIR SIGC++CONFIG_INCLUDE_DIR SIGC++_LIBRARY)

        set(SIGC++_LIBRARIES ${SIGC++_LIBRARY})
        set(SIGC++_INCLUDE_DIRS ${SIGC++_INCLUDE_DIR} ${SIGC++CONFIG_INCLUDE_DIR})
    else (NOT WIN32)
        # assume so, for now
        set(SIGC++_FOUND TRUE)
    endif (NOT WIN32)
endif (SIGC++_INCLUDE_DIRS AND SIGC++_LIBRARIES)