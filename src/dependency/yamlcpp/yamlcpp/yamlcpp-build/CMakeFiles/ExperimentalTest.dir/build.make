# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/qvanle/projects/CrossyRoad/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/qvanle/projects/CrossyRoad/build

# Utility rule file for ExperimentalTest.

# Include any custom commands dependencies for this target.
include /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/compiler_depend.make

# Include the progress variables for this target.
include /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/progress.make

/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest:
	cd /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build && /usr/bin/ctest -D ExperimentalTest

ExperimentalTest: /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest
ExperimentalTest: /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/build.make
.PHONY : ExperimentalTest

# Rule to build all files generated by this target.
/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/build: ExperimentalTest
.PHONY : /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/build

/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/clean:
	cd /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalTest.dir/cmake_clean.cmake
.PHONY : /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/clean

/home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/depend:
	cd /home/qvanle/projects/CrossyRoad/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/qvanle/projects/CrossyRoad/src /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-src /home/qvanle/projects/CrossyRoad/build /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : /home/qvanle/projects/CrossyRoad/src/dependency/yamlcpp/yamlcpp/yamlcpp-build/CMakeFiles/ExperimentalTest.dir/depend

