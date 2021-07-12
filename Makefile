# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kajames/projects/health_care/healthcare_chronic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kajames/projects/health_care/healthcare_chronic

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/cmake-3.15.4-Linux-x86_64/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
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
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kajames/projects/health_care/healthcare_chronic/CMakeFiles /home/kajames/projects/health_care/healthcare_chronic/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kajames/projects/health_care/healthcare_chronic/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tests_main

# Build rule for target.
tests_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tests_main
.PHONY : tests_main

# fast build rule for target.
tests_main/fast:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/build
.PHONY : tests_main/fast

#=============================================================================
# Target rules for targets named healthdp

# Build rule for target.
healthdp: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 healthdp
.PHONY : healthdp

# fast build rule for target.
healthdp/fast:
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/build
.PHONY : healthdp/fast

#=============================================================================
# Target rules for targets named gmock_main

# Build rule for target.
gmock_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock_main
.PHONY : gmock_main

# fast build rule for target.
gmock_main/fast:
	$(MAKE) -f bin/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build.make bin/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build
.PHONY : gmock_main/fast

#=============================================================================
# Target rules for targets named gmock

# Build rule for target.
gmock: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock
.PHONY : gmock

# fast build rule for target.
gmock/fast:
	$(MAKE) -f bin/googletest-build/googlemock/CMakeFiles/gmock.dir/build.make bin/googletest-build/googlemock/CMakeFiles/gmock.dir/build
.PHONY : gmock/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) -f bin/googletest-build/googletest/CMakeFiles/gtest_main.dir/build.make bin/googletest-build/googletest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) -f bin/googletest-build/googletest/CMakeFiles/gtest.dir/build.make bin/googletest-build/googletest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

health_dp_main.o: health_dp_main.cc.o

.PHONY : health_dp_main.o

# target to build an object file
health_dp_main.cc.o:
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/health_dp_main.cc.o
.PHONY : health_dp_main.cc.o

health_dp_main.i: health_dp_main.cc.i

.PHONY : health_dp_main.i

# target to preprocess a source file
health_dp_main.cc.i:
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/health_dp_main.cc.i
.PHONY : health_dp_main.cc.i

health_dp_main.s: health_dp_main.cc.s

.PHONY : health_dp_main.s

# target to generate assembly for a file
health_dp_main.cc.s:
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/health_dp_main.cc.s
.PHONY : health_dp_main.cc.s

src/dp/decision_cache.o: src/dp/decision_cache.cc.o

.PHONY : src/dp/decision_cache.o

# target to build an object file
src/dp/decision_cache.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/decision_cache.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/decision_cache.cc.o
.PHONY : src/dp/decision_cache.cc.o

src/dp/decision_cache.i: src/dp/decision_cache.cc.i

.PHONY : src/dp/decision_cache.i

# target to preprocess a source file
src/dp/decision_cache.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/decision_cache.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/decision_cache.cc.i
.PHONY : src/dp/decision_cache.cc.i

src/dp/decision_cache.s: src/dp/decision_cache.cc.s

.PHONY : src/dp/decision_cache.s

# target to generate assembly for a file
src/dp/decision_cache.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/decision_cache.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/decision_cache.cc.s
.PHONY : src/dp/decision_cache.cc.s

src/dp/storage.o: src/dp/storage.cc.o

.PHONY : src/dp/storage.o

# target to build an object file
src/dp/storage.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/storage.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/storage.cc.o
.PHONY : src/dp/storage.cc.o

src/dp/storage.i: src/dp/storage.cc.i

.PHONY : src/dp/storage.i

# target to preprocess a source file
src/dp/storage.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/storage.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/storage.cc.i
.PHONY : src/dp/storage.cc.i

src/dp/storage.s: src/dp/storage.cc.s

.PHONY : src/dp/storage.s

# target to generate assembly for a file
src/dp/storage.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/dp/storage.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/dp/storage.cc.s
.PHONY : src/dp/storage.cc.s

