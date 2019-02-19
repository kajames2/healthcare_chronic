cmake_minimum_required(VERSION 3.10.2)
project (HealthCare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)
 
set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/healthcare/person.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/period_result.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/decision_evaluator.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/joy_reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/job_reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/fitness_reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/prob_reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/configuration/insurance_reader.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/enjoyment/fractional.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/decision.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/fitness/composite.cc
  ${PROJECT_SOURCE_DIR}/src/healthcare/fitness/fixed_price.cc
  ${PROJECT_SOURCE_DIR}/src/dp/decision_cache.cc
  )

if (MSYS)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME ON)
endif (MSYS)

find_package( Boost REQUIRED COMPONENTS system filesystem program_options)
include_directories( ${Boost_INCLUDE_DIRS} )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(healthdp ${PROJECT_SOURCE_DIR}/health_dp_main.cc ${SOURCES})
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
target_link_libraries(healthdp Threads::Threads ${Boost_LIBRARIES})



# Taken from GoogleTests Manual

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(TEST_SOURCES
  ${PROJECT_SOURCE_DIR}/test/healthcare/decision_test.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/enjoyment/frational.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/person_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/fitness/flat_loss_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/fitness/proportional_loss.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/fitness/composite_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/fitness/fixed_price_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/insurance/fixed_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/insurance/actuarial_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/job/flat_tests.cc
  ${PROJECT_SOURCE_DIR}/test/healthcare/job/age_linear_tests.cc
  )

add_executable(tests_main tests_main.cc ${SOURCES} ${TEST_SOURCES})

target_link_libraries(tests_main gtest_main)
add_test(NAME    tests_main 
         COMMAND tests_main)
