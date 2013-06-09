#include <gtest/gtest.h>
#include "../src/request_handler.hpp"
#include "../src/request.hpp"
#include <boost/shared_ptr.hpp>
#include <iostream>

namespace sioux {
	namespace test {
		request_handler handler;

		TEST(handle_request, NotFoundCase) {
			std::shared_ptr< sioux::request > req( 
				new sioux::request() );
			req->method = "GET";
			req->uri = "file/doesnt/exist.html";
			req->http_version = "HTTP/1.0";
			reply rep;
			handler.handle_request(req, rep);
			ASSERT_EQ( reply::not_found, rep.type );
		}

		TEST(handle_request, OkCase) {
			std::shared_ptr< sioux::request > req( 
				new sioux::request() );
			req->method = "GET";
			req->uri = "test/index.html";
			req->http_version = "HTTP/1.0";
			reply rep;
			handler.handle_request(req, rep);
			std::cout << req->to_string();
			std::cout << rep.to_string();
			ASSERT_EQ( reply::ok, rep.type );
		}

		TEST(handle_request, IncorrectRequestCase) {
			std::shared_ptr< sioux::request > req;
			reply rep;
			handler.handle_request(req, rep);
			ASSERT_EQ( reply::not_implemented, rep.type );
		}

	}
}