src/healthcare/configuration.o: src/healthcare/configuration.cc.o

.PHONY : src/healthcare/configuration.o

# target to build an object file
src/healthcare/configuration.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration.cc.o
.PHONY : src/healthcare/configuration.cc.o

src/healthcare/configuration.i: src/healthcare/configuration.cc.i

.PHONY : src/healthcare/configuration.i

# target to preprocess a source file
src/healthcare/configuration.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration.cc.i
.PHONY : src/healthcare/configuration.cc.i

src/healthcare/configuration.s: src/healthcare/configuration.cc.s

.PHONY : src/healthcare/configuration.s

# target to generate assembly for a file
src/healthcare/configuration.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration.cc.s
.PHONY : src/healthcare/configuration.cc.s

src/healthcare/configuration/fitness_reader.o: src/healthcare/configuration/fitness_reader.cc.o

.PHONY : src/healthcare/configuration/fitness_reader.o

# target to build an object file
src/healthcare/configuration/fitness_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/fitness_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/fitness_reader.cc.o
.PHONY : src/healthcare/configuration/fitness_reader.cc.o

src/healthcare/configuration/fitness_reader.i: src/healthcare/configuration/fitness_reader.cc.i

.PHONY : src/healthcare/configuration/fitness_reader.i

# target to preprocess a source file
src/healthcare/configuration/fitness_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/fitness_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/fitness_reader.cc.i
.PHONY : src/healthcare/configuration/fitness_reader.cc.i

src/healthcare/configuration/fitness_reader.s: src/healthcare/configuration/fitness_reader.cc.s

.PHONY : src/healthcare/configuration/fitness_reader.s

# target to generate assembly for a file
src/healthcare/configuration/fitness_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/fitness_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/fitness_reader.cc.s
.PHONY : src/healthcare/configuration/fitness_reader.cc.s

src/healthcare/configuration/insurance_reader.o: src/healthcare/configuration/insurance_reader.cc.o

.PHONY : src/healthcare/configuration/insurance_reader.o

# target to build an object file
src/healthcare/configuration/insurance_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/insurance_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/insurance_reader.cc.o
.PHONY : src/healthcare/configuration/insurance_reader.cc.o

src/healthcare/configuration/insurance_reader.i: src/healthcare/configuration/insurance_reader.cc.i

.PHONY : src/healthcare/configuration/insurance_reader.i

# target to preprocess a source file
src/healthcare/configuration/insurance_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/insurance_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/insurance_reader.cc.i
.PHONY : src/healthcare/configuration/insurance_reader.cc.i

src/healthcare/configuration/insurance_reader.s: src/healthcare/configuration/insurance_reader.cc.s

.PHONY : src/healthcare/configuration/insurance_reader.s

# target to generate assembly for a file
src/healthcare/configuration/insurance_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/insurance_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/insurance_reader.cc.s
.PHONY : src/healthcare/configuration/insurance_reader.cc.s

src/healthcare/configuration/job_reader.o: src/healthcare/configuration/job_reader.cc.o

.PHONY : src/healthcare/configuration/job_reader.o

# target to build an object file
src/healthcare/configuration/job_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/job_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/job_reader.cc.o
.PHONY : src/healthcare/configuration/job_reader.cc.o

src/healthcare/configuration/job_reader.i: src/healthcare/configuration/job_reader.cc.i

.PHONY : src/healthcare/configuration/job_reader.i

# target to preprocess a source file
src/healthcare/configuration/job_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/job_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/job_reader.cc.i
.PHONY : src/healthcare/configuration/job_reader.cc.i

src/healthcare/configuration/job_reader.s: src/healthcare/configuration/job_reader.cc.s

.PHONY : src/healthcare/configuration/job_reader.s

# target to generate assembly for a file
src/healthcare/configuration/job_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/job_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/job_reader.cc.s
.PHONY : src/healthcare/configuration/job_reader.cc.s

src/healthcare/configuration/joy_reader.o: src/healthcare/configuration/joy_reader.cc.o

