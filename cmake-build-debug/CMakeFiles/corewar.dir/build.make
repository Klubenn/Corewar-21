# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/etuffleb/21/Corewar-21

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/etuffleb/21/Corewar-21/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/corewar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/corewar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/corewar.dir/flags.make

CMakeFiles/corewar.dir/src/to_bytecode.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/src/to_bytecode.c.o: ../src/to_bytecode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/corewar.dir/src/to_bytecode.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/src/to_bytecode.c.o   -c /Users/etuffleb/21/Corewar-21/src/to_bytecode.c

CMakeFiles/corewar.dir/src/to_bytecode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/src/to_bytecode.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/etuffleb/21/Corewar-21/src/to_bytecode.c > CMakeFiles/corewar.dir/src/to_bytecode.c.i

CMakeFiles/corewar.dir/src/to_bytecode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/src/to_bytecode.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/etuffleb/21/Corewar-21/src/to_bytecode.c -o CMakeFiles/corewar.dir/src/to_bytecode.c.s

CMakeFiles/corewar.dir/src/asm.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/src/asm.c.o: ../src/asm.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/corewar.dir/src/asm.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/src/asm.c.o   -c /Users/etuffleb/21/Corewar-21/src/asm.c

CMakeFiles/corewar.dir/src/asm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/src/asm.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/etuffleb/21/Corewar-21/src/asm.c > CMakeFiles/corewar.dir/src/asm.c.i

CMakeFiles/corewar.dir/src/asm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/src/asm.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/etuffleb/21/Corewar-21/src/asm.c -o CMakeFiles/corewar.dir/src/asm.c.s

CMakeFiles/corewar.dir/src/labels.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/src/labels.c.o: ../src/labels.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/corewar.dir/src/labels.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/src/labels.c.o   -c /Users/etuffleb/21/Corewar-21/src/labels.c

CMakeFiles/corewar.dir/src/labels.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/src/labels.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/etuffleb/21/Corewar-21/src/labels.c > CMakeFiles/corewar.dir/src/labels.c.i

CMakeFiles/corewar.dir/src/labels.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/src/labels.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/etuffleb/21/Corewar-21/src/labels.c -o CMakeFiles/corewar.dir/src/labels.c.s

CMakeFiles/corewar.dir/src/checks.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/src/checks.c.o: ../src/checks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/corewar.dir/src/checks.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/src/checks.c.o   -c /Users/etuffleb/21/Corewar-21/src/checks.c

CMakeFiles/corewar.dir/src/checks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/src/checks.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/etuffleb/21/Corewar-21/src/checks.c > CMakeFiles/corewar.dir/src/checks.c.i

CMakeFiles/corewar.dir/src/checks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/src/checks.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/etuffleb/21/Corewar-21/src/checks.c -o CMakeFiles/corewar.dir/src/checks.c.s

CMakeFiles/corewar.dir/src/op.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/src/op.c.o: ../src/op.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/corewar.dir/src/op.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/src/op.c.o   -c /Users/etuffleb/21/Corewar-21/src/op.c

CMakeFiles/corewar.dir/src/op.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/src/op.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/etuffleb/21/Corewar-21/src/op.c > CMakeFiles/corewar.dir/src/op.c.i

CMakeFiles/corewar.dir/src/op.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/src/op.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/etuffleb/21/Corewar-21/src/op.c -o CMakeFiles/corewar.dir/src/op.c.s

# Object files for target corewar
corewar_OBJECTS = \
"CMakeFiles/corewar.dir/src/to_bytecode.c.o" \
"CMakeFiles/corewar.dir/src/asm.c.o" \
"CMakeFiles/corewar.dir/src/labels.c.o" \
"CMakeFiles/corewar.dir/src/checks.c.o" \
"CMakeFiles/corewar.dir/src/op.c.o"

# External object files for target corewar
corewar_EXTERNAL_OBJECTS =

corewar: CMakeFiles/corewar.dir/src/to_bytecode.c.o
corewar: CMakeFiles/corewar.dir/src/asm.c.o
corewar: CMakeFiles/corewar.dir/src/labels.c.o
corewar: CMakeFiles/corewar.dir/src/checks.c.o
corewar: CMakeFiles/corewar.dir/src/op.c.o
corewar: CMakeFiles/corewar.dir/build.make
corewar: /Users/gtristan/CLionProjects/corewar/libft/libft.a
corewar: CMakeFiles/corewar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable corewar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/corewar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/corewar.dir/build: corewar

.PHONY : CMakeFiles/corewar.dir/build

CMakeFiles/corewar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/corewar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/corewar.dir/clean

CMakeFiles/corewar.dir/depend:
	cd /Users/etuffleb/21/Corewar-21/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/etuffleb/21/Corewar-21 /Users/etuffleb/21/Corewar-21 /Users/etuffleb/21/Corewar-21/cmake-build-debug /Users/etuffleb/21/Corewar-21/cmake-build-debug /Users/etuffleb/21/Corewar-21/cmake-build-debug/CMakeFiles/corewar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/corewar.dir/depend

