#include "youtube_handler.h"

#include "youtube_stream.h"

namespace ytst {
	void YoutubeHandler::serve(HttpRequest& request, HttpResponseWriter& writer) {
		auto query = parse_query(request.query_string);
		auto youtube_id = query.find("id");
		auto chunked = query.find("chunked");
		if (youtube_id == query.end()) {
			std::string body = "Must pass youtube video id as query param 'id'";
			writer.write_response(HttpResponse::STATUS_BAD_REQUEST, false, body);
			return;
		} else {
			writer.header["Content-Type"] = "audio/mpeg";
			if (chunked != query.end() && chunked->second == "1") {
				writer.write_header(HttpResponse::STATUS_OK, true, -1);
			} else {
				// XXX: Hack! I can't get SONOS to work with chunked encoding, so just make the content-length really long
				writer.header["Content-Length"] = "524288000";
				writer.write_header(HttpResponse::STATUS_OK, false, -1);
			}

			start_decode(youtube_id->second, writer);
		}
	}

	void YoutubeHandler::start_decode(std::string& youtube_id, HttpResponseWriter& writer) {
		stream_running = true;
		stream_thread = std::thread([this,&writer,youtube_id] {
				ytst::YoutubeStream stream(fifo_directory,
						    python_supervisor,
						    stream_running,
						    writer);
				stream.stream(youtube_id);
			});
	}

	YoutubeHandler::YoutubeHandler(const std::string& fifo_directory,
				       std::shared_ptr<PythonSupervisor> python_supervisor) : fifo_directory(fifo_directory),
											      python_supervisor(python_supervisor) {
		stream_running = false;
	}

	YoutubeHandler::~YoutubeHandler() {
		stream_running = false;
		if (stream_thread.joinable()) {
			stream_thread.join();
		}
	}
}
