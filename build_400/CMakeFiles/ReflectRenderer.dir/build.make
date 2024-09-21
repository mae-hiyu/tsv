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
CMAKE_SOURCE_DIR = /Users/hiyu/renderer/TSVRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hiyu/renderer/TSVRenderer/build_400

# Include any dependencies generated for this target.
include CMakeFiles/ReflectRenderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ReflectRenderer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ReflectRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ReflectRenderer.dir/flags.make

CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o: CMakeFiles/ReflectRenderer.dir/flags.make
CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o: /Users/hiyu/renderer/TSVRenderer/source/reflect_renderer/renderer.cpp
CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o: CMakeFiles/ReflectRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hiyu/renderer/TSVRenderer/build_400/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o -MF CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o.d -o CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o -c /Users/hiyu/renderer/TSVRenderer/source/reflect_renderer/renderer.cpp

CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hiyu/renderer/TSVRenderer/source/reflect_renderer/renderer.cpp > CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.i

CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hiyu/renderer/TSVRenderer/source/reflect_renderer/renderer.cpp -o CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.s

# Object files for target ReflectRenderer
ReflectRenderer_OBJECTS = \
"CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o"

# External object files for target ReflectRenderer
ReflectRenderer_EXTERNAL_OBJECTS =

libs/libReflectRenderer.0.1.0.dylib: CMakeFiles/ReflectRenderer.dir/source/reflect_renderer/renderer.cpp.o
libs/libReflectRenderer.0.1.0.dylib: CMakeFiles/ReflectRenderer.dir/build.make
libs/libReflectRenderer.0.1.0.dylib: libs/libReflectCore.0.1.0.dylib
libs/libReflectRenderer.0.1.0.dylib: /opt/homebrew/Cellar/qt@5/5.15.12/lib/QtWidgets.framework/QtWidgets
libs/libReflectRenderer.0.1.0.dylib: /opt/homebrew/Cellar/qt@5/5.15.12/lib/QtGui.framework/QtGui
libs/libReflectRenderer.0.1.0.dylib: /opt/homebrew/Cellar/qt@5/5.15.12/lib/QtCore.framework/QtCore
libs/libReflectRenderer.0.1.0.dylib: libs/libZisc.0.5.0.dylib
libs/libReflectRenderer.0.1.0.dylib: CMakeFiles/ReflectRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hiyu/renderer/TSVRenderer/build_400/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libs/libReflectRenderer.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReflectRenderer.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libs/libReflectRenderer.0.1.0.dylib libs/libReflectRenderer.0.dylib libs/libReflectRenderer.dylib

libs/libReflectRenderer.0.dylib: libs/libReflectRenderer.0.1.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libs/libReflectRenderer.0.dylib

libs/libReflectRenderer.dylib: libs/libReflectRenderer.0.1.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libs/libReflectRenderer.dylib

# Rule to build all files generated by this target.
CMakeFiles/ReflectRenderer.dir/build: libs/libReflectRenderer.dylib
.PHONY : CMakeFiles/ReflectRenderer.dir/build

CMakeFiles/ReflectRenderer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ReflectRenderer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ReflectRenderer.dir/clean

CMakeFiles/ReflectRenderer.dir/depend:
	cd /Users/hiyu/renderer/TSVRenderer/build_400 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hiyu/renderer/TSVRenderer /Users/hiyu/renderer/TSVRenderer /Users/hiyu/renderer/TSVRenderer/build_400 /Users/hiyu/renderer/TSVRenderer/build_400 /Users/hiyu/renderer/TSVRenderer/build_400/CMakeFiles/ReflectRenderer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ReflectRenderer.dir/depend

