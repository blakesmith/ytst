import re

from .common import InfoExtractor
from ..utils import (
    int_or_none,
    parse_duration,
)


class CNNIE(InfoExtractor):
    _VALID_URL = r'''(?x)https?://((edition|www)\.)?cnn\.com/video/(data/.+?|\?)/
        (?P<path>.+?/(?P<title>[^/]+?)(?:\.cnn|(?=&)))'''

    _TESTS = [{
        u'url': u'http://edition.cnn.com/video/?/video/sports/2013/06/09/nadal-1-on-1.cnn',
        u'file': u'sports_2013_06_09_nadal-1-on-1.cnn.mp4',
        u'md5': u'3e6121ea48df7e2259fe73a0628605c4',
        u'info_dict': {
            u'title': u'Nadal wins 8th French Open title',
            u'description': u'World Sport\'s Amanda Davies chats with 2013 French Open champion Rafael Nadal.',
            u'duration': 135,
            u'upload_date': u'20130609',
        },
    },
    {
        u"url": u"http://edition.cnn.com/video/?/video/us/2013/08/21/sot-student-gives-epic-speech.georgia-institute-of-technology&utm_source=feedburner&utm_medium=feed&utm_campaign=Feed%3A+rss%2Fcnn_topstories+%28RSS%3A+Top+Stories%29",
        u"file": u"us_2013_08_21_sot-student-gives-epic-speech.georgia-institute-of-technology.mp4",
        u"md5": u"b5cc60c60a3477d185af8f19a2a26f4e",
        u"info_dict": {
            u"title": "Student's epic speech stuns new freshmen",
            u"description": "A Georgia Tech student welcomes the incoming freshmen with an epic speech backed by music from \"2001: A Space Odyssey.\""
        }
    }]

    def _real_extract(self, url):
        mobj = re.match(self._VALID_URL, url)
        path = mobj.group('path')
        page_title = mobj.group('title')
        info_url = u'http://cnn.com/video/data/3.0/%s/index.xml' % path
        info = self._download_xml(info_url, page_title)

        formats = []
        rex = re.compile(r'''(?x)
            (?P<width>[0-9]+)x(?P<height>[0-9]+)
            (?:_(?P<bitrate>[0-9]+)k)?
        ''')
        for f in info.findall('files/file'):
            video_url = 'http://ht.cdn.turner.com/cnn/big%s' % (f.text.strip())
            fdct = {
                'format_id': f.attrib['bitrate'],
                'url': video_url,
            }

            mf = rex.match(f.attrib['bitrate'])
            if mf:
                fdct['width'] = int(mf.group('width'))
                fdct['height'] = int(mf.group('height'))
                fdct['tbr'] = int_or_none(mf.group('bitrate'))
            else:
                mf = rex.search(f.text)
                if mf:
                    fdct['width'] = int(mf.group('width'))
                    fdct['height'] = int(mf.group('height'))
                    fdct['tbr'] = int_or_none(mf.group('bitrate'))
                else:
                    mi = re.match(r'ios_(audio|[0-9]+)$', f.attrib['bitrate'])
                    if mi:
                        if mi.group(1) == 'audio':
                            fdct['vcodec'] = 'none'
                            fdct['ext'] = 'm4a'
                        else:
                            fdct['tbr'] = int(mi.group(1))

            formats.append(fdct)

        self._sort_formats(formats)

        thumbnails = sorted([((int(t.attrib['height']),int(t.attrib['width'])), t.text) for t in info.findall('images/image')])
        thumbs_dict = [{'resolution': res, 'url': t_url} for (res, t_url) in thumbnails]

        metas_el = info.find('metas')
        upload_date = (
            metas_el.attrib.get('version') if metas_el is not None else None)

        duration_el = info.find('length')
        duration = parse_duration(duration_el.text)

        return {
            'id': info.attrib['id'],
            'title': info.find('headline').text,
            'formats': formats,
            'thumbnail': thumbnails[-1][1],
            'thumbnails': thumbs_dict,
            'description': info.find('description').text,
            'duration': duration,
            'upload_date': upload_date,
        }
