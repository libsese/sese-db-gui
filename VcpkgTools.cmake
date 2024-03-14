macro(SESE_AUTO_FIND_VCPKG)
  if (NOT VCPKG_FOUND)
    if (DEFINED CMAKE_TOOLCHAIN_FILE)
      get_filename_component(FILENAME ${CMAKE_TOOLCHAIN_FILE} NAME)
      if (${FILENAME} STREQUAL "vcpkg.cmake")
        set(VCPKG_FOUND ON)
      endif ()
    endif ()

    if (NOT VCPKG_FOUND)
      if (NOT $ENV{VCPKG_ROOT} STREQUAL "")
        set(VCPKG_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        message(STATUS "VCPKG_TOOLCHAIN_FILE: ${VCPKG_TOOLCHAIN_FILE}")
        include(${VCPKG_TOOLCHAIN_FILE})
      else ()
        find_path(VCPKG_TOOLCHAIN_DIR vcpkg.cmake
                C:/src/vcpkg/scripts/buildsystems
                C:/vcpkg/scripts/buildsystems
                D:/vcpkg/scripts/buildsystems
                E:/vcpkg/scripts/buildsystems
                F:/vcpkg/scripts/buildsystems
                C:/Users/$ENV{USER}/vcpkg/scripts/buildsystems
                C:/Users/$ENV{USER}/.vcpkg/scripts/buildsystems
                /usr/local/vcpkg/scripts/buildsystems
                /usr/local/share/vcpkg/scripts/buildsystems
                /src/vcpkg/scripts/buildsystems
                /home/$ENV{USER}/vcpkg/scripts/buildsystems
                /home/$ENV{USER}/.vcpkg/scripts/buildsystems
                /Users/$ENV{USER}/vcpkg/scripts/buildsystems
                /Users/$ENV{USER}/.vcpkg/scripts/buildsystems
        )

        if (${VCPKG_TOOLCHAIN_DIR} STREQUAL "VCPKG_TOOLCHAIN_DIR-NOTFOUND")
          message(FATAL_ERROR "Could not found the vcpkg.cmake")
        else ()
          message(STATUS "VCPKG_TOOLCHAIN_FILE: ${VCPKG_TOOLCHAIN_DIR}/vcpkg.cmake")
          include("${VCPKG_TOOLCHAIN_DIR}/vcpkg.cmake")
        endif ()
      endif ()
    endif ()
  endif ()
endmacro()