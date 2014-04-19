#include <assert.h>

#include <iostream>
#include "http_url.h"

int main() {
	std::string spaces_input("hello+there");
	std::string spaces_output("hello there");

	auto output = ytst::HttpUrl::decode(spaces_input);
	assert(output == spaces_output);

	std::string spaces_hex("hello%20there");
	output = ytst::HttpUrl::decode(spaces_hex);
	assert(output == spaces_output);

	std::string malformed("%2");
	output = ytst::HttpUrl::decode(malformed);
	assert(malformed == malformed);
}
