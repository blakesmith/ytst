#include "YTDownloader.hpp"

namespace ytst {
	YTDownloader::YTDownloader(const char* url, const char* out) {
		this->download_url = url;
		this->file_out = out;
	}

	int YTDownloader::download() {
		return 0;
	}
}
