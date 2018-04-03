import json, yaml, csv, sys
import xml.etree.ElementTree as ET
from pprint import pprint

def get_cook_book(dformat):
    if dformat == 'json':
        with open('cook.json') as cf:
            return json.load(cf)
    elif dformat == 'yaml':
        with open('cook.yml') as cf:
            return yaml.load(cf)
    elif dformat == 'xml':
        tree = ET.parse('cook.xml')
        dishes = {}
        for e in tree.iter():
            if 'dishname' in e.attrib:
                ingridients = []
                for ch in e.iter():
                    if 'quantity' in ch.attrib:
                        ch.attrib['quantity'] = int(ch.attrib['quantity'])
                        ingridients.append(ch.attrib)
                dishes[e.attrib['dishname']] =  ingridients
        return dishes
    elif dformat == "csv":
         with open('cook.csv') as f:
           r = csv.DictReader(f, delimiter=';')
           dishes = {}
           name = ''
           for row in r:
               if name != row['name']:
                   name = row['name']
                   dishes[row['name']] = []
               row['quantity'] = int(row['quantity'])
               dishes[row['name']].append(row)
           return dishes
    else:
        print("Wrong format of data.")
        sys.exit()

def get_shop_list_by_dishes(dishes, person_count, dformat):
  shop_list = {}
  cook_book = get_cook_book(dformat)
  for dish in dishes:
    for ingridient in cook_book[dish]:
      new_shop_list_item = dict(ingridient)
      new_shop_list_item['quantity'] *= person_count
      if new_shop_list_item['ingridient_name'] not in shop_list:
        shop_list[new_shop_list_item['ingridient_name']] = new_shop_list_item
      else:
        shop_list[new_shop_list_item['ingridient_name']]['quantity'] += new_shop_list_item['quantity']
  return shop_list

def print_shop_list(shop_list):
  for shop_list_item in shop_list.values():
    print('{} {} {}'.format(shop_list_item['ingridient_name'], shop_list_item['quantity'],
                            shop_list_item['measure']))

def create_shop_list():
  dformat = input('Введите формат данных: ')
  person_count = int(input('Введите количество человек: '))
  dishes = input('Введите блюда в расчете на одного человека (через запятую): ').lower().split(', ')
  shop_list = get_shop_list_by_dishes(dishes, person_count, dformat)
  print_shop_list(shop_list)

create_shop_list()
