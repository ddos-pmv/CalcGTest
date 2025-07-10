include(FetchContent)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(CalcLib PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(CalcTests PRIVATE --coverage)
endif()

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(CalcTests 
CalculatorTest.cpp
HistroyTest.cpp
EdgeCaseTest.cpp

)

target_link_libraries(
    CalcTests
    CalcLib
    GTest::gtest_main  
    GTest::gmock_main
)

target_include_directories(
    CalcTests
     PRIVATE ${CMAKE_SOURCE_DIR}
)

