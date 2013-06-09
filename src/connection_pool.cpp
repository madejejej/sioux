#include "connection_pool.hpp"
#include "connection.hpp"

namespace sioux {
	void connection_pool::start_connection(boost::shared_ptr<connection> connection_ptr) {
		connection_ptr->start();
		m_connections.insert( connection_ptr );
	}
	
	void connection_pool::stop_connection(boost::shared_ptr<connection> connection_ptr) {
		connection_ptr->stop();
		m_connections.erase( connection_ptr );
	}
}
