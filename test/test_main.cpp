#include <gtest/gtest.h>

#include "request_handler_test.cpp"
#include "request_parser_test.cpp"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
