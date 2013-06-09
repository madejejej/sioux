#ifndef __HEADER__
#define __HEADER__

#include <string>

namespace sioux {
	class header {
	public:
		header(const std::string &name, const std::string &value) : name(name), value(value) {}

		const std::string& get_name() { return name; }
		const std::string& get_value() { return value; }

	private:
		std::string name;
		std::string value;
	};
}

#endif
