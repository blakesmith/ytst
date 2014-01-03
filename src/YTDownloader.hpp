#ifndef YTST_YT_DOWNLOADER_HPP
#define YTST_YT_DOWNLOADER_HPP

namespace ytst {
	class YTDownloader {
		const char* download_url;
		const char* file_out;
	public:
		YTDownloader(const char* url, const char* out);
		int download();
	};
}
#endif
