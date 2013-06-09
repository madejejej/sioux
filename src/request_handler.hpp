#ifndef __REQUEST_HANDLER__
#define __REQUEST_HANDLER__

#include "reply.hpp"
#include "request.hpp"

#include <sys/stat.h>
#include <memory>
#include <fstream>

namespace sioux {
	struct request;

	class request_handler {
	public:
		void handle_request( std::shared_ptr< request > req, reply &rep );
	private:
		bool file_exists( const std::string &name ) {
  			struct stat buffer;   
  			return (stat (name.c_str(), &buffer) == 0); 
		}
	};

}

#endif