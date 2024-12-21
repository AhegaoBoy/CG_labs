# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-build"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/tmp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp/${subDir}")
endforeach()
