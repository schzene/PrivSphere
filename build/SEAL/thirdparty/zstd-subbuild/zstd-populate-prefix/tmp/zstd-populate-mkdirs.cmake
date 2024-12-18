# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-src"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-build"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/tmp"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/src/zstd-populate-stamp"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/src"
  "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/src/zstd-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/src/zstd-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/PrivSphere/build/SEAL/thirdparty/zstd-subbuild/zstd-populate-prefix/src/zstd-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
