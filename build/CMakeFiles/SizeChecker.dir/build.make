# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.9/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.9/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hiyu/Tools/TSVRenderer/TSVRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hiyu/Tools/TSVRenderer/TSVRenderer/build

# Include any dependencies generated for this target.
include CMakeFiles/SizeChecker.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SizeChecker.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SizeChecker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SizeChecker.dir/flags.make

CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o: CMakeFiles/SizeChecker.dir/flags.make
CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o: /Users/hiyu/Tools/TSVRenderer/TSVRenderer/test/size_checker.cpp
CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o: CMakeFiles/SizeChecker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hiyu/Tools/TSVRenderer/TSVRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o -MF CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o.d -o CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o -c /Users/hiyu/Tools/TSVRenderer/TSVRenderer/test/size_checker.cpp

CMakeFiles/SizeChecker.dir/test/size_checker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SizeChecker.dir/test/size_checker.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hiyu/Tools/TSVRenderer/TSVRenderer/test/size_checker.cpp > CMakeFiles/SizeChecker.dir/test/size_checker.cpp.i

CMakeFiles/SizeChecker.dir/test/size_checker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SizeChecker.dir/test/size_checker.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hiyu/Tools/TSVRenderer/TSVRenderer/test/size_checker.cpp -o CMakeFiles/SizeChecker.dir/test/size_checker.cpp.s

# Object files for target SizeChecker
SizeChecker_OBJECTS = \
"CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o"

# External object files for target SizeChecker
SizeChecker_EXTERNAL_OBJECTS =

SizeChecker: CMakeFiles/SizeChecker.dir/test/size_checker.cpp.o
SizeChecker: CMakeFiles/SizeChecker.dir/build.make
SizeChecker: libs/libReflectCore.0.1.0.dylib
SizeChecker: /opt/homebrew/opt/qt@5/lib/QtWidgets.framework/QtWidgets
SizeChecker: /opt/homebrew/opt/qt@5/lib/QtGui.framework/QtGui
SizeChecker: /opt/homebrew/opt/qt@5/lib/QtCore.framework/QtCore
SizeChecker: libs/libZisc.0.5.0.dylib
SizeChecker: CMakeFiles/SizeChecker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hiyu/Tools/TSVRenderer/TSVRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SizeChecker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SizeChecker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SizeChecker.dir/build: SizeChecker
.PHONY : CMakeFiles/SizeChecker.dir/build

CMakeFiles/SizeChecker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SizeChecker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SizeChecker.dir/clean

CMakeFiles/SizeChecker.dir/depend:
	cd /Users/hiyu/Tools/TSVRenderer/TSVRenderer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hiyu/Tools/TSVRenderer/TSVRenderer /Users/hiyu/Tools/TSVRenderer/TSVRenderer /Users/hiyu/Tools/TSVRenderer/TSVRenderer/build /Users/hiyu/Tools/TSVRenderer/TSVRenderer/build /Users/hiyu/Tools/TSVRenderer/TSVRenderer/build/CMakeFiles/SizeChecker.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SizeChecker.dir/depend

