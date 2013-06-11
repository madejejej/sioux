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
			ASSERT_EQ( reply::ok, rep.type );
			ASSERT_EQ( "<html><head><title>Test site</title></head><body><h1>O HAI</h1><br /><p>This works!</p></body></html>\n",
					rep.content );
		}

		TEST(handle_request, IncorrectRequestCase) {
			std::shared_ptr< sioux::request > req;
			reply rep;
			handler.handle_request(req, rep);
			ASSERT_EQ( reply::not_implemented, rep.type );
		}

	}
}
