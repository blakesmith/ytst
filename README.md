# YTST (Youtube Streamer)

YTST is a small web server that does on-the-fly youtube video
downloading and audio rencoding. The goal is to support streaming the
audio portion of a youtube video to a sonos device via
[Sonatron](https://sonatron.blakesmith.me).

## Current functionality

- Downloads and encodes the video as a 128kbit MP3.

## TODO

- Accept the actual youtube video id as as input query param. Right
  now it just hardcodes a Madeon video. Need to integrate an actual
  http parser.
- Investigate memory usage. Might just be the embedded python
  interpreter adding bloat
- Better encoder thread frame buffering strategy

## Compile / Use

You'll need a C++11 compatible compiler. I use g++-4.8.

    ./autogen.sh
	CXX=g++-4.8 ./configure
	make
	make install
	
Additionally, ytst by default looks for the `youtube-dl` python code
in `/usr/local/lib/ytst/python`. You can change that with the -p flag.
	
Start ytst:

    ytst -p /usr/local/lib/ytst/python
	
Then try a local mplayer call to stream a video:

    mplayer "http://localhost:8192"
	