.PHONY : src/healthcare/configuration/joy_reader.o

# target to build an object file
src/healthcare/configuration/joy_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/joy_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/joy_reader.cc.o
.PHONY : src/healthcare/configuration/joy_reader.cc.o

src/healthcare/configuration/joy_reader.i: src/healthcare/configuration/joy_reader.cc.i

.PHONY : src/healthcare/configuration/joy_reader.i

# target to preprocess a source file
src/healthcare/configuration/joy_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/joy_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/joy_reader.cc.i
.PHONY : src/healthcare/configuration/joy_reader.cc.i

src/healthcare/configuration/joy_reader.s: src/healthcare/configuration/joy_reader.cc.s

.PHONY : src/healthcare/configuration/joy_reader.s

# target to generate assembly for a file
src/healthcare/configuration/joy_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/joy_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/joy_reader.cc.s
.PHONY : src/healthcare/configuration/joy_reader.cc.s

src/healthcare/configuration/prob_reader.o: src/healthcare/configuration/prob_reader.cc.o

.PHONY : src/healthcare/configuration/prob_reader.o

# target to build an object file
src/healthcare/configuration/prob_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/prob_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/prob_reader.cc.o
.PHONY : src/healthcare/configuration/prob_reader.cc.o

src/healthcare/configuration/prob_reader.i: src/healthcare/configuration/prob_reader.cc.i

.PHONY : src/healthcare/configuration/prob_reader.i

# target to preprocess a source file
src/healthcare/configuration/prob_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/prob_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/prob_reader.cc.i
.PHONY : src/healthcare/configuration/prob_reader.cc.i

src/healthcare/configuration/prob_reader.s: src/healthcare/configuration/prob_reader.cc.s

.PHONY : src/healthcare/configuration/prob_reader.s

# target to generate assembly for a file
src/healthcare/configuration/prob_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/prob_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/prob_reader.cc.s
.PHONY : src/healthcare/configuration/prob_reader.cc.s

src/healthcare/configuration/subjective_probability_reader.o: src/healthcare/configuration/subjective_probability_reader.cc.o

.PHONY : src/healthcare/configuration/subjective_probability_reader.o

# target to build an object file
src/healthcare/configuration/subjective_probability_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/subjective_probability_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/subjective_probability_reader.cc.o
.PHONY : src/healthcare/configuration/subjective_probability_reader.cc.o

src/healthcare/configuration/subjective_probability_reader.i: src/healthcare/configuration/subjective_probability_reader.cc.i

.PHONY : src/healthcare/configuration/subjective_probability_reader.i

# target to preprocess a source file
src/healthcare/configuration/subjective_probability_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/subjective_probability_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/subjective_probability_reader.cc.i
.PHONY : src/healthcare/configuration/subjective_probability_reader.cc.i

src/healthcare/configuration/subjective_probability_reader.s: src/healthcare/configuration/subjective_probability_reader.cc.s

.PHONY : src/healthcare/configuration/subjective_probability_reader.s

# target to generate assembly for a file
src/healthcare/configuration/subjective_probability_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/subjective_probability_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/subjective_probability_reader.cc.s
.PHONY : src/healthcare/configuration/subjective_probability_reader.cc.s

src/healthcare/configuration/utility_reader.o: src/healthcare/configuration/utility_reader.cc.o

.PHONY : src/healthcare/configuration/utility_reader.o

# target to build an object file
src/healthcare/configuration/utility_reader.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/utility_reader.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/utility_reader.cc.o
.PHONY : src/healthcare/configuration/utility_reader.cc.o

src/healthcare/configuration/utility_reader.i: src/healthcare/configuration/utility_reader.cc.i

.PHONY : src/healthcare/configuration/utility_reader.i

# target to preprocess a source file
src/healthcare/configuration/utility_reader.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/utility_reader.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/utility_reader.cc.i
.PHONY : src/healthcare/configuration/utility_reader.cc.i

src/healthcare/configuration/utility_reader.s: src/healthcare/configuration/utility_reader.cc.s

