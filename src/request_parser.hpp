#ifndef __REQUEST_PARSER__
#define __REQUEST_PARSER__

#include <memory>
#include <iterator>

#include "request.hpp"
#include "WrongRequestException.hpp"

namespace sioux {

	class request_parser {
		
		public:
			request_parser() {}
			std::shared_ptr<request> parse(std::shared_ptr<std::string> request_str)
				throw( WrongRequestException );
		private:
			
	};
}
#endif