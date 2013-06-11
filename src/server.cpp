#include "server.hpp"
#include "request_handler.hpp"
#include "connection.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace sioux {
using namespace boost::asio;

server::server(const std::string &address, 
			const std::string &port ) : m_acceptor(m_ioService), 
			m_requestHandler( new request_handler() )
{
	ip::tcp::resolver 			resolver(m_ioService);
	ip::tcp::resolver::query 	query( address, port, boost::asio::ip::resolver_query_base::numeric_service );
	ip::tcp::endpoint 			endpoint = *resolver.resolve( query );
	m_acceptor.open( endpoint.protocol() );
	m_acceptor.set_option( ip::tcp::acceptor::reuse_address(true) );
	boost::system::error_code ec;
	m_acceptor.bind( endpoint, ec );
	if( ec ) {
		std::cerr << "Error: " << ec.message() << std::endl;
	}
	m_acceptor.listen();

	start();
}

void server::run( std::size_t thread_count )
{
	if( thread_count < 1 ) {
		std::cerr << thread_count << " threads, rly?\n";
		return;
	}
	for(std::size_t i=0; i<thread_count; i++) {
		m_workerThreads.create_thread( boost::bind(&server::run_thread, this) );
	}
	std::cout << "Started " << thread_count << " dispatching threads\n";
	m_workerThreads.join_all();
}

void server::run_thread()
{
	m_ioService.run();
}

void server::start() 
{
	m_incomingConnection.reset(
		new connection(m_ioService, m_requestHandler, m_connectionPool));
	std::cerr << "Waiting for new connection\n";
	m_acceptor.async_accept( *m_incomingConnection->get_socket(),
		boost::bind(&server::accept_handler, this, boost::asio::placeholders::error) );
}

void server::accept_handler( const boost::system::error_code &ec ) 
{
	if(!m_acceptor.is_open()) {
		return;
	}
		std::cerr << "Accepted new connection\n";
		m_connectionPool.start_connection(m_incomingConnection);
		start();
}
}
