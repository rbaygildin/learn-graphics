# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macbook/Documents/Education/4_Year/CompGraphics/shading

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug

# Utility rule file for shading_autogen.

# Include the progress variables for this target.
include CMakeFiles/shading_autogen.dir/progress.make

CMakeFiles/shading_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target shading"
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E cmake_autogen /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug/CMakeFiles/shading_autogen.dir/ Debug

shading_autogen: CMakeFiles/shading_autogen
shading_autogen: CMakeFiles/shading_autogen.dir/build.make

.PHONY : shading_autogen

# Rule to build all files generated by this target.
CMakeFiles/shading_autogen.dir/build: shading_autogen

.PHONY : CMakeFiles/shading_autogen.dir/build

CMakeFiles/shading_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shading_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shading_autogen.dir/clean

CMakeFiles/shading_autogen.dir/depend:
	cd /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macbook/Documents/Education/4_Year/CompGraphics/shading /Users/macbook/Documents/Education/4_Year/CompGraphics/shading /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug /Users/macbook/Documents/Education/4_Year/CompGraphics/shading/cmake-build-debug/CMakeFiles/shading_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shading_autogen.dir/depend

