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
CMAKE_SOURCE_DIR = /home/PrivSphere/extern/SEAL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/PrivSphere/build/SEAL

# Include any dependencies generated for this target.
include thirdparty/zlib-build/CMakeFiles/zlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.make

# Include the progress variables for this target.
include thirdparty/zlib-build/CMakeFiles/zlib.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make

thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o: thirdparty/zlib-src/adler32.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o -MF CMakeFiles/zlib.dir/adler32.o.d -o CMakeFiles/zlib.dir/adler32.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/adler32.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/adler32.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/adler32.c > CMakeFiles/zlib.dir/adler32.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/adler32.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/adler32.c -o CMakeFiles/zlib.dir/adler32.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o: thirdparty/zlib-src/compress.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o -MF CMakeFiles/zlib.dir/compress.o.d -o CMakeFiles/zlib.dir/compress.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/compress.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/compress.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/compress.c > CMakeFiles/zlib.dir/compress.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/compress.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/compress.c -o CMakeFiles/zlib.dir/compress.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o: thirdparty/zlib-src/crc32.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o -MF CMakeFiles/zlib.dir/crc32.o.d -o CMakeFiles/zlib.dir/crc32.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/crc32.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/crc32.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/crc32.c > CMakeFiles/zlib.dir/crc32.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/crc32.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/crc32.c -o CMakeFiles/zlib.dir/crc32.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o: thirdparty/zlib-src/deflate.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o -MF CMakeFiles/zlib.dir/deflate.o.d -o CMakeFiles/zlib.dir/deflate.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/deflate.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/deflate.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/deflate.c > CMakeFiles/zlib.dir/deflate.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/deflate.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/deflate.c -o CMakeFiles/zlib.dir/deflate.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o: thirdparty/zlib-src/gzclose.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o -MF CMakeFiles/zlib.dir/gzclose.o.d -o CMakeFiles/zlib.dir/gzclose.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzclose.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzclose.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzclose.c > CMakeFiles/zlib.dir/gzclose.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzclose.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzclose.c -o CMakeFiles/zlib.dir/gzclose.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o: thirdparty/zlib-src/gzlib.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o -MF CMakeFiles/zlib.dir/gzlib.o.d -o CMakeFiles/zlib.dir/gzlib.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzlib.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzlib.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzlib.c > CMakeFiles/zlib.dir/gzlib.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzlib.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzlib.c -o CMakeFiles/zlib.dir/gzlib.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o: thirdparty/zlib-src/gzread.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o -MF CMakeFiles/zlib.dir/gzread.o.d -o CMakeFiles/zlib.dir/gzread.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzread.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzread.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzread.c > CMakeFiles/zlib.dir/gzread.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzread.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzread.c -o CMakeFiles/zlib.dir/gzread.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o: thirdparty/zlib-src/gzwrite.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o -MF CMakeFiles/zlib.dir/gzwrite.o.d -o CMakeFiles/zlib.dir/gzwrite.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzwrite.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzwrite.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzwrite.c > CMakeFiles/zlib.dir/gzwrite.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzwrite.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/gzwrite.c -o CMakeFiles/zlib.dir/gzwrite.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o: thirdparty/zlib-src/inflate.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o -MF CMakeFiles/zlib.dir/inflate.o.d -o CMakeFiles/zlib.dir/inflate.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inflate.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inflate.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inflate.c > CMakeFiles/zlib.dir/inflate.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inflate.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inflate.c -o CMakeFiles/zlib.dir/inflate.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o: thirdparty/zlib-src/infback.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o -MF CMakeFiles/zlib.dir/infback.o.d -o CMakeFiles/zlib.dir/infback.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/infback.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/infback.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/infback.c > CMakeFiles/zlib.dir/infback.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/infback.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/infback.c -o CMakeFiles/zlib.dir/infback.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o: thirdparty/zlib-src/inftrees.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o -MF CMakeFiles/zlib.dir/inftrees.o.d -o CMakeFiles/zlib.dir/inftrees.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inftrees.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inftrees.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inftrees.c > CMakeFiles/zlib.dir/inftrees.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inftrees.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inftrees.c -o CMakeFiles/zlib.dir/inftrees.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o: thirdparty/zlib-src/inffast.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o -MF CMakeFiles/zlib.dir/inffast.o.d -o CMakeFiles/zlib.dir/inffast.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inffast.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inffast.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inffast.c > CMakeFiles/zlib.dir/inffast.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inffast.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/inffast.c -o CMakeFiles/zlib.dir/inffast.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o: thirdparty/zlib-src/trees.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o -MF CMakeFiles/zlib.dir/trees.o.d -o CMakeFiles/zlib.dir/trees.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/trees.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/trees.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/trees.c > CMakeFiles/zlib.dir/trees.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/trees.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/trees.c -o CMakeFiles/zlib.dir/trees.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o: thirdparty/zlib-src/uncompr.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o -MF CMakeFiles/zlib.dir/uncompr.o.d -o CMakeFiles/zlib.dir/uncompr.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/uncompr.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/uncompr.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/uncompr.c > CMakeFiles/zlib.dir/uncompr.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/uncompr.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/uncompr.c -o CMakeFiles/zlib.dir/uncompr.s

thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/flags.make
thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o: thirdparty/zlib-src/zutil.c
thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o: thirdparty/zlib-build/CMakeFiles/zlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o -MF CMakeFiles/zlib.dir/zutil.o.d -o CMakeFiles/zlib.dir/zutil.o -c /home/PrivSphere/build/SEAL/thirdparty/zlib-src/zutil.c

thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/zutil.i"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/PrivSphere/build/SEAL/thirdparty/zlib-src/zutil.c > CMakeFiles/zlib.dir/zutil.i

thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/zutil.s"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/PrivSphere/build/SEAL/thirdparty/zlib-src/zutil.c -o CMakeFiles/zlib.dir/zutil.s

# Object files for target zlib
zlib_OBJECTS = \
"CMakeFiles/zlib.dir/adler32.o" \
"CMakeFiles/zlib.dir/compress.o" \
"CMakeFiles/zlib.dir/crc32.o" \
"CMakeFiles/zlib.dir/deflate.o" \
"CMakeFiles/zlib.dir/gzclose.o" \
"CMakeFiles/zlib.dir/gzlib.o" \
"CMakeFiles/zlib.dir/gzread.o" \
"CMakeFiles/zlib.dir/gzwrite.o" \
"CMakeFiles/zlib.dir/inflate.o" \
"CMakeFiles/zlib.dir/infback.o" \
"CMakeFiles/zlib.dir/inftrees.o" \
"CMakeFiles/zlib.dir/inffast.o" \
"CMakeFiles/zlib.dir/trees.o" \
"CMakeFiles/zlib.dir/uncompr.o" \
"CMakeFiles/zlib.dir/zutil.o"

# External object files for target zlib
zlib_EXTERNAL_OBJECTS =

lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/adler32.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/compress.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/crc32.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/deflate.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/gzclose.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/gzlib.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/gzread.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/gzwrite.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/inflate.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/infback.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/inftrees.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/inffast.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/trees.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/uncompr.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/zutil.o
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/build.make
lib/libz.so.1.2.13: thirdparty/zlib-build/CMakeFiles/zlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/PrivSphere/build/SEAL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C shared library ../../lib/libz.so"
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zlib.dir/link.txt --verbose=$(VERBOSE)
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libz.so.1.2.13 ../../lib/libz.so.1 ../../lib/libz.so

lib/libz.so.1: lib/libz.so.1.2.13
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libz.so.1

lib/libz.so: lib/libz.so.1.2.13
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libz.so

# Rule to build all files generated by this target.
thirdparty/zlib-build/CMakeFiles/zlib.dir/build: lib/libz.so
.PHONY : thirdparty/zlib-build/CMakeFiles/zlib.dir/build

thirdparty/zlib-build/CMakeFiles/zlib.dir/clean:
	cd /home/PrivSphere/build/SEAL/thirdparty/zlib-build && $(CMAKE_COMMAND) -P CMakeFiles/zlib.dir/cmake_clean.cmake
.PHONY : thirdparty/zlib-build/CMakeFiles/zlib.dir/clean

thirdparty/zlib-build/CMakeFiles/zlib.dir/depend:
	cd /home/PrivSphere/build/SEAL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/PrivSphere/extern/SEAL /home/PrivSphere/build/SEAL/thirdparty/zlib-src /home/PrivSphere/build/SEAL /home/PrivSphere/build/SEAL/thirdparty/zlib-build /home/PrivSphere/build/SEAL/thirdparty/zlib-build/CMakeFiles/zlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/zlib-build/CMakeFiles/zlib.dir/depend
