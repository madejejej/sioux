#include "request_handler.hpp"

#include <fstream>
#include <boost/lexical_cast.hpp>

namespace sioux
{
	void request_handler::handle_request( std::shared_ptr< request > req, reply &rep )
	{
		if( req.get() == nullptr ) {
			rep = reply::stock_reply(reply::not_implemented);
		} else if( req->method == "GET" ) {
			if( file_exists( req->uri ) ) {
				rep = reply::stock_reply(reply::ok);
				rep.content = get_file_content( req->uri );
			} else {
				rep = reply::stock_reply(reply::not_found);
			}

		} else {
			rep = reply::stock_reply(reply::not_implemented);
		}
		rep.headers.push_back( header( "Content-Length",
									boost::lexical_cast<std::string>( rep.content.size() ) ) );
				rep.headers.push_back( header("Content-Type", "text/html") );

	}

	std::string request_handler::get_file_content( const std::string &filepath )
	{
		std::ifstream ifs(filepath);
		return std::string( ( std::istreambuf_iterator<char>(ifs) ),
                ( std::istreambuf_iterator<char>() ) );

	}
}
