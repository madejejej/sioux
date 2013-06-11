#ifndef __REPLY__
#define __REPLY__

#include "header.hpp"

#include <string>
#include <vector>

namespace sioux {
	struct response {
		
		enum reply_type {
			ok = 200,
			bad_request = 400,
			not_found = 404,
			not_implemented = 501
		};
		reply_type type;
		std::string content;
		std::vector<header> headers;

		std::string to_string();

		static std::string type_to_string( reply_type t );
		static response stock_reply( reply_type t ) {
			response rep;
			rep.type = t;
			make_content( rep );
			return rep;
		}

	private:
		static void make_content(response &rep);
	};
}
#endif
