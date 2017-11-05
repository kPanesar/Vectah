# - Try to find Cairomm
# Once done this will define
#  CAIROMM_FOUND - System has Cairomm
#  CAIROMM_INCLUDE_DIRS - The Cairomm include directories
#  CAIROMM_LIBRARIES - The libraries needed to use Cairomm
#  CAIROMM_DEFINITIONS - Compiler switches required for using Cairomm


if (CAIROMM_INCLUDE_DIRS AND CAIROMM_LIBRARIES)
    set(CAIROMM_FOUND TRUE) # in-cache

else (CAIROMM_INCLUDE_DIRS AND CAIROMM_LIBRARIES)
    if (NOT WIN32)
        find_package(PkgConfig)
        find_package(SigC++)
        find_package(FreeType2)
        find_package(Cairo)
        pkg_check_modules(PC_CAIROMM QUIET cairomm-1.0)
        set(CAIROMM_DEFINITIONS ${PC_CAIROMM_CFLAGS_OTHER})

        find_path(CAIROMM_INCLUDE_DIR cairomm/cairomm.h
                HINTS ${PC_CAIROMM_INCLUDEDIR} ${PC_CAIROMM_INCLUDE_DIRS}
                PATH_SUFFIXES cairomm)

        find_path(CAIROMMCONFIG_INCLUDE_DIR cairommconfig.h
                HINTS ${PC_CAIROMM_INCLUDEDIR} ${PC_CAIROMM_INCLUDE_DIRS})

        find_library(CAIROMM_LIBRARY NAMES cairomm-1.0 libcairomm-1.0
                HINTS ${PC_CAIROMM_LIBDIR} ${PC_CAIROMM_LIBRARY_DIRS})

        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(Cairomm DEFAULT_MSG CAIROMM_LIBRARY CAIROMM_INCLUDE_DIR CAIROMMCONFIG_INCLUDE_DIR)

        mark_as_advanced(CAIROMM_INCLUDE_DIR CAIROMMCONFIG_INCLUDE_DIR CAIROMM_LIBRARY)

        set(CAIROMM_LIBRARIES ${CAIROMM_LIBRARY}
                ${SIGC++_LIBRARIES}
                ${FREETYPE2_LIBRARIES}
                ${CAIRO_LIBRARIES})
        set(CAIROMM_INCLUDE_DIRS
                ${CAIROMM_INCLUDE_DIR}
                ${CAIROMMCONFIG_INCLUDE_DIR}
                ${SIGC++_INCLUDE_DIRS}
                ${FREETYPE2_INCLUDE_DIRS}
                ${CAIRO_INCLUDE_DIRS})
    else (NOT WIN32)
        # assume so, for now
        set(CAIROMM_FOUND TRUE)
    endif (NOT WIN32)
endif (CAIROMM_INCLUDE_DIRS AND CAIROMM_LIBRARIES)