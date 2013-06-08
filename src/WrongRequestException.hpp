#ifndef __WRONGREQUESTEXCEPTION__
#define __WRONGREQUESTEXCEPTION__

#include <exception>
namespace sioux {
	class WrongRequestException : public std::exception {
		virtual const char* what() const throw()
  		{
    		return "Bad request";
  		}
	};
}
#endif