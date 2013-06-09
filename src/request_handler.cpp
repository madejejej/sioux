#include "request_handler.hpp"

namespace sioux
{
	void request_handler::handle_request( std::shared_ptr< request > req, reply &rep )
	{
		if( req.get() == nullptr ) {
			rep = reply::stock_reply(reply::not_implemented);
			return;
		}
		if( req->method == "GET" ) {
			if( file_exists( req->uri ) ) {
				rep = reply::stock_reply(reply::ok);
				return;
			} else {
				rep = reply::stock_reply(reply::not_found);
				return;
			}
		}
	}
}
