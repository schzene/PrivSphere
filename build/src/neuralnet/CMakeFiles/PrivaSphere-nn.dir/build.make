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
CMAKE_SOURCE_DIR = /home/PrivSphere

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/PrivSphere/build

# Include any dependencies generated for this target.
include src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/compiler_depend.make

# Include the progress variables for this target.
include src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/progress.make

# Include the compile flags for this target's objects.
include src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/flags.make

src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o: src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/flags.make
src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o: ../src/neuralnet/simplenet.cpp
src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o: src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o"
	cd /home/PrivSphere/build/src/neuralnet && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o -MF CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o.d -o CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o -c /home/PrivSphere/src/neuralnet/simplenet.cpp

src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.i"
	cd /home/PrivSphere/build/src/neuralnet && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/PrivSphere/src/neuralnet/simplenet.cpp > CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.i

src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.s"
	cd /home/PrivSphere/build/src/neuralnet && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/PrivSphere/src/neuralnet/simplenet.cpp -o CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.s

# Object files for target PrivaSphere-nn
PrivaSphere__nn_OBJECTS = \
"CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o"

# External object files for target PrivaSphere-nn
PrivaSphere__nn_EXTERNAL_OBJECTS =

lib/libPrivaSphere-nn.a: src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/simplenet.cpp.o
lib/libPrivaSphere-nn.a: src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/build.make
lib/libPrivaSphere-nn.a: src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/PrivSphere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libPrivaSphere-nn.a"
	cd /home/PrivSphere/build/src/neuralnet && $(CMAKE_COMMAND) -P CMakeFiles/PrivaSphere-nn.dir/cmake_clean_target.cmake
	cd /home/PrivSphere/build/src/neuralnet && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PrivaSphere-nn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/build: lib/libPrivaSphere-nn.a
.PHONY : src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/build

src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/clean:
	cd /home/PrivSphere/build/src/neuralnet && $(CMAKE_COMMAND) -P CMakeFiles/PrivaSphere-nn.dir/cmake_clean.cmake
.PHONY : src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/clean

src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/depend:
	cd /home/PrivSphere/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/PrivSphere /home/PrivSphere/src/neuralnet /home/PrivSphere/build /home/PrivSphere/build/src/neuralnet /home/PrivSphere/build/src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/neuralnet/CMakeFiles/PrivaSphere-nn.dir/depend
