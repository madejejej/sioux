#include "../server.hpp"

#include <string>
#include <boost/program_options.hpp>
using namespace sioux;

int main(int argc, char **argv) {
	std::string default_addr = "127.0.0.1";
	std::string port = "80";
	std::size_t thread_count = 1;

	try {
		namespace po = boost::program_options;
		po::options_description desc("Options");
		    desc.add_options()
		      ("help,h", "Print help messages")
		      ("port,p", po::value<std::string>(&port), "port number")
		      ("thread_count,t", po::value<std::size_t>(&thread_count), "Number of dispatching threads");

		po::variables_map vm;
		try {
			po::store( po::parse_command_line(argc, argv, desc), vm);

			if( vm.count("help") ) {
				std::cout << "Program options: \n";
				std::cout << "--help, -h : prints program help\n";
				std::cout << "--port, -p : sets server port (default: 8080)\n";
				std::cout << "--thread_count, -t : Sets number of dispatching threads (default: 1)\n";
				return 0;
			}
			po::notify(vm);

		} catch( po::error &e) {
			std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
			std::cerr << desc << std::endl;
			return 2;
		}

		server s(default_addr, port);
		s.run( thread_count );
	} catch(std::exception &e) {
		std::cerr << "An error occurred. Sorry :'(\n";
		return -1;
	}

	return 0;
}
