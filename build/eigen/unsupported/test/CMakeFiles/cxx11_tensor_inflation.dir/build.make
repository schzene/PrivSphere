# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /root/cmake-3.23.3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /root/cmake-3.23.3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/PrivSphere/extern/eigen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/PrivSphere/build/eigen

# Include any dependencies generated for this target.
include unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/compiler_depend.make

# Include the progress variables for this target.
include unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/progress.make

# Include the compile flags for this target's objects.
include unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/flags.make

unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o: unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/flags.make
unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o: /home/PrivSphere/extern/eigen/unsupported/test/cxx11_tensor_inflation.cpp
unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o: unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/eigen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o"
	cd /home/PrivSphere/build/eigen/unsupported/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o -MF CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o.d -o CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o -c /home/PrivSphere/extern/eigen/unsupported/test/cxx11_tensor_inflation.cpp

unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.i"
	cd /home/PrivSphere/build/eigen/unsupported/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/PrivSphere/extern/eigen/unsupported/test/cxx11_tensor_inflation.cpp > CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.i

unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.s"
	cd /home/PrivSphere/build/eigen/unsupported/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/PrivSphere/extern/eigen/unsupported/test/cxx11_tensor_inflation.cpp -o CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.s

# Object files for target cxx11_tensor_inflation
cxx11_tensor_inflation_OBJECTS = \
"CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o"

# External object files for target cxx11_tensor_inflation
cxx11_tensor_inflation_EXTERNAL_OBJECTS =

unsupported/test/cxx11_tensor_inflation: unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/cxx11_tensor_inflation.cpp.o
unsupported/test/cxx11_tensor_inflation: unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/build.make
unsupported/test/cxx11_tensor_inflation: unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/PrivSphere/build/eigen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cxx11_tensor_inflation"
	cd /home/PrivSphere/build/eigen/unsupported/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cxx11_tensor_inflation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/build: unsupported/test/cxx11_tensor_inflation
.PHONY : unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/build

unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/clean:
	cd /home/PrivSphere/build/eigen/unsupported/test && $(CMAKE_COMMAND) -P CMakeFiles/cxx11_tensor_inflation.dir/cmake_clean.cmake
.PHONY : unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/clean

unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/depend:
	cd /home/PrivSphere/build/eigen && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/PrivSphere/extern/eigen /home/PrivSphere/extern/eigen/unsupported/test /home/PrivSphere/build/eigen /home/PrivSphere/build/eigen/unsupported/test /home/PrivSphere/build/eigen/unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/test/CMakeFiles/cxx11_tensor_inflation.dir/depend
