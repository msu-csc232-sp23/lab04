/**
 * CSC232 - Data Structures
 * Missouri State University
 *
 * @file    test_task1.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Test suite to validate task 1 of this assignment.
 * @version v2022.12.26
 * @date    Spring 2023
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "csc232.h"

TEST_SUITE("Task 1" * doctest::description("A suite of tests for Task 1: Create a shape interface") *
           doctest::skip(SKIP_TESTING_TASK_1)) {
    SCENARIO("The task is handed over for evaluation and we want to know if we should bother proceeding") {
        GIVEN("a sentinel value that signals the verification of task 1 to commence") {
            const char *search_string = "SKIP_TESTING_TASK_1 FALSE";
            const char *filename = "csc232.h";
            std::ifstream input_stream{filename, std::ios::in};
            if (!input_stream) {
                FAIL_CHECK("Test source file could not be opened!");
                exit(EXIT_FAILURE);
            }

            WHEN("the file containing the signal is read") {
                // Read the entire file into memory
                std::string file_contents;
                std::string current_line;
                while (getline(input_stream, current_line))
                    file_contents += current_line + '\n';
                input_stream.close();

                size_t pos = file_contents.find(search_string);
                THEN("the signal to proceed is encountered") {
                    REQUIRE_MESSAGE((static_cast<int>(pos) > 0),
                                    "It appears you have not toggled SKIP_TESTING_TASK_1 from TRUE to FALSE. "
                                    "Please do this before attempt to validate this task.");
                }
            }
        }
    }

    SCENARIO("I'm looking for a particular declarations in a shape interface") {
        GIVEN("task 1 is ready for evaluation") {
            const char *search_string = "virtual";
            const char *filename = "Shape.h";
            std::ifstream input_stream{filename, std::ios::in};
            if (!input_stream) {
                FAIL_CHECK("Test header file could not be opened!");
                exit(EXIT_FAILURE);
            }
            WHEN("I look to see if the draw method has been declared as a pure virtual function") {
                // Read the entire file into memory
                std::string file_contents;
                std::string current_line;
                while (getline(input_stream, current_line))
                    file_contents += current_line + '\n';
                input_stream.close();

                size_t pos = file_contents.find(search_string);

                THEN("I expect to see the virtual keyword") {

                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared a virtual method in "
                                                              "your interface.");
                }
                AND_THEN("I also expect to see the = 0 pure declaration") {
                    search_string = " = 0";
                    pos = file_contents.find(search_string);
                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared a pure virtual method "
                                                              "in your interface.");
                }
            }
            AND_WHEN("I look to see if a virtual destructor is defined") {
                // Read the entire file into memory
                std::string file_contents;
                std::string current_line;
                while (getline(input_stream, current_line))
                    file_contents += current_line + '\n';
                input_stream.close();
                search_string = "virtual ~Shape";
                size_t pos = file_contents.find(search_string);

                THEN("I expect to see the virtual shape destructor is indeed defined") {
                    bool isDestructorDefined{(static_cast<int>(pos) > 0)};
                    WARN_MESSAGE(isDestructorDefined, "It appears you have not defined a virtual shape "
                                                      "destructor in your interface.");
                }
            }
        }
    }
}
