#include <gtest/gtest.h>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include "../src/request_parser.hpp"
#include "../src/WrongRequestException.hpp"

#include <memory>

namespace sioux {
	namespace test {

	request_parser req_parser;
	std::string basic_request( "GET /index.html HTTP/1.0\r\n\r\n" );

	TEST(parse, GetRequestCase) {
		auto req = req_parser.parse(std::make_shared<std::string>(basic_request));
		ASSERT_EQ("GET", req->method);
		ASSERT_EQ("index.html", req->uri);
		ASSERT_EQ("HTTP/1.0", req->http_version);
	}

	std::string bad_request( "LOL nowwhere/really_nowhere.wtf HTTP/1.0" );
	TEST(parse, BadRequestCase) {
		auto req = req_parser.parse(std::make_shared<std::string>(bad_request));
		ASSERT_EQ( nullptr, req.get() );
	}


}
}