.PHONY : src/healthcare/configuration/utility_reader.s

# target to generate assembly for a file
src/healthcare/configuration/utility_reader.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/configuration/utility_reader.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/configuration/utility_reader.cc.s
.PHONY : src/healthcare/configuration/utility_reader.cc.s

src/healthcare/decision.o: src/healthcare/decision.cc.o

.PHONY : src/healthcare/decision.o

# target to build an object file
src/healthcare/decision.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision.cc.o
.PHONY : src/healthcare/decision.cc.o

src/healthcare/decision.i: src/healthcare/decision.cc.i

.PHONY : src/healthcare/decision.i

# target to preprocess a source file
src/healthcare/decision.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision.cc.i
.PHONY : src/healthcare/decision.cc.i

src/healthcare/decision.s: src/healthcare/decision.cc.s

.PHONY : src/healthcare/decision.s

# target to generate assembly for a file
src/healthcare/decision.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision.cc.s
.PHONY : src/healthcare/decision.cc.s

src/healthcare/decision_evaluator.o: src/healthcare/decision_evaluator.cc.o

.PHONY : src/healthcare/decision_evaluator.o

# target to build an object file
src/healthcare/decision_evaluator.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision_evaluator.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision_evaluator.cc.o
.PHONY : src/healthcare/decision_evaluator.cc.o

src/healthcare/decision_evaluator.i: src/healthcare/decision_evaluator.cc.i

.PHONY : src/healthcare/decision_evaluator.i

# target to preprocess a source file
src/healthcare/decision_evaluator.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision_evaluator.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision_evaluator.cc.i
.PHONY : src/healthcare/decision_evaluator.cc.i

src/healthcare/decision_evaluator.s: src/healthcare/decision_evaluator.cc.s

.PHONY : src/healthcare/decision_evaluator.s

# target to generate assembly for a file
src/healthcare/decision_evaluator.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/decision_evaluator.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/decision_evaluator.cc.s
.PHONY : src/healthcare/decision_evaluator.cc.s

src/healthcare/period_result.o: src/healthcare/period_result.cc.o

.PHONY : src/healthcare/period_result.o

# target to build an object file
src/healthcare/period_result.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/period_result.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/period_result.cc.o
.PHONY : src/healthcare/period_result.cc.o

src/healthcare/period_result.i: src/healthcare/period_result.cc.i

.PHONY : src/healthcare/period_result.i

# target to preprocess a source file
src/healthcare/period_result.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/period_result.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/period_result.cc.i
.PHONY : src/healthcare/period_result.cc.i

src/healthcare/period_result.s: src/healthcare/period_result.cc.s

.PHONY : src/healthcare/period_result.s

# target to generate assembly for a file
src/healthcare/period_result.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/period_result.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/period_result.cc.s
.PHONY : src/healthcare/period_result.cc.s

src/healthcare/person.o: src/healthcare/person.cc.o

.PHONY : src/healthcare/person.o

# target to build an object file
src/healthcare/person.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/person.cc.o
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/person.cc.o
.PHONY : src/healthcare/person.cc.o

src/healthcare/person.i: src/healthcare/person.cc.i

.PHONY : src/healthcare/person.i

# target to preprocess a source file
src/healthcare/person.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/person.cc.i
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/person.cc.i
.PHONY : src/healthcare/person.cc.i

src/healthcare/person.s: src/healthcare/person.cc.s

.PHONY : src/healthcare/person.s

# target to generate assembly for a file
src/healthcare/person.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/src/healthcare/person.cc.s
	$(MAKE) -f CMakeFiles/healthdp.dir/build.make CMakeFiles/healthdp.dir/src/healthcare/person.cc.s
.PHONY : src/healthcare/person.cc.s

test/healthcare/decision_test.o: test/healthcare/decision_test.cc.o

.PHONY : test/healthcare/decision_test.o

# target to build an object file
test/healthcare/decision_test.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/decision_test.cc.o
.PHONY : test/healthcare/decision_test.cc.o

