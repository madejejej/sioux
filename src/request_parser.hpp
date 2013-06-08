#include <boost/shared_ptr.hpp>
#include <iterator>

#include "request.hpp"
#include "WrongRequestException.hpp"

namespace sioux {

	class request_parser {
		
		public:
			request_parser() {}
			boost::shared_ptr<request> parse(boost::shared_ptr<std::string> request_str)
				throw( WrongRequestException );
		private:
			
	};
}