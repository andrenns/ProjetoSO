# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "/Users/Tadeu17/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.5107.21/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/Tadeu17/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.5107.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Tadeu17/Desktop/UMA/ProjetoSO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProjetoSO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjetoSO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjetoSO.dir/flags.make

CMakeFiles/ProjetoSO.dir/Monitor.c.o: CMakeFiles/ProjetoSO.dir/flags.make
CMakeFiles/ProjetoSO.dir/Monitor.c.o: ../Monitor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ProjetoSO.dir/Monitor.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProjetoSO.dir/Monitor.c.o   -c /Users/Tadeu17/Desktop/UMA/ProjetoSO/Monitor.c

CMakeFiles/ProjetoSO.dir/Monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProjetoSO.dir/Monitor.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Tadeu17/Desktop/UMA/ProjetoSO/Monitor.c > CMakeFiles/ProjetoSO.dir/Monitor.c.i

CMakeFiles/ProjetoSO.dir/Monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProjetoSO.dir/Monitor.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Tadeu17/Desktop/UMA/ProjetoSO/Monitor.c -o CMakeFiles/ProjetoSO.dir/Monitor.c.s

CMakeFiles/ProjetoSO.dir/util.c.o: CMakeFiles/ProjetoSO.dir/flags.make
CMakeFiles/ProjetoSO.dir/util.c.o: ../util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ProjetoSO.dir/util.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProjetoSO.dir/util.c.o   -c /Users/Tadeu17/Desktop/UMA/ProjetoSO/util.c

CMakeFiles/ProjetoSO.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProjetoSO.dir/util.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Tadeu17/Desktop/UMA/ProjetoSO/util.c > CMakeFiles/ProjetoSO.dir/util.c.i

CMakeFiles/ProjetoSO.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProjetoSO.dir/util.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Tadeu17/Desktop/UMA/ProjetoSO/util.c -o CMakeFiles/ProjetoSO.dir/util.c.s

CMakeFiles/ProjetoSO.dir/Simulator.c.o: CMakeFiles/ProjetoSO.dir/flags.make
CMakeFiles/ProjetoSO.dir/Simulator.c.o: ../Simulator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ProjetoSO.dir/Simulator.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProjetoSO.dir/Simulator.c.o   -c /Users/Tadeu17/Desktop/UMA/ProjetoSO/Simulator.c

CMakeFiles/ProjetoSO.dir/Simulator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProjetoSO.dir/Simulator.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Tadeu17/Desktop/UMA/ProjetoSO/Simulator.c > CMakeFiles/ProjetoSO.dir/Simulator.c.i

CMakeFiles/ProjetoSO.dir/Simulator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProjetoSO.dir/Simulator.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Tadeu17/Desktop/UMA/ProjetoSO/Simulator.c -o CMakeFiles/ProjetoSO.dir/Simulator.c.s

# Object files for target ProjetoSO
ProjetoSO_OBJECTS = \
"CMakeFiles/ProjetoSO.dir/Monitor.c.o" \
"CMakeFiles/ProjetoSO.dir/util.c.o" \
"CMakeFiles/ProjetoSO.dir/Simulator.c.o"

# External object files for target ProjetoSO
ProjetoSO_EXTERNAL_OBJECTS =

ProjetoSO: CMakeFiles/ProjetoSO.dir/Monitor.c.o
ProjetoSO: CMakeFiles/ProjetoSO.dir/util.c.o
ProjetoSO: CMakeFiles/ProjetoSO.dir/Simulator.c.o
ProjetoSO: CMakeFiles/ProjetoSO.dir/build.make
ProjetoSO: CMakeFiles/ProjetoSO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ProjetoSO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjetoSO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjetoSO.dir/build: ProjetoSO

.PHONY : CMakeFiles/ProjetoSO.dir/build

CMakeFiles/ProjetoSO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjetoSO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjetoSO.dir/clean

CMakeFiles/ProjetoSO.dir/depend:
	cd /Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Tadeu17/Desktop/UMA/ProjetoSO /Users/Tadeu17/Desktop/UMA/ProjetoSO /Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug /Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug /Users/Tadeu17/Desktop/UMA/ProjetoSO/cmake-build-debug/CMakeFiles/ProjetoSO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjetoSO.dir/depend

