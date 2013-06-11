#include "connection.hpp"
#include "connection_pool.hpp"
#include "request_handler.hpp"
#include "reply.hpp"
#include "request.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace sioux
{
	connection::connection(boost::asio::io_service& io_service,
			std::shared_ptr <request_handler> req_handler, connection_pool &conn_pool) : 
			m_ioService(io_service), m_connectionPool( conn_pool ),
			m_socket( new boost::asio::ip::tcp::socket(io_service) )
	{

	}

	void connection::start()
	{
		std::cerr << "Waiting for message on connection...\n";
		m_socket->async_read_some(boost::asio::buffer(m_data),
				boost::bind(&connection::read_handler, shared_from_this(), boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}

	void connection::stop() 
	{
		boost::system::error_code ec;
		m_socket->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
		m_socket->close( ec );
	}

	void connection::read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
	{
		auto req = m_requestParser.parse(
				std::make_shared<std::string>(std::string(m_data.data(), m_data.data() + bytes_transferred)));

		if(req.get() != nullptr) {
			std::cerr << "Parsed request: " << req->to_string() << std::endl;
		} else {
			std::cerr << "Incorrect or unimplemented request: " << m_data.data() << std::endl;
		}
		response rep;
		m_requestHandler->handle_request( req, rep );

		std::cout << "Reply: " << rep.to_string() << std::endl;

		boost::asio::async_write( *m_socket, boost::asio::buffer(rep.to_string()),
				boost::bind(&connection::write_handler, shared_from_this(), boost::asio::placeholders::error) );
	}

	void connection::write_handler(const boost::system::error_code &ec)
	{
		m_connectionPool.stop_connection( shared_from_this() );
	}
}