test/healthcare/decision_test.i: test/healthcare/decision_test.cc.i

.PHONY : test/healthcare/decision_test.i

# target to preprocess a source file
test/healthcare/decision_test.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/decision_test.cc.i
.PHONY : test/healthcare/decision_test.cc.i

test/healthcare/decision_test.s: test/healthcare/decision_test.cc.s

.PHONY : test/healthcare/decision_test.s

# target to generate assembly for a file
test/healthcare/decision_test.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/decision_test.cc.s
.PHONY : test/healthcare/decision_test.cc.s

test/healthcare/insurance/actuarial_tests.o: test/healthcare/insurance/actuarial_tests.cc.o

.PHONY : test/healthcare/insurance/actuarial_tests.o

# target to build an object file
test/healthcare/insurance/actuarial_tests.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/actuarial_tests.cc.o
.PHONY : test/healthcare/insurance/actuarial_tests.cc.o

test/healthcare/insurance/actuarial_tests.i: test/healthcare/insurance/actuarial_tests.cc.i

.PHONY : test/healthcare/insurance/actuarial_tests.i

# target to preprocess a source file
test/healthcare/insurance/actuarial_tests.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/actuarial_tests.cc.i
.PHONY : test/healthcare/insurance/actuarial_tests.cc.i

test/healthcare/insurance/actuarial_tests.s: test/healthcare/insurance/actuarial_tests.cc.s

.PHONY : test/healthcare/insurance/actuarial_tests.s

# target to generate assembly for a file
test/healthcare/insurance/actuarial_tests.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/actuarial_tests.cc.s
.PHONY : test/healthcare/insurance/actuarial_tests.cc.s

test/healthcare/insurance/fixed_tests.o: test/healthcare/insurance/fixed_tests.cc.o

.PHONY : test/healthcare/insurance/fixed_tests.o

# target to build an object file
test/healthcare/insurance/fixed_tests.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/fixed_tests.cc.o
.PHONY : test/healthcare/insurance/fixed_tests.cc.o

test/healthcare/insurance/fixed_tests.i: test/healthcare/insurance/fixed_tests.cc.i

.PHONY : test/healthcare/insurance/fixed_tests.i

# target to preprocess a source file
test/healthcare/insurance/fixed_tests.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/fixed_tests.cc.i
.PHONY : test/healthcare/insurance/fixed_tests.cc.i

test/healthcare/insurance/fixed_tests.s: test/healthcare/insurance/fixed_tests.cc.s

.PHONY : test/healthcare/insurance/fixed_tests.s

# target to generate assembly for a file
test/healthcare/insurance/fixed_tests.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/insurance/fixed_tests.cc.s
.PHONY : test/healthcare/insurance/fixed_tests.cc.s

test/healthcare/person_tests.o: test/healthcare/person_tests.cc.o

.PHONY : test/healthcare/person_tests.o

# target to build an object file
test/healthcare/person_tests.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/person_tests.cc.o
.PHONY : test/healthcare/person_tests.cc.o

test/healthcare/person_tests.i: test/healthcare/person_tests.cc.i

.PHONY : test/healthcare/person_tests.i

# target to preprocess a source file
test/healthcare/person_tests.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/person_tests.cc.i
.PHONY : test/healthcare/person_tests.cc.i

test/healthcare/person_tests.s: test/healthcare/person_tests.cc.s

.PHONY : test/healthcare/person_tests.s

# target to generate assembly for a file
test/healthcare/person_tests.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/test/healthcare/person_tests.cc.s
.PHONY : test/healthcare/person_tests.cc.s

tests_main.o: tests_main.cc.o

.PHONY : tests_main.o

# target to build an object file
tests_main.cc.o:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/tests_main.cc.o
.PHONY : tests_main.cc.o

tests_main.i: tests_main.cc.i

.PHONY : tests_main.i

# target to preprocess a source file
tests_main.cc.i:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/tests_main.cc.i
.PHONY : tests_main.cc.i

