import glob, json, codecs, collections
from pprint import pprint
from xml.dom import minidom

def get_all_json():
    return glob.glob('*.json')

def get_all_xml():
    return glob.glob('*.xml')

def strip_html(string):
    is_tag = False
    string_wihtout_tags = ''
    for ch in string:
        if ch == '<':
            is_tag = True
            continue
        elif ch == '>':
            is_tag = False
            continue
        if not is_tag and ch != '\n' and ch != '/':
            string_wihtout_tags += ch
    return string_wihtout_tags

def strip_small_words(string):
    return [word for word in string.split(' ') if len(word) > 5]

def print_most_common(string):
    counter = collections.Counter(strip_small_words(string)).most_common()
    [ print (w[0], w[1]) for w in counter[0:6]]

def get_news_from_json(f, e):
    all_news = ''
    with open(f, encoding=e) as opf:
        tmp = json.load(opf)
        for each in tmp['rss']['channel']['item']:
            if  isinstance(each['title'], dict):
                all_news += strip_html(each['title']['__cdata'] + each['description']['__cdata'])
            else:
                all_news += strip_html(each['title'] + each['description'])
    return all_news

def get_news_from_xml(f, e):
    all_news = ''
    with open(f, encoding=e) as opf:
        xmldoc = minidom.parse(opf)
        itemlist = xmldoc.getElementsByTagName('description')
        for s in itemlist:
            all_news += s.firstChild.nodeValue
        itemlist = xmldoc.getElementsByTagName('title')
        for s in itemlist:
            all_news += s.firstChild.nodeValue
    return strip_html(all_news)

encodings_json = ['iso8859_5', 'cp1251', 'utf-8', 'koi8_r']
encodings_xml = ['iso8859_5', 'cp1251', 'koi8_r', 'utf-8']

json_files = get_all_json()

for f, e in zip(json_files, encodings_json):
    print('In file {} most common 6chars+ words are as follows:'.format(f))
    print_most_common(get_news_from_json(f, e))
    print('\n')

xml_files = get_all_xml()

for f, e in zip(xml_files, encodings_xml):
    print('In file {} most common 6chars+ words are as follows:'.format(f))
    print_most_common(get_news_from_xml(f, e))
    print('\n')
