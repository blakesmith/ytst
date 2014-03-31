#ifndef YTST_YOUTUBE_HANDLER
#define YTST_YOUTUBE_HANDLER

#include <atomic>
#include <thread>
#include <memory>

#include "http/http_handler.h"
#include "PythonSupervisor.hpp"

namespace ytst {
	class YoutubeHandler : public HttpHandler {
		std::thread stream_thread;
		std::atomic<bool> stream_running;
		const std::string& fifo_directory;
		std::shared_ptr<PythonSupervisor> python_supervisor;

		void start_decode(std::string& youtube_id, HttpResponseWriter& writer);
	public:
		virtual void serve(HttpRequest& request, HttpResponseWriter& writer);
		~YoutubeHandler();
		YoutubeHandler(const std::string& fifo_directory,
			       std::shared_ptr<PythonSupervisor> python_supervisor);
	};
}

#endif
