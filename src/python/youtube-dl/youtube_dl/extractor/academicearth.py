import re

from .common import InfoExtractor


class AcademicEarthCourseIE(InfoExtractor):
    _VALID_URL = r'^https?://(?:www\.)?academicearth\.org/(?:courses|playlists)/(?P<id>[^?#/]+)'
    IE_NAME = u'AcademicEarth:Course'

    def _real_extract(self, url):
        m = re.match(self._VALID_URL, url)
        playlist_id = m.group('id')

        webpage = self._download_webpage(url, playlist_id)
        title = self._html_search_regex(
            r'<h1 class="playlist-name">(.*?)</h1>', webpage, u'title')
        description = self._html_search_regex(
            r'<p class="excerpt">(.*?)</p>',
            webpage, u'description', fatal=False)
        urls = re.findall(
            r'<h3 class="lecture-title"><a target="_blank" href="([^"]+)">',
            webpage)
        entries = [self.url_result(u) for u in urls]

        return {
            '_type': 'playlist',
            'id': playlist_id,
            'title': title,
            'description': description,
            'entries': entries,
        }
