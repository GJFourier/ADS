# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\G.J.Fourier\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\G.J.Fourier\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Lab\ads\homework\hw11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Lab\ads\homework\hw11\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw11.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hw11.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw11.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw11.dir/flags.make

CMakeFiles/hw11.dir/main.cpp.obj: CMakeFiles/hw11.dir/flags.make
CMakeFiles/hw11.dir/main.cpp.obj: D:/Lab/ads/homework/hw11/main.cpp
CMakeFiles/hw11.dir/main.cpp.obj: CMakeFiles/hw11.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Lab\ads\homework\hw11\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw11.dir/main.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw11.dir/main.cpp.obj -MF CMakeFiles\hw11.dir\main.cpp.obj.d -o CMakeFiles\hw11.dir\main.cpp.obj -c D:\Lab\ads\homework\hw11\main.cpp

CMakeFiles/hw11.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw11.dir/main.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Lab\ads\homework\hw11\main.cpp > CMakeFiles\hw11.dir\main.cpp.i

CMakeFiles/hw11.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw11.dir/main.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Lab\ads\homework\hw11\main.cpp -o CMakeFiles\hw11.dir\main.cpp.s

# Object files for target hw11
hw11_OBJECTS = \
"CMakeFiles/hw11.dir/main.cpp.obj"

# External object files for target hw11
hw11_EXTERNAL_OBJECTS =

hw11.exe: CMakeFiles/hw11.dir/main.cpp.obj
hw11.exe: CMakeFiles/hw11.dir/build.make
hw11.exe: CMakeFiles/hw11.dir/linklibs.rsp
hw11.exe: CMakeFiles/hw11.dir/objects1.rsp
hw11.exe: CMakeFiles/hw11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Lab\ads\homework\hw11\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw11.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw11.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw11.dir/build: hw11.exe
.PHONY : CMakeFiles/hw11.dir/build

CMakeFiles/hw11.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw11.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw11.dir/clean

CMakeFiles/hw11.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Lab\ads\homework\hw11 D:\Lab\ads\homework\hw11 D:\Lab\ads\homework\hw11\cmake-build-debug D:\Lab\ads\homework\hw11\cmake-build-debug D:\Lab\ads\homework\hw11\cmake-build-debug\CMakeFiles\hw11.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw11.dir/depend