tests_main.s: tests_main.cc.s

.PHONY : tests_main.s

# target to generate assembly for a file
tests_main.cc.s:
	$(MAKE) -f CMakeFiles/tests_main.dir/build.make CMakeFiles/tests_main.dir/tests_main.cc.s
.PHONY : tests_main.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install/local"
	@echo "... edit_cache"
	@echo "... tests_main"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... healthdp"
	@echo "... gmock_main"
	@echo "... gmock"
	@echo "... gtest_main"
	@echo "... gtest"
	@echo "... health_dp_main.o"
	@echo "... health_dp_main.i"
	@echo "... health_dp_main.s"
	@echo "... src/dp/decision_cache.o"
	@echo "... src/dp/decision_cache.i"
	@echo "... src/dp/decision_cache.s"
	@echo "... src/dp/storage.o"
	@echo "... src/dp/storage.i"
	@echo "... src/dp/storage.s"
	@echo "... src/healthcare/configuration.o"
	@echo "... src/healthcare/configuration.i"
	@echo "... src/healthcare/configuration.s"
	@echo "... src/healthcare/configuration/fitness_reader.o"
	@echo "... src/healthcare/configuration/fitness_reader.i"
	@echo "... src/healthcare/configuration/fitness_reader.s"
	@echo "... src/healthcare/configuration/insurance_reader.o"
	@echo "... src/healthcare/configuration/insurance_reader.i"
	@echo "... src/healthcare/configuration/insurance_reader.s"
	@echo "... src/healthcare/configuration/job_reader.o"
	@echo "... src/healthcare/configuration/job_reader.i"
	@echo "... src/healthcare/configuration/job_reader.s"
	@echo "... src/healthcare/configuration/joy_reader.o"
	@echo "... src/healthcare/configuration/joy_reader.i"
	@echo "... src/healthcare/configuration/joy_reader.s"
	@echo "... src/healthcare/configuration/prob_reader.o"
	@echo "... src/healthcare/configuration/prob_reader.i"
	@echo "... src/healthcare/configuration/prob_reader.s"
	@echo "... src/healthcare/configuration/subjective_probability_reader.o"
	@echo "... src/healthcare/configuration/subjective_probability_reader.i"
	@echo "... src/healthcare/configuration/subjective_probability_reader.s"
	@echo "... src/healthcare/configuration/utility_reader.o"
	@echo "... src/healthcare/configuration/utility_reader.i"
	@echo "... src/healthcare/configuration/utility_reader.s"
	@echo "... src/healthcare/decision.o"
	@echo "... src/healthcare/decision.i"
	@echo "... src/healthcare/decision.s"
	@echo "... src/healthcare/decision_evaluator.o"
	@echo "... src/healthcare/decision_evaluator.i"
	@echo "... src/healthcare/decision_evaluator.s"
	@echo "... src/healthcare/period_result.o"
	@echo "... src/healthcare/period_result.i"
	@echo "... src/healthcare/period_result.s"
	@echo "... src/healthcare/person.o"
	@echo "... src/healthcare/person.i"
	@echo "... src/healthcare/person.s"
	@echo "... test/healthcare/decision_test.o"
	@echo "... test/healthcare/decision_test.i"
	@echo "... test/healthcare/decision_test.s"
	@echo "... test/healthcare/insurance/actuarial_tests.o"
	@echo "... test/healthcare/insurance/actuarial_tests.i"
	@echo "... test/healthcare/insurance/actuarial_tests.s"
	@echo "... test/healthcare/insurance/fixed_tests.o"
	@echo "... test/healthcare/insurance/fixed_tests.i"
	@echo "... test/healthcare/insurance/fixed_tests.s"
	@echo "... test/healthcare/person_tests.o"
	@echo "... test/healthcare/person_tests.i"
	@echo "... test/healthcare/person_tests.s"
	@echo "... tests_main.o"
	@echo "... tests_main.i"
	@echo "... tests_main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

