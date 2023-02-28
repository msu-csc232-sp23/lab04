/**
 * CSC232 - Data Structures
 * Missouri State University
 *
 * @file    test_task3.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Test suite to validate task 3 of this assignment.
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

#if !SKIP_TESTING_TASK_3
#include "Rectangle.h"
#endif

TEST_SUITE("Task 3"
           * doctest::description("A suite of tests for Task 3")
           * doctest::skip(SKIP_TESTING_TASK_3))
{
#if !SKIP_TESTING_TASK_3
    SCENARIO("The task is handed over for evaluation and we want to know if we should bother proceeding") {
        GIVEN("a sentinel value that signals the verification of task 3 to commence") {
            const char *search_string = "SKIP_TESTING_TASK_3 FALSE";
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
                                    "It appears you have not toggled SKIP_TESTING_TASK_3 from TRUE to FALSE. "
                                    "Please do this before attempt to validate this task.");
                }
            }
        }
    }
    SCENARIO("I'm looking for a particular declarations in a Rectangle class") {
        GIVEN("task 3 is ready for evaluation") {
            const char *search_string = "class Rectangle";
            const char *filename = "Rectangle.h";
            std::ifstream input_stream{filename, std::ios::in};
            if (!input_stream) {
                FAIL_CHECK("Test header file (Rectangle.h) could not be opened!");
                exit(EXIT_FAILURE);
            }
            WHEN("I look to see if the Rectangle class is declared") {
                // Read the entire file into memory
                std::string file_contents;
                std::string current_line;
                while (getline(input_stream, current_line))
                    file_contents += current_line + '\n';
                input_stream.close();

                size_t pos = file_contents.find(search_string);

                THEN("I expect to see the class properly declared") {

                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared a Rectangle class in "
                                                              "your header file (Rectangle.h).");
                }
                AND_THEN("I also expect to see the : Shape class extension declaration") {
                    search_string = "classRectangle:publicShape";
                    std::string s = std::string{ search_string };
                    file_contents.erase(std::remove_if(file_contents.begin(), file_contents.end(), ::isspace), file_contents.end());
                    pos = file_contents.find(search_string);
                    WARN_MESSAGE((static_cast<int>(pos) > 0), "It appears you have not declared the Rectangle class "
                                                              "to extend the Shape interface in your header file "
                                                              "(Rectangle.h).");
                }
            }
        }
    }
    SCENARIO("I'm looking for a particular definitions in a Rectangle class") {
        GIVEN("a Shape pointer pointing to a default Rectangle object") {
            Shape* shape{ new Rectangle{ } };
            double initial_len_value{ 1 };
            double initial_width_value{ 1 };
            WHEN("I ask for its length") {
                double expected{ initial_len_value };
                double actual{dynamic_cast<Rectangle*>(shape)->getLength()};
                THEN("I expect it to be of length 1") {
                    REQUIRE_EQ(expected, actual);
                }
            }
            AND_WHEN("I ask for its width") {
                double expected{ initial_width_value };
                double actual{dynamic_cast<Rectangle*>(shape)->getWidth()};
                THEN("I expect it to be of width 1") {
                    REQUIRE_EQ(expected, actual);
                }
            }
        }
        GIVEN("a Shape pointer pointing to an initialized Rectangle object") {
            double initial_len_value{ 1 };
            double initial_width_value{ 1 };
            Shape* shape{ new Rectangle{ initial_len_value, initial_width_value } };

            WHEN("I ask for its length") {
                double expected{ initial_len_value };
                double actual{dynamic_cast<Rectangle*>(shape)->getLength()};
                THEN("I expect it to be of length 1") {
                    REQUIRE_EQ(expected, actual);
                }
            }
            AND_WHEN("I ask for its width") {
                double expected{ initial_width_value };
                double actual{dynamic_cast<Rectangle*>(shape)->getWidth()};
                THEN("I expect it to be of width 1") {
                    REQUIRE_EQ(expected, actual);
                }
            }
        }
    }

    SCENARIO("A lazy afternoon drawing Rectangle shapes") {
        GIVEN("a Shape pointer pointing to a default Rectangle object") {
            Shape *shape{new Rectangle{}};
            // std::cout << "Rectangle of length " << length << " and width " << width << " is drawn...\n";
            std::string expected = "Rectangle of length 1 and width 1 is drawn...\n";
            std::stringstream buffer;

            WHEN("I draw that shape") {
                // Redirect std::cout to buffer
                std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

                // begin code to be tested
                shape->draw();
                // end code to be tested

                // Use the string value of buffer to compare against expected output
                const std::string text = buffer.str();
                // Restore original buffer before exiting
                std::cout.rdbuf(prevcoutbuf);

                THEN("I expect to see \"Rectangle of length 1 and width 1 is drawn...\" output to the standard output stream") {
                    CHECK_EQ(text, expected);
                }
            }
        }

        GIVEN("a Shape pointer pointing to an initialized Rectangle object") {
            double initial_len_value{ 2 };
            double initial_width_value{ 4 };
            Shape* shape{ new Rectangle{ initial_len_value, initial_width_value } };

            std::string expected = "Rectangle of length 2 and width 4 is drawn...\n";
            std::stringstream buffer;

            WHEN("I draw that shape") {
                // Redirect std::cout to buffer
                std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

                // begin code to be tested
                shape->draw();
                // end code to be tested

                // Use the string value of buffer to compare against expected output
                const std::string text = buffer.str();
                // Restore original buffer before exiting
                std::cout.rdbuf(prevcoutbuf);
                THEN("I expect to see \"Rectangle of length 2 and width 4 is drawn...\" output to the standard output stream") {
                    CHECK_EQ(text, expected);
                }
            }
            AND_WHEN("I point it to a different kind of shape and draw it") {
                // Redirect std::cout to buffer
                std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

                // begin code to be tested
                delete shape;
                shape = new Circle{ };
                shape->draw();
                // end code to be tested

                // Use the string value of buffer to compare against (the new) expected output
                expected = "Circle of radius 1 is drawn...\n";
                const std::string text = buffer.str();
                // Restore original buffer before exiting
                std::cout.rdbuf(prevcoutbuf);
                THEN("I expect to see \"Circle of radius 1 is drawn...\" output to the standard output stream") {
                    CHECK_EQ(text, expected);
                }
            }
        }
    }
#endif
}
