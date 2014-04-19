#include "http_url.h"

namespace ytst {
	const char HttpUrl::unhex(const char c) {
		if ('0' <= c && c <= '9') {
			return c - '0';
		}
		
		if ('a' <= c && c <= 'f') {
			return c - 'a' + 10;
		}

		if ('A' <= c && c <= 'F') {
			return c - 'A' + 10;
		}

		return 0;
	}

	std::string HttpUrl::decode(const std::string& input) {
		std::string decoded;
		char dehexed;

		for (int i = 0; i < input.length(); ++i) {
			char ch = input[i];


			switch (ch) {
			case '+':
				decoded.push_back(' ');
				break;
			case '%':
				if (i+2 <= input.length()) {
					dehexed = unhex(input[i+1]) << 4 | unhex(input[i+2]);
					decoded.push_back(dehexed);
					i += 2;
				}
				break;
			default:
				decoded.push_back(ch);
			}
		}

		return decoded;
	}
}
