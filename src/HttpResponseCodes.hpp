#ifndef YTST_HTTP_RESPONSE_CODES_HPP
#define YTST_HTTP_RESPONSE_CODES_HPP

using namespace std;

namespace ytst {
	class HttpResponse {
	public:
		static const int STATUS_OK = 200;

		static const string get_name(const int code) {
			switch (code) {
			case 200: return "OK";
			}
		}
	};
}

#endif
