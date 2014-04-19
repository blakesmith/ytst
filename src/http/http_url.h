#ifndef YTST_HTTP_URL
#define YTST_HTTP_URL

#include <string>

namespace ytst {
	class HttpUrl {
		static const char unhex(const char c);
	public:
		static std::string decode(const std::string& input);
	};
}

#endif
