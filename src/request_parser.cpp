#include "request_parser.hpp"
#include "request.hpp"
#include "WrongRequestException.hpp"
#include <sstream>
#include <algorithm>
#include <vector>

namespace sioux {
std::shared_ptr<request> request_parser::parse(std::shared_ptr<std::string> request_str)
	throw( WrongRequestException )
{
	using namespace std;
	std::shared_ptr<request> req (
		new request() );

	istringstream iss(*request_str);
	vector< string > tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter< vector<string> >(tokens));

	if(tokens.size() < 3) {
		req.reset();
		return req;
	}

	if(tokens[0] == "GET") {
		req->method = "GET";
	} else {
		req.reset( );
		return req;
	}
	req->uri = tokens[1].substr(1);
	if(req->uri == "") {
		req->uri = "index.html";
	}
	req->http_version = tokens[2];
	return req;
}

}
