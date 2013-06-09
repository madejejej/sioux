#ifndef __CONNECTION__
#define __CONNECTION__

#include "request_parser.hpp"

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>

namespace sioux {
	class connection_pool;
	class request_handler;

	class connection : public boost::enable_shared_from_this<connection> {
	public:
		connection(boost::asio::io_service& io_service,
			std::shared_ptr <request_handler> req_handler, connection_pool &conn_pool);

		void start();
		void stop();
		std::shared_ptr< boost::asio::ip::tcp::socket > get_socket() {
			return m_socket;
		}

	private:
		void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred);
		void write_handler(const boost::system::error_code &ec);

		const boost::asio::io_service &					m_ioService;
		std::shared_ptr< request_handler > 				m_requestHandler;
		request_parser									m_requestParser;
		connection_pool &								m_connectionPool;
		std::shared_ptr< boost::asio::ip::tcp::socket > m_socket;
		boost::array<char, 8192>						m_data;
	};
}

#endif
