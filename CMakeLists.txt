cmake_minimum_required(VERSION 3.10)

project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SUDOKU_LIB ${CMAKE_CURRENT_SOURCE_DIR} sudoku/*.cpp sudoku/*.h)

add_executable(Sudoku
    main.cpp
    ${SUDOKU_LIB})

#Setup CMake to run tests
enable_testing()

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    # Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc} ${SUDOKU_LIB})

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)
