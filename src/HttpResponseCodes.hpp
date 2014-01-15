#ifndef YTST_HTTP_RESPONSE_CODES_HPP
#define YTST_HTTP_RESPONSE_CODES_HPP

using namespace std;

namespace ytst {
	struct HttpResponseCode {
		int code;
		string name;
	};

	class HttpResponse {
	public:
		static const HttpResponseCode StatusOk() {
			return HttpResponseCode { 200, "OK" };
		}
	};
}

#endif
