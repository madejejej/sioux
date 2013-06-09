#ifndef __REQUEST__
#define __REQUEST__
#include <string>

namespace sioux {
	struct request {
		std::string method;
		std::string uri;
		std::string http_version;

		std::string to_string() {
			return method + " " + uri + " " + http_version + "\r\n";
		}
	};
}
#endif
