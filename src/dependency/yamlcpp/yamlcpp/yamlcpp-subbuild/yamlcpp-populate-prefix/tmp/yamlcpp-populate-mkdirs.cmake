# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-src"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/tmp"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/src"
  "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
