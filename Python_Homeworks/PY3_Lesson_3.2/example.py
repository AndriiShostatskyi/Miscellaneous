import requests
import os
import sys

# Please change this api key if necessary
API_KEY = ('trnsl.1.1.20170402T101928Z.316c1ceb43346933.'
           'a4056acf9796d62841a2468eceb702d3922c771a')


def detect_lang(path_to_file):
    try:
        detect_param = {'key': API_KEY, 'text': open(os.path.basename(
            os.path.join(path_to_file))).readlines()}
        return requests.get('https://translate.'
                            'yandex.net/api/v1.5/tr.json/detect',
                            params=detect_param).json()['lang']
    except:
        print("Error opening the given file and/or detecting its language")
        sys.exit()


def translate(path_source_file, path_result_file, from_lang, to_lang="ru"):
    if from_lang == detect_lang(path_source_file):
        params = {
            'key': API_KEY,
            'text': open(os.path.basename(os.path.join(path_source_file))
                         ).readlines(),
            'lang': '{}-{}'.format(from_lang, to_lang),
        }
        with open(path_result_file, 'w') as fop:
            print("Translating ...")
            fop.write("".join(requests.get(
                'https://translate.yandex.net/api/v1.5/tr.json/translate',
                params=params).json()['text']))
            print("Done")
    else:
        print("Given language does not match detected language of text")
        sys.exit()


def tranlate_all_txt_files():
    translate('DE.txt', 'DE_RU.txt', 'de')
    translate('FR.txt', 'FR_EN.txt', 'fr', 'en')
    translate('ES.txt', 'ES_UK.txt', 'es', 'uk')


tranlate_all_txt_files()
