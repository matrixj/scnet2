# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jmchen/work/scnet2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmchen/work/scnet2

# Include any dependencies generated for this target.
include src/base/CMakeFiles/scnet2_base.dir/depend.make

# Include the progress variables for this target.
include src/base/CMakeFiles/scnet2_base.dir/progress.make

# Include the compile flags for this target's objects.
include src/base/CMakeFiles/scnet2_base.dir/flags.make

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o: src/base/BaseLoop.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/BaseLoop.cc.o -c /home/jmchen/work/scnet2/src/base/BaseLoop.cc

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/BaseLoop.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/BaseLoop.cc > CMakeFiles/scnet2_base.dir/BaseLoop.cc.i

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/BaseLoop.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/BaseLoop.cc -o CMakeFiles/scnet2_base.dir/BaseLoop.cc.s

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o: src/base/Thread.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/Thread.cc.o -c /home/jmchen/work/scnet2/src/base/Thread.cc

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/Thread.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/Thread.cc > CMakeFiles/scnet2_base.dir/Thread.cc.i

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/Thread.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/Thread.cc -o CMakeFiles/scnet2_base.dir/Thread.cc.s

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o: src/base/Timer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/Timer.cc.o -c /home/jmchen/work/scnet2/src/base/Timer.cc

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/Timer.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/Timer.cc > CMakeFiles/scnet2_base.dir/Timer.cc.i

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/Timer.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/Timer.cc -o CMakeFiles/scnet2_base.dir/Timer.cc.s

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/Time.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/Time.cc.o: src/base/Time.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/Time.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/Time.cc.o -c /home/jmchen/work/scnet2/src/base/Time.cc

src/base/CMakeFiles/scnet2_base.dir/Time.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/Time.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/Time.cc > CMakeFiles/scnet2_base.dir/Time.cc.i

src/base/CMakeFiles/scnet2_base.dir/Time.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/Time.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/Time.cc -o CMakeFiles/scnet2_base.dir/Time.cc.s

src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/Time.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o: src/base/Timestamp.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/Timestamp.cc.o -c /home/jmchen/work/scnet2/src/base/Timestamp.cc

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/Timestamp.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/Timestamp.cc > CMakeFiles/scnet2_base.dir/Timestamp.cc.i

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/Timestamp.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/Timestamp.cc -o CMakeFiles/scnet2_base.dir/Timestamp.cc.s

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o: src/base/Channel.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/Channel.cc.o -c /home/jmchen/work/scnet2/src/base/Channel.cc

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/Channel.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/Channel.cc > CMakeFiles/scnet2_base.dir/Channel.cc.i

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/Channel.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/Channel.cc -o CMakeFiles/scnet2_base.dir/Channel.cc.s

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o: src/base/logbuffer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/logbuffer.cc.o -c /home/jmchen/work/scnet2/src/base/logbuffer.cc

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/logbuffer.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/logbuffer.cc > CMakeFiles/scnet2_base.dir/logbuffer.cc.i

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/logbuffer.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/logbuffer.cc -o CMakeFiles/scnet2_base.dir/logbuffer.cc.s

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/logger.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/logger.cc.o: src/base/logger.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/logger.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/logger.cc.o -c /home/jmchen/work/scnet2/src/base/logger.cc

src/base/CMakeFiles/scnet2_base.dir/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/logger.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/logger.cc > CMakeFiles/scnet2_base.dir/logger.cc.i

src/base/CMakeFiles/scnet2_base.dir/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/logger.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/logger.cc -o CMakeFiles/scnet2_base.dir/logger.cc.s

src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/logger.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.provides.build

src/base/CMakeFiles/scnet2_base.dir/condition.cc.o: src/base/CMakeFiles/scnet2_base.dir/flags.make
src/base/CMakeFiles/scnet2_base.dir/condition.cc.o: src/base/condition.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmchen/work/scnet2/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/base/CMakeFiles/scnet2_base.dir/condition.cc.o"
	cd /home/jmchen/work/scnet2/src/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/scnet2_base.dir/condition.cc.o -c /home/jmchen/work/scnet2/src/base/condition.cc

src/base/CMakeFiles/scnet2_base.dir/condition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scnet2_base.dir/condition.cc.i"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmchen/work/scnet2/src/base/condition.cc > CMakeFiles/scnet2_base.dir/condition.cc.i

src/base/CMakeFiles/scnet2_base.dir/condition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scnet2_base.dir/condition.cc.s"
	cd /home/jmchen/work/scnet2/src/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmchen/work/scnet2/src/base/condition.cc -o CMakeFiles/scnet2_base.dir/condition.cc.s

src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.requires:
.PHONY : src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.requires

src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.provides: src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.provides.build
.PHONY : src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.provides

src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.provides.build: src/base/CMakeFiles/scnet2_base.dir/condition.cc.o
.PHONY : src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.provides.build

# Object files for target scnet2_base
scnet2_base_OBJECTS = \
"CMakeFiles/scnet2_base.dir/BaseLoop.cc.o" \
"CMakeFiles/scnet2_base.dir/Thread.cc.o" \
"CMakeFiles/scnet2_base.dir/Timer.cc.o" \
"CMakeFiles/scnet2_base.dir/Time.cc.o" \
"CMakeFiles/scnet2_base.dir/Timestamp.cc.o" \
"CMakeFiles/scnet2_base.dir/Channel.cc.o" \
"CMakeFiles/scnet2_base.dir/logbuffer.cc.o" \
"CMakeFiles/scnet2_base.dir/logger.cc.o" \
"CMakeFiles/scnet2_base.dir/condition.cc.o"

# External object files for target scnet2_base
scnet2_base_EXTERNAL_OBJECTS =

lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/Time.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/logger.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/condition.cc.o
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/build.make
lib/libscnet2_base.a: src/base/CMakeFiles/scnet2_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libscnet2_base.a"
	cd /home/jmchen/work/scnet2/src/base && $(CMAKE_COMMAND) -P CMakeFiles/scnet2_base.dir/cmake_clean_target.cmake
	cd /home/jmchen/work/scnet2/src/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scnet2_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/base/CMakeFiles/scnet2_base.dir/build: lib/libscnet2_base.a
.PHONY : src/base/CMakeFiles/scnet2_base.dir/build

src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/BaseLoop.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/Thread.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/Timer.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/Time.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/Timestamp.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/Channel.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/logbuffer.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/logger.cc.o.requires
src/base/CMakeFiles/scnet2_base.dir/requires: src/base/CMakeFiles/scnet2_base.dir/condition.cc.o.requires
.PHONY : src/base/CMakeFiles/scnet2_base.dir/requires

src/base/CMakeFiles/scnet2_base.dir/clean:
	cd /home/jmchen/work/scnet2/src/base && $(CMAKE_COMMAND) -P CMakeFiles/scnet2_base.dir/cmake_clean.cmake
.PHONY : src/base/CMakeFiles/scnet2_base.dir/clean

src/base/CMakeFiles/scnet2_base.dir/depend:
	cd /home/jmchen/work/scnet2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmchen/work/scnet2 /home/jmchen/work/scnet2/src/base /home/jmchen/work/scnet2 /home/jmchen/work/scnet2/src/base /home/jmchen/work/scnet2/src/base/CMakeFiles/scnet2_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/base/CMakeFiles/scnet2_base.dir/depend
