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
CMAKE_SOURCE_DIR = D:\Lab\ads\homework\hw3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Lab\ads\homework\hw3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hw3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw3.dir/flags.make

CMakeFiles/hw3.dir/main.cpp.obj: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/main.cpp.obj: D:/Lab/ads/homework/hw3/main.cpp
CMakeFiles/hw3.dir/main.cpp.obj: CMakeFiles/hw3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Lab\ads\homework\hw3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw3.dir/main.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw3.dir/main.cpp.obj -MF CMakeFiles\hw3.dir\main.cpp.obj.d -o CMakeFiles\hw3.dir\main.cpp.obj -c D:\Lab\ads\homework\hw3\main.cpp

CMakeFiles/hw3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/main.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Lab\ads\homework\hw3\main.cpp > CMakeFiles\hw3.dir\main.cpp.i

CMakeFiles/hw3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/main.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Lab\ads\homework\hw3\main.cpp -o CMakeFiles\hw3.dir\main.cpp.s

CMakeFiles/hw3.dir/BloomFilter.cpp.obj: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/BloomFilter.cpp.obj: D:/Lab/ads/homework/hw3/BloomFilter.cpp
CMakeFiles/hw3.dir/BloomFilter.cpp.obj: CMakeFiles/hw3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Lab\ads\homework\hw3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw3.dir/BloomFilter.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw3.dir/BloomFilter.cpp.obj -MF CMakeFiles\hw3.dir\BloomFilter.cpp.obj.d -o CMakeFiles\hw3.dir\BloomFilter.cpp.obj -c D:\Lab\ads\homework\hw3\BloomFilter.cpp

CMakeFiles/hw3.dir/BloomFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/BloomFilter.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Lab\ads\homework\hw3\BloomFilter.cpp > CMakeFiles\hw3.dir\BloomFilter.cpp.i

CMakeFiles/hw3.dir/BloomFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/BloomFilter.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Lab\ads\homework\hw3\BloomFilter.cpp -o CMakeFiles\hw3.dir\BloomFilter.cpp.s

# Object files for target hw3
hw3_OBJECTS = \
"CMakeFiles/hw3.dir/main.cpp.obj" \
"CMakeFiles/hw3.dir/BloomFilter.cpp.obj"

# External object files for target hw3
hw3_EXTERNAL_OBJECTS =

hw3.exe: CMakeFiles/hw3.dir/main.cpp.obj
hw3.exe: CMakeFiles/hw3.dir/BloomFilter.cpp.obj
hw3.exe: CMakeFiles/hw3.dir/build.make
hw3.exe: CMakeFiles/hw3.dir/linklibs.rsp
hw3.exe: CMakeFiles/hw3.dir/objects1.rsp
hw3.exe: CMakeFiles/hw3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Lab\ads\homework\hw3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hw3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw3.dir/build: hw3.exe
.PHONY : CMakeFiles/hw3.dir/build

CMakeFiles/hw3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw3.dir/clean

CMakeFiles/hw3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Lab\ads\homework\hw3 D:\Lab\ads\homework\hw3 D:\Lab\ads\homework\hw3\cmake-build-debug D:\Lab\ads\homework\hw3\cmake-build-debug D:\Lab\ads\homework\hw3\cmake-build-debug\CMakeFiles\hw3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw3.dir/depend

