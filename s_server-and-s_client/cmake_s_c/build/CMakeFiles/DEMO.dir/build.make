# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/s_server-and-s_client/cmake_s_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/s_server-and-s_client/cmake_s_c/build

# Include any dependencies generated for this target.
include CMakeFiles/DEMO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DEMO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DEMO.dir/flags.make

CMakeFiles/DEMO.dir/main.c.o: CMakeFiles/DEMO.dir/flags.make
CMakeFiles/DEMO.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/s_server-and-s_client/cmake_s_c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DEMO.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DEMO.dir/main.c.o   -c /root/s_server-and-s_client/cmake_s_c/main.c

CMakeFiles/DEMO.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DEMO.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/s_server-and-s_client/cmake_s_c/main.c > CMakeFiles/DEMO.dir/main.c.i

CMakeFiles/DEMO.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DEMO.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/s_server-and-s_client/cmake_s_c/main.c -o CMakeFiles/DEMO.dir/main.c.s

CMakeFiles/DEMO.dir/main.c.o.requires:

.PHONY : CMakeFiles/DEMO.dir/main.c.o.requires

CMakeFiles/DEMO.dir/main.c.o.provides: CMakeFiles/DEMO.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/DEMO.dir/build.make CMakeFiles/DEMO.dir/main.c.o.provides.build
.PHONY : CMakeFiles/DEMO.dir/main.c.o.provides

CMakeFiles/DEMO.dir/main.c.o.provides.build: CMakeFiles/DEMO.dir/main.c.o


# Object files for target DEMO
DEMO_OBJECTS = \
"CMakeFiles/DEMO.dir/main.c.o"

# External object files for target DEMO
DEMO_EXTERNAL_OBJECTS =

DEMO: CMakeFiles/DEMO.dir/main.c.o
DEMO: CMakeFiles/DEMO.dir/build.make
DEMO: lib/libSC.a
DEMO: CMakeFiles/DEMO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/s_server-and-s_client/cmake_s_c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable DEMO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DEMO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DEMO.dir/build: DEMO

.PHONY : CMakeFiles/DEMO.dir/build

CMakeFiles/DEMO.dir/requires: CMakeFiles/DEMO.dir/main.c.o.requires

.PHONY : CMakeFiles/DEMO.dir/requires

CMakeFiles/DEMO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DEMO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DEMO.dir/clean

CMakeFiles/DEMO.dir/depend:
	cd /root/s_server-and-s_client/cmake_s_c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/s_server-and-s_client/cmake_s_c /root/s_server-and-s_client/cmake_s_c /root/s_server-and-s_client/cmake_s_c/build /root/s_server-and-s_client/cmake_s_c/build /root/s_server-and-s_client/cmake_s_c/build/CMakeFiles/DEMO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DEMO.dir/depend

