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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ch11_strings_clionprj.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ch11_strings_clionprj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ch11_strings_clionprj.dir/flags.make

CMakeFiles/ch11_strings_clionprj.dir/main.c.obj: CMakeFiles/ch11_strings_clionprj.dir/flags.make
CMakeFiles/ch11_strings_clionprj.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ch11_strings_clionprj.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ch11_strings_clionprj.dir\main.c.obj -c C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\main.c

CMakeFiles/ch11_strings_clionprj.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ch11_strings_clionprj.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\main.c > CMakeFiles\ch11_strings_clionprj.dir\main.c.i

CMakeFiles/ch11_strings_clionprj.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ch11_strings_clionprj.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\main.c -o CMakeFiles\ch11_strings_clionprj.dir\main.c.s

# Object files for target ch11_strings_clionprj
ch11_strings_clionprj_OBJECTS = \
"CMakeFiles/ch11_strings_clionprj.dir/main.c.obj"

# External object files for target ch11_strings_clionprj
ch11_strings_clionprj_EXTERNAL_OBJECTS =

ch11_strings_clionprj.exe: CMakeFiles/ch11_strings_clionprj.dir/main.c.obj
ch11_strings_clionprj.exe: CMakeFiles/ch11_strings_clionprj.dir/build.make
ch11_strings_clionprj.exe: CMakeFiles/ch11_strings_clionprj.dir/linklibs.rsp
ch11_strings_clionprj.exe: CMakeFiles/ch11_strings_clionprj.dir/objects1.rsp
ch11_strings_clionprj.exe: CMakeFiles/ch11_strings_clionprj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ch11_strings_clionprj.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ch11_strings_clionprj.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ch11_strings_clionprj.dir/build: ch11_strings_clionprj.exe
.PHONY : CMakeFiles/ch11_strings_clionprj.dir/build

CMakeFiles/ch11_strings_clionprj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ch11_strings_clionprj.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ch11_strings_clionprj.dir/clean

CMakeFiles/ch11_strings_clionprj.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug C:\git\CPractice\CPrimerPlusBook\Ch11Strings\ch11_strings_clionprj\cmake-build-debug\CMakeFiles\ch11_strings_clionprj.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ch11_strings_clionprj.dir/depend

