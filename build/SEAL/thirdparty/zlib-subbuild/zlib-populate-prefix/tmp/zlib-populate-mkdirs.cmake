# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-src"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-build"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/tmp"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/src"
  "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/PrivSphere/build/SEAL/thirdparty/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()