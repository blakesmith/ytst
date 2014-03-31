#include "YoutubeHandler.hpp"

#include "HttpParser.hpp"
#include "Stream.hpp"

namespace ytst {
	void YoutubeHandler::serve(HttpRequest& request, HttpResponseWriter& writer) {
		std::map<std::string, std::string> query;
		HttpParser::parse_query(query, request.query_string);
		auto youtube_id = query.find("id");
		auto chunked = query.find("chunked");
		if (youtube_id == query.end()) {
			std::string body = "Must pass youtube video id as query param 'id'";
			writer.write_response(400, false, body);
			return;
		} else {
			writer.header["Content-Type"] = "audio/mpeg";
			if (chunked != query.end() && chunked->second == "1") {
				writer.write_header(200, true, -1);
			} else {
				// XXX: Hack! I can't get SONOS to work with chunked encoding, so just make the content-length really long
				writer.header["Content-Length"] = "524288000";
				writer.write_header(200, false, -1);
			}

			start_decode(youtube_id->second, writer);
		}
	}

	void YoutubeHandler::start_decode(std::string& youtube_id, HttpResponseWriter& writer) {
		stream_running = true;
		stream_thread = std::thread([this,&writer,youtube_id] {
				ytst::Stream stream(fifo_directory,
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
