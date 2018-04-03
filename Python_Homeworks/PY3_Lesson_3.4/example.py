import osa
import re
import os
import statistics as stat

def get_avtemp_cel(file_path):
    with open(os.path.join(file_path)) as temp_file:
        avt = stat.mean([float(line[:2]) for line in temp_file])
        client = osa.client.Client('http://www.webservicex.net/ConvertTemperature.asmx?WSDL')
        return round(client.service.ConvertTemp(Temperature=avt, FromUnit='degreeFahrenheit', ToUnit='degreeCelsius'), 2)

def get_amount(file_path):
    with open(os.path.join(file_path)) as temp_file:
        client = osa.client.Client('http://fx.currencysystem.com/webservices/CurrencyServer4.asmx?WSDL')
        total = 0.0
        for line in temp_file:
            amount = re.findall('\d+', line)
            curren = line[-4:]
            if len(curren) >= 3:
                total += client.service.ConvertToNum(toCurrency='RUB', fromCurrency=curren[:3], amount=amount, rounding=1)
        return total

def get_distance(file_path):
    with open(os.path.join(file_path)) as temp_file:
        client = osa.client.Client('http://www.webservicex.net/length.asmx?WSDL')
        total = 0.0
        for line in temp_file:
            dist = re.findall('[0-9][0-9,.]+', line.replace(',',''))
            total += client.service.ChangeLengthUnit(LengthValue=dist, fromLengthUnit='Miles', toLengthUnit='Kilometers')
        return round(total, 2)

print('Average temperature in Celsius: ', get_avtemp_cel('temps.txt'))
print('Total amount in RUB: ', get_amount('currencies.txt'))
print('Total distance in kilometrs: ', get_distance('travel.txt'))
