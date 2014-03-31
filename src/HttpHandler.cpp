#include "HttpHandler.hpp"

namespace ytst {
	int HttpHandler::parse_query(std::map<std::string, std::string>& res, std::string& q) {
		bool has_more = true;
		string::size_type pos = 0;
		string::size_type end_pos;

		while (has_more) {
			end_pos = q.find_first_of("=", pos);
			if (end_pos == string::npos) {
				break;
			}
			auto k = q.substr(pos, end_pos-pos);

			pos = end_pos+1;
			end_pos = q.find_first_of("&", pos);
			if (end_pos == string::npos) {
				has_more = false;
			}
			auto v = q.substr(pos, end_pos-pos);

			res[k] = v;
			pos = end_pos+1;
		}

		return 0;
	}
}
