# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-build"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix/tmp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix/src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/a/mai_stuff/Computer_grafics/lab_3/cmake-build-debug/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp/${subDir}")
endforeach()
