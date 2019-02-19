cmake_minimum_required(VERSION 3.10.2)
project (HealthCare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
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
