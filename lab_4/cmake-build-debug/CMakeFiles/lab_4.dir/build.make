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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/a/mai_stuff/Computer_grafics/lab_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab_4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab_4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab_4.dir/flags.make

CMakeFiles/lab_4.dir/main.cpp.o: CMakeFiles/lab_4.dir/flags.make
CMakeFiles/lab_4.dir/main.cpp.o: ../main.cpp
CMakeFiles/lab_4.dir/main.cpp.o: CMakeFiles/lab_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab_4.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab_4.dir/main.cpp.o -MF CMakeFiles/lab_4.dir/main.cpp.o.d -o CMakeFiles/lab_4.dir/main.cpp.o -c /mnt/a/mai_stuff/Computer_grafics/lab_4/main.cpp

CMakeFiles/lab_4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_4.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/a/mai_stuff/Computer_grafics/lab_4/main.cpp > CMakeFiles/lab_4.dir/main.cpp.i

CMakeFiles/lab_4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_4.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/a/mai_stuff/Computer_grafics/lab_4/main.cpp -o CMakeFiles/lab_4.dir/main.cpp.s

# Object files for target lab_4
lab_4_OBJECTS = \
"CMakeFiles/lab_4.dir/main.cpp.o"

# External object files for target lab_4
lab_4_EXTERNAL_OBJECTS =

lab_4: CMakeFiles/lab_4.dir/main.cpp.o
lab_4: CMakeFiles/lab_4.dir/build.make
lab_4: /usr/lib/x86_64-linux-gnu/libGLEW.so
lab_4: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
lab_4: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
lab_4: /usr/lib/x86_64-linux-gnu/libGLX.so
lab_4: /usr/lib/x86_64-linux-gnu/libOpenGL.so
lab_4: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
lab_4: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
lab_4: CMakeFiles/lab_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab_4.dir/build: lab_4
.PHONY : CMakeFiles/lab_4.dir/build

CMakeFiles/lab_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab_4.dir/clean

CMakeFiles/lab_4.dir/depend:
	cd /mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/a/mai_stuff/Computer_grafics/lab_4 /mnt/a/mai_stuff/Computer_grafics/lab_4 /mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug /mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug /mnt/a/mai_stuff/Computer_grafics/lab_4/cmake-build-debug/CMakeFiles/lab_4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab_4.dir/depend

