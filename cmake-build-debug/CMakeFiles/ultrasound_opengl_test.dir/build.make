# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/82/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/82/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hanwen/CLionProjects/ultrasound_opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ultrasound_opengl_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ultrasound_opengl_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ultrasound_opengl_test.dir/flags.make

CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o: CMakeFiles/ultrasound_opengl_test.dir/flags.make
CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o -c /home/hanwen/CLionProjects/ultrasound_opengl/main.cpp

CMakeFiles/ultrasound_opengl_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ultrasound_opengl_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hanwen/CLionProjects/ultrasound_opengl/main.cpp > CMakeFiles/ultrasound_opengl_test.dir/main.cpp.i

CMakeFiles/ultrasound_opengl_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ultrasound_opengl_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hanwen/CLionProjects/ultrasound_opengl/main.cpp -o CMakeFiles/ultrasound_opengl_test.dir/main.cpp.s

# Object files for target ultrasound_opengl_test
ultrasound_opengl_test_OBJECTS = \
"CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o"

# External object files for target ultrasound_opengl_test
ultrasound_opengl_test_EXTERNAL_OBJECTS =

ultrasound_opengl_test: CMakeFiles/ultrasound_opengl_test.dir/main.cpp.o
ultrasound_opengl_test: CMakeFiles/ultrasound_opengl_test.dir/build.make
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libglut.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libXmu.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libXi.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libOpenGL.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libGLX.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libGLU.so
ultrasound_opengl_test: libultrasound_opengl_lib.so
ultrasound_opengl_test: /usr/lib/gcc/x86_64-linux-gnu/7/libgomp.so
ultrasound_opengl_test: /usr/lib/x86_64-linux-gnu/libpthread.so
ultrasound_opengl_test: CMakeFiles/ultrasound_opengl_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ultrasound_opengl_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ultrasound_opengl_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ultrasound_opengl_test.dir/build: ultrasound_opengl_test

.PHONY : CMakeFiles/ultrasound_opengl_test.dir/build

CMakeFiles/ultrasound_opengl_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ultrasound_opengl_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ultrasound_opengl_test.dir/clean

CMakeFiles/ultrasound_opengl_test.dir/depend:
	cd /home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hanwen/CLionProjects/ultrasound_opengl /home/hanwen/CLionProjects/ultrasound_opengl /home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug /home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug /home/hanwen/CLionProjects/ultrasound_opengl/cmake-build-debug/CMakeFiles/ultrasound_opengl_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ultrasound_opengl_test.dir/depend

