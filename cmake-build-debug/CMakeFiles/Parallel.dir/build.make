# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/ras/5 course/Second/Parallel"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Parallel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Parallel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Parallel.dir/flags.make

CMakeFiles/Parallel.dir/Single.c.o: CMakeFiles/Parallel.dir/flags.make
CMakeFiles/Parallel.dir/Single.c.o: ../Single.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Parallel.dir/Single.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Parallel.dir/Single.c.o   -c "/cygdrive/c/ras/5 course/Second/Parallel/Single.c"

CMakeFiles/Parallel.dir/Single.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Parallel.dir/Single.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/ras/5 course/Second/Parallel/Single.c" > CMakeFiles/Parallel.dir/Single.c.i

CMakeFiles/Parallel.dir/Single.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Parallel.dir/Single.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/ras/5 course/Second/Parallel/Single.c" -o CMakeFiles/Parallel.dir/Single.c.s

CMakeFiles/Parallel.dir/Single.c.o.requires:

.PHONY : CMakeFiles/Parallel.dir/Single.c.o.requires

CMakeFiles/Parallel.dir/Single.c.o.provides: CMakeFiles/Parallel.dir/Single.c.o.requires
	$(MAKE) -f CMakeFiles/Parallel.dir/build.make CMakeFiles/Parallel.dir/Single.c.o.provides.build
.PHONY : CMakeFiles/Parallel.dir/Single.c.o.provides

CMakeFiles/Parallel.dir/Single.c.o.provides.build: CMakeFiles/Parallel.dir/Single.c.o


# Object files for target Parallel
Parallel_OBJECTS = \
"CMakeFiles/Parallel.dir/Single.c.o"

# External object files for target Parallel
Parallel_EXTERNAL_OBJECTS =

Parallel.exe: CMakeFiles/Parallel.dir/Single.c.o
Parallel.exe: CMakeFiles/Parallel.dir/build.make
Parallel.exe: CMakeFiles/Parallel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Parallel.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Parallel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Parallel.dir/build: Parallel.exe

.PHONY : CMakeFiles/Parallel.dir/build

CMakeFiles/Parallel.dir/requires: CMakeFiles/Parallel.dir/Single.c.o.requires

.PHONY : CMakeFiles/Parallel.dir/requires

CMakeFiles/Parallel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Parallel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Parallel.dir/clean

CMakeFiles/Parallel.dir/depend:
	cd "/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/ras/5 course/Second/Parallel" "/cygdrive/c/ras/5 course/Second/Parallel" "/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug" "/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug" "/cygdrive/c/ras/5 course/Second/Parallel/cmake-build-debug/CMakeFiles/Parallel.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Parallel.dir/depend

