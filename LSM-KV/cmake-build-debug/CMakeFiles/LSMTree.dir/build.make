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
CMAKE_SOURCE_DIR = D:\wsl\LSMTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\wsl\LSMTree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LSMTree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LSMTree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LSMTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LSMTree.dir/flags.make

CMakeFiles/LSMTree.dir/correctness.cc.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/correctness.cc.obj: D:/wsl/LSMTree/correctness.cc
CMakeFiles/LSMTree.dir/correctness.cc.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LSMTree.dir/correctness.cc.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/correctness.cc.obj -MF CMakeFiles\LSMTree.dir\correctness.cc.obj.d -o CMakeFiles\LSMTree.dir\correctness.cc.obj -c D:\wsl\LSMTree\correctness.cc

CMakeFiles/LSMTree.dir/correctness.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/correctness.cc.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\correctness.cc > CMakeFiles\LSMTree.dir\correctness.cc.i

CMakeFiles/LSMTree.dir/correctness.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/correctness.cc.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\correctness.cc -o CMakeFiles\LSMTree.dir\correctness.cc.s

CMakeFiles/LSMTree.dir/kvstore.cc.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/kvstore.cc.obj: D:/wsl/LSMTree/kvstore.cc
CMakeFiles/LSMTree.dir/kvstore.cc.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LSMTree.dir/kvstore.cc.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/kvstore.cc.obj -MF CMakeFiles\LSMTree.dir\kvstore.cc.obj.d -o CMakeFiles\LSMTree.dir\kvstore.cc.obj -c D:\wsl\LSMTree\kvstore.cc

CMakeFiles/LSMTree.dir/kvstore.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/kvstore.cc.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\kvstore.cc > CMakeFiles\LSMTree.dir\kvstore.cc.i

CMakeFiles/LSMTree.dir/kvstore.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/kvstore.cc.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\kvstore.cc -o CMakeFiles\LSMTree.dir\kvstore.cc.s

CMakeFiles/LSMTree.dir/skipList.cpp.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/skipList.cpp.obj: D:/wsl/LSMTree/skipList.cpp
CMakeFiles/LSMTree.dir/skipList.cpp.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LSMTree.dir/skipList.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/skipList.cpp.obj -MF CMakeFiles\LSMTree.dir\skipList.cpp.obj.d -o CMakeFiles\LSMTree.dir\skipList.cpp.obj -c D:\wsl\LSMTree\skipList.cpp

CMakeFiles/LSMTree.dir/skipList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/skipList.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\skipList.cpp > CMakeFiles\LSMTree.dir\skipList.cpp.i

CMakeFiles/LSMTree.dir/skipList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/skipList.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\skipList.cpp -o CMakeFiles\LSMTree.dir\skipList.cpp.s

CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj: D:/wsl/LSMTree/bloomFilter.cpp
CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj -MF CMakeFiles\LSMTree.dir\bloomFilter.cpp.obj.d -o CMakeFiles\LSMTree.dir\bloomFilter.cpp.obj -c D:\wsl\LSMTree\bloomFilter.cpp

CMakeFiles/LSMTree.dir/bloomFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/bloomFilter.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\bloomFilter.cpp > CMakeFiles\LSMTree.dir\bloomFilter.cpp.i

CMakeFiles/LSMTree.dir/bloomFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/bloomFilter.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\bloomFilter.cpp -o CMakeFiles\LSMTree.dir\bloomFilter.cpp.s

CMakeFiles/LSMTree.dir/SSTable.cpp.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/SSTable.cpp.obj: D:/wsl/LSMTree/SSTable.cpp
CMakeFiles/LSMTree.dir/SSTable.cpp.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/LSMTree.dir/SSTable.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/SSTable.cpp.obj -MF CMakeFiles\LSMTree.dir\SSTable.cpp.obj.d -o CMakeFiles\LSMTree.dir\SSTable.cpp.obj -c D:\wsl\LSMTree\SSTable.cpp

CMakeFiles/LSMTree.dir/SSTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/SSTable.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\SSTable.cpp > CMakeFiles\LSMTree.dir\SSTable.cpp.i

CMakeFiles/LSMTree.dir/SSTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/SSTable.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\SSTable.cpp -o CMakeFiles\LSMTree.dir\SSTable.cpp.s

CMakeFiles/LSMTree.dir/cache.cpp.obj: CMakeFiles/LSMTree.dir/flags.make
CMakeFiles/LSMTree.dir/cache.cpp.obj: D:/wsl/LSMTree/cache.cpp
CMakeFiles/LSMTree.dir/cache.cpp.obj: CMakeFiles/LSMTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/LSMTree.dir/cache.cpp.obj"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LSMTree.dir/cache.cpp.obj -MF CMakeFiles\LSMTree.dir\cache.cpp.obj.d -o CMakeFiles\LSMTree.dir\cache.cpp.obj -c D:\wsl\LSMTree\cache.cpp

CMakeFiles/LSMTree.dir/cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSMTree.dir/cache.cpp.i"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wsl\LSMTree\cache.cpp > CMakeFiles\LSMTree.dir\cache.cpp.i

CMakeFiles/LSMTree.dir/cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSMTree.dir/cache.cpp.s"
	D:\cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wsl\LSMTree\cache.cpp -o CMakeFiles\LSMTree.dir\cache.cpp.s

# Object files for target LSMTree
LSMTree_OBJECTS = \
"CMakeFiles/LSMTree.dir/correctness.cc.obj" \
"CMakeFiles/LSMTree.dir/kvstore.cc.obj" \
"CMakeFiles/LSMTree.dir/skipList.cpp.obj" \
"CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj" \
"CMakeFiles/LSMTree.dir/SSTable.cpp.obj" \
"CMakeFiles/LSMTree.dir/cache.cpp.obj"

# External object files for target LSMTree
LSMTree_EXTERNAL_OBJECTS =

LSMTree.exe: CMakeFiles/LSMTree.dir/correctness.cc.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/kvstore.cc.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/skipList.cpp.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/bloomFilter.cpp.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/SSTable.cpp.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/cache.cpp.obj
LSMTree.exe: CMakeFiles/LSMTree.dir/build.make
LSMTree.exe: CMakeFiles/LSMTree.dir/linklibs.rsp
LSMTree.exe: CMakeFiles/LSMTree.dir/objects1.rsp
LSMTree.exe: CMakeFiles/LSMTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\wsl\LSMTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable LSMTree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LSMTree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LSMTree.dir/build: LSMTree.exe
.PHONY : CMakeFiles/LSMTree.dir/build

CMakeFiles/LSMTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LSMTree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LSMTree.dir/clean

CMakeFiles/LSMTree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\wsl\LSMTree D:\wsl\LSMTree D:\wsl\LSMTree\cmake-build-debug D:\wsl\LSMTree\cmake-build-debug D:\wsl\LSMTree\cmake-build-debug\CMakeFiles\LSMTree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LSMTree.dir/depend

