# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "D:\Program_Files\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program_Files\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/assembler.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/assembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assembler.dir/flags.make

CMakeFiles/assembler.dir/src/parser.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/parser.cpp.obj: CMakeFiles/assembler.dir/includes_CXX.rsp
CMakeFiles/assembler.dir/src/parser.cpp.obj: ../src/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assembler.dir/src/parser.cpp.obj"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\parser.cpp.obj -c E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\parser.cpp

CMakeFiles/assembler.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/parser.cpp.i"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\parser.cpp > CMakeFiles\assembler.dir\src\parser.cpp.i

CMakeFiles/assembler.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/parser.cpp.s"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\parser.cpp -o CMakeFiles\assembler.dir\src\parser.cpp.s

CMakeFiles/assembler.dir/src/codegen.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/codegen.cpp.obj: CMakeFiles/assembler.dir/includes_CXX.rsp
CMakeFiles/assembler.dir/src/codegen.cpp.obj: ../src/codegen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/assembler.dir/src/codegen.cpp.obj"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\codegen.cpp.obj -c E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\codegen.cpp

CMakeFiles/assembler.dir/src/codegen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/codegen.cpp.i"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\codegen.cpp > CMakeFiles\assembler.dir\src\codegen.cpp.i

CMakeFiles/assembler.dir/src/codegen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/codegen.cpp.s"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\codegen.cpp -o CMakeFiles\assembler.dir\src\codegen.cpp.s

CMakeFiles/assembler.dir/src/symbol_table.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/symbol_table.cpp.obj: CMakeFiles/assembler.dir/includes_CXX.rsp
CMakeFiles/assembler.dir/src/symbol_table.cpp.obj: ../src/symbol_table.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/assembler.dir/src/symbol_table.cpp.obj"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\symbol_table.cpp.obj -c E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\symbol_table.cpp

CMakeFiles/assembler.dir/src/symbol_table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/symbol_table.cpp.i"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\symbol_table.cpp > CMakeFiles\assembler.dir\src\symbol_table.cpp.i

CMakeFiles/assembler.dir/src/symbol_table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/symbol_table.cpp.s"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\symbol_table.cpp -o CMakeFiles\assembler.dir\src\symbol_table.cpp.s

CMakeFiles/assembler.dir/src/main.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/main.cpp.obj: CMakeFiles/assembler.dir/includes_CXX.rsp
CMakeFiles/assembler.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/assembler.dir/src/main.cpp.obj"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\main.cpp.obj -c E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\main.cpp

CMakeFiles/assembler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/main.cpp.i"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\main.cpp > CMakeFiles\assembler.dir\src\main.cpp.i

CMakeFiles/assembler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/main.cpp.s"
	D:\Program_Files\Mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\src\main.cpp -o CMakeFiles\assembler.dir\src\main.cpp.s

# Object files for target assembler
assembler_OBJECTS = \
"CMakeFiles/assembler.dir/src/parser.cpp.obj" \
"CMakeFiles/assembler.dir/src/codegen.cpp.obj" \
"CMakeFiles/assembler.dir/src/symbol_table.cpp.obj" \
"CMakeFiles/assembler.dir/src/main.cpp.obj"

# External object files for target assembler
assembler_EXTERNAL_OBJECTS =

assembler.exe: CMakeFiles/assembler.dir/src/parser.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/codegen.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/symbol_table.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/main.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/build.make
assembler.exe: CMakeFiles/assembler.dir/linklibs.rsp
assembler.exe: CMakeFiles/assembler.dir/objects1.rsp
assembler.exe: CMakeFiles/assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable assembler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\assembler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assembler.dir/build: assembler.exe
.PHONY : CMakeFiles/assembler.dir/build

CMakeFiles/assembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\assembler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/assembler.dir/clean

CMakeFiles/assembler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug E:\projects\Nand2Tetris\nand2tetris\projects\6\assembler\cmake-build-debug\CMakeFiles\assembler.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assembler.dir/depend

