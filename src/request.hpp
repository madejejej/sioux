#ifndef __REQUEST__
#define __REQUEST__
#include <string>

namespace sioux {
	struct request {
		std::string method;
		std::string uri;
	};
}
#endif