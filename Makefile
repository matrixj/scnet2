# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip
.PHONY : install/strip/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jmchen/work/scnet2/CMakeFiles /home/jmchen/work/scnet2/CMakeFiles/progress.make
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jmchen/work/scnet2/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named scnet2_base

# Build rule for target.
scnet2_base: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 scnet2_base
.PHONY : scnet2_base

# fast build rule for target.
scnet2_base/fast:
	$(MAKE) -f src/base/CMakeFiles/scnet2_base.dir/build.make src/base/CMakeFiles/scnet2_base.dir/build
.PHONY : scnet2_base/fast

#=============================================================================
# Target rules for targets named baseandloop

# Build rule for target.
baseandloop: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 baseandloop
.PHONY : baseandloop

# fast build rule for target.
baseandloop/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/baseandloop.dir/build.make src/base/tests/CMakeFiles/baseandloop.dir/build
.PHONY : baseandloop/fast

#=============================================================================
# Target rules for targets named condition

# Build rule for target.
condition: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 condition
.PHONY : condition

# fast build rule for target.
condition/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/condition.dir/build.make src/base/tests/CMakeFiles/condition.dir/build
.PHONY : condition/fast

#=============================================================================
# Target rules for targets named condition_timedwait

# Build rule for target.
condition_timedwait: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 condition_timedwait
.PHONY : condition_timedwait

# fast build rule for target.
condition_timedwait/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/condition_timedwait.dir/build.make src/base/tests/CMakeFiles/condition_timedwait.dir/build
.PHONY : condition_timedwait/fast

#=============================================================================
# Target rules for targets named currenttid

# Build rule for target.
currenttid: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 currenttid
.PHONY : currenttid

# fast build rule for target.
currenttid/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/currenttid.dir/build.make src/base/tests/CMakeFiles/currenttid.dir/build
.PHONY : currenttid/fast

#=============================================================================
# Target rules for targets named logbuffer

# Build rule for target.
logbuffer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 logbuffer
.PHONY : logbuffer

# fast build rule for target.
logbuffer/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/logbuffer.dir/build.make src/base/tests/CMakeFiles/logbuffer.dir/build
.PHONY : logbuffer/fast

#=============================================================================
# Target rules for targets named timer

# Build rule for target.
timer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 timer
.PHONY : timer

# fast build rule for target.
timer/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/timer.dir/build.make src/base/tests/CMakeFiles/timer.dir/build
.PHONY : timer/fast

#=============================================================================
# Target rules for targets named timer2

# Build rule for target.
timer2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 timer2
.PHONY : timer2

# fast build rule for target.
timer2/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/timer2.dir/build.make src/base/tests/CMakeFiles/timer2.dir/build
.PHONY : timer2/fast

#=============================================================================
# Target rules for targets named writefile

# Build rule for target.
writefile: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 writefile
.PHONY : writefile

# fast build rule for target.
writefile/fast:
	$(MAKE) -f src/base/tests/CMakeFiles/writefile.dir/build.make src/base/tests/CMakeFiles/writefile.dir/build
.PHONY : writefile/fast

#=============================================================================
# Target rules for targets named scnet2_net

# Build rule for target.
scnet2_net: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 scnet2_net
.PHONY : scnet2_net

# fast build rule for target.
scnet2_net/fast:
	$(MAKE) -f src/net/CMakeFiles/scnet2_net.dir/build.make src/net/CMakeFiles/scnet2_net.dir/build
.PHONY : scnet2_net/fast

#=============================================================================
# Target rules for targets named listenner

# Build rule for target.
listenner: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 listenner
.PHONY : listenner

# fast build rule for target.
listenner/fast:
	$(MAKE) -f src/net/tests/CMakeFiles/listenner.dir/build.make src/net/tests/CMakeFiles/listenner.dir/build
.PHONY : listenner/fast

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f src/net/tests/CMakeFiles/server.dir/build.make src/net/tests/CMakeFiles/server.dir/build
.PHONY : server/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... scnet2_base"
	@echo "... baseandloop"
	@echo "... condition"
	@echo "... condition_timedwait"
	@echo "... currenttid"
	@echo "... logbuffer"
	@echo "... timer"
	@echo "... timer2"
	@echo "... writefile"
	@echo "... scnet2_net"
	@echo "... listenner"
	@echo "... server"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

