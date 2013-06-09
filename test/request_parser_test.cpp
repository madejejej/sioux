#include <gtest/gtest.h>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include "../src/request_parser.hpp"
#include "../src/WrongRequestException.hpp"

#include <memory>

namespace sioux {
	namespace test {

	request_parser req_parser;
	std::string basic_request("GET /index.html HTTP/1.0\r\n\r\n");

	TEST(parse, shouldUnderstandGetRequest) {
		auto req = req_parser.parse(std::make_shared<std::string>(basic_request));
		ASSERT_EQ("GET", req->method);
		ASSERT_EQ("index.html", req->uri);
	}


}
}
