#include "../server.hpp"

using namespace sioux;

int main() {
	server s("127.0.0.1", "8080");
	s.run();
	return 0;
}
