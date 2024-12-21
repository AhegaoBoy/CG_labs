# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-build"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src"
  "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/a/mai_stuff/Computer_grafics/lab_6/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
