#ifndef __CONNECTION_POOL__
#define __CONNECTION_POOL__ 

#include <set>
#include <boost/shared_ptr.hpp>

namespace sioux {
	class connection;

	class connection_pool {
	public:
		void start_connection(boost::shared_ptr<connection> connection_ptr);
		void stop_connection(boost::shared_ptr<connection> connection_ptr);
	private:
		std::set< boost::shared_ptr<connection> > m_connections;
	};
}
#endif
