#ifndef YTST_HTTP_RESPONSE_CODES_HPP
#define YTST_HTTP_RESPONSE_CODES_HPP

using namespace std;

namespace ytst {
	class HttpResponse {
	public:
		static const int STATUS_OK = 200;
		static const int STATUS_BAD_REQUEST = 400;
		static const int STATUS_NOT_FOUND = 404;

		static const int get_name(const int code, string& out) {
			switch (code) {
			case 200:
				out = "OK";
				return 0;
			case 400:
				out = "Bad Request";
				return 0;
			case 404:
				out = "Not Found";
				return 0;
			default:
				out = "OK";
				return -1;
			}
		}
	};
}

#endif
