#include "request_parser.hpp"
#include "request.hpp"
#include "WrongRequestException.hpp"
#include <sstream>
#include <algorithm>
#include <vector>

namespace sioux {
boost::shared_ptr<request> request_parser::parse(boost::shared_ptr<std::string> request_str)
	throw( WrongRequestException )
{
	using namespace std;
	boost::shared_ptr<request> req (
		new request() );

	istringstream iss(*request_str);
	vector< string > tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter< vector<string> >(tokens));

	if(tokens[0] == "GET") {
		req->method = "GET";
	} else {
		
	}
	req->uri = tokens[1];
	return req;
}

}