/**
 * CSC232 - Data Structures
 * Missouri State University
 *
 * @file    test_task2.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Test suite to validate task 2 of this assignment.
 * @version v2022.12.26
 * @date    Spring 2023
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "csc232.h"
#if !SKIP_TESTING_TASK_1
#include "Shape.h"
#endif

#if !SKIP_TESTING_TASK_2
#include "Circle.h"
#endif

TEST_SUITE("Task 2"
           * doctest::description("A suite of tests for Task 2")
           * doctest::skip(SKIP_TESTING_TASK_2)) {
#if !SKIP_TESTING_TASK_2
    SCENARIO("The task is handed over for evaluation and we want to know if we should bother proceeding") {
        GIVEN("a sentinel value that signals the verification of task 2 to commence") {
            const char *search_string = "SKIP_TESTING_TASK_2 FALSE";
            const char *filename = "csc232.h";
            std::ifstream input_stream{filename, std::ios::in};
            if (!input_stream) {
                FAIL_CHECK("Test source file (csc232.h) could not be opened!");
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
                                    "It appears you have not toggled SKIP_TESTING_TASK_2 from TRUE to FALSE. "
                                    "Please do this before attempt to validate this task.");
                }
            }
        }
    }
    SCENARIO("I'm looking for a particular declarations in a Circle class") {
        GIVEN("task 2 is ready for evaluation") {
            const char *search_string = "class Circle";
            const char *filename = "Circle.h";
            std::ifstream input_stream{filename, std::ios::in};
            if (!input_stream) {
                FAIL_CHECK("Test header file (Circle.h) could not be opened!");
                exit(EXIT_FAILURE);
            }
            WHEN("I look to see if the Circle class is declared") {
                // Read the entire file into memory
                std::string file_contents;
                std::string current_line;
                while (getline(input_stream, current_line))
                    file_contents += current_line + '\n';
                input_stream.close();

                size_t pos = file_contents.find(search_string);

                THEN("I expect to see the class properly declared") {

                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared a Circle class in "
                                                              "your header file (Circle.h).");
                }
                AND_THEN("I also expect to see the : Shape class extension declaration") {
                    search_string = "classCircle:publicShape";
                    std::string s = std::string{ search_string };
                    file_contents.erase(std::remove_if(file_contents.begin(), file_contents.end(), ::isspace), file_contents.end());
                    pos = file_contents.find(search_string);
                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared the Circle class "
                                                              "to extend the Shape interface in your header file "
                                                              "(Circle.h).");
                }
            }
        }
    }
    SCENARIO("I'm looking for a particular definitions in a Circle class") {
        GIVEN("a Shape pointer pointing to a default Circle object") {
            Shape* shape{ new Circle{ } };
            double initial_value{ 1 };
            WHEN("I ask for its radius") {
                double expected{ initial_value };
                double actual{dynamic_cast<Circle*>(shape)->getRadius()};
                THEN("I expect it to be the radius of a unit circle") {
                    REQUIRE_EQ(expected, actual);
                }
            }
        }
        GIVEN("a Shape pointer pointing to an initialized Circle object") {
            double initial_value{ 3.14159 };
            Shape* shape{ new Circle{ initial_value } };

            WHEN("I ask for its radius") {
                double expected{ initial_value };
                double actual{dynamic_cast<Circle*>(shape)->getRadius()};
                THEN("I expect the radius to be the initial value") {
                    REQUIRE_EQ(expected, actual);
                }
            }
        }
    }

    SCENARIO("A lazy afternoon drawing Circle shapes") {
        GIVEN("a Shape pointer pointing to a default Circle object") {
            Shape* shape{ new Circle{ } };
            std::string expected = "Circle of radius 1 is drawn...\n";
            std::stringstream buffer;

            WHEN("I draw that shape") {
                // Redirect std::cout to buffer
                std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

                // begin code to be tested
                shape->draw();
                // end code to be tested

                // Use the string value of buffer to compare against expected output
                const std::string text = buffer.str();
                // Restore original buffer before exiting
                std::cout.rdbuf(prevcoutbuf);

                THEN("I expect to see \"Circle of radius 1 is drawn...\" output to the standard output stream") {
                    CHECK_EQ(text, expected);
                }
            }
        }

        GIVEN("a Shape pointer pointing to an initialized Circle object") {
            double initial_radius{ 3.14159 };
            Shape* shape{ new Circle{ initial_radius } };
            std::string expected = "Circle of radius 3.14159 is drawn...\n";
            std::stringstream buffer;

            WHEN("I draw that shape") {
                // Redirect std::cout to buffer
                std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

                // begin code to be tested
                shape->draw();
                // end code to be tested

                // Use the string value of buffer to compare against expected output
                const std::string text = buffer.str();
                // Restore original buffer before exiting
                std::cout.rdbuf(prevcoutbuf);
                THEN("I expect to see \"Circle of radius 3.14159 is drawn...\" output to the standard output stream") {
                    CHECK_EQ(text, expected);
                }
            }
        }
    }
#endif
}