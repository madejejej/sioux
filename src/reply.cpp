#include "reply.hpp"

#include <boost/lexical_cast.hpp>
#include <sstream>
#include <map>

namespace sioux {
	namespace premade_replies {
		using namespace std;
		static string reply_ok = "";
		static string reply_not_found =
				"<html>"
			  	"<head><title>Not Found</title></head>"
			  	"<body><h1>404 Not Found</h1></body>"
			 	"</html>";
		static string reply_bad_request =
				"<html>"
				"<head><title>Bad Request</title></head>"
				"<body><h1>400 Bad Request</h1></body>"
				"</html>";
		static string reply_not_implemented =
				"<html>"
				"<head><title>Not Implemented</title></head>"
				"<body><h1>501 Not Implemented</h1></body>"
				"</html>";
	}

	std::string reply::to_string()
	{
		using namespace std;
		ostringstream ss;
		ss << "HTTP/1.0 " << type_to_string(type) << "\r\n";
		for(header h : headers) {
			ss << h.get_name() << ": " << h.get_value() << "\r\n";
		}
		ss << "\r\n";
		ss << content << "\r\n";

		return ss.str();
	}

	std::string reply::type_to_string( reply_type t )
	{
		switch(t) {
					case ok:
						return "200 OK";
					case not_found:
						return "404 Not Found";
					case bad_request:
						return "400 Bad Request";
					case not_implemented:
						return "501 Not Implemented";
				}
	}

	void reply::make_content(reply &rep)
	{
		using namespace std;
		switch(rep.type) {
			case ok:
				rep.content = premade_replies::reply_ok;
				break;
			case not_found:
				rep.content = premade_replies::reply_not_found;
				break;
			case bad_request:
				rep.content = premade_replies::reply_bad_request;
				break;
			case not_implemented:
				rep.content = premade_replies::reply_not_implemented;
				break;
		}
		rep.headers.push_back( header( "Content-Length",
							boost::lexical_cast<std::string>( rep.content.size() ) ) );
		rep.headers.push_back( header("Content-Type", "text/html") );
	}
}
