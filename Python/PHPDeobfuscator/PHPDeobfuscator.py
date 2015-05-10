#!/usr/bin/python3

import sys
import re
import binascii
import zlib
import base64

def gzinflate(base64_string):
    compressed_data = base64.b64decode(base64_string)
    return zlib.decompress(compressed_data, -15)

def hexreplace(hex_string): #unused
    hexas = re.findall(r'\\x[0-9A-F]{2}', hex_string, re.I);

    translated = set()
    for i in range(len(hexas)):
        transtuple = (hexas[i],)
        hexas[i]=hexas[i][2:]
        hexas[i]=(binascii.unhexlify(hexas[i])).decode("utf-8")
        transtuple = (transtuple[0],hexas[i])
        translated.add(transtuple)

    for transtuple in translated:
        hex_string = re.sub("\\"+transtuple[0], transtuple[1], hex_string)
    return hex_string

filename = sys.argv[1]
file = open(filename)
fileText = file.read()

while len(fileText) != 0:
    match = re.findall("[a-zA-Z0-9\n+/=]*", fileText);

    max_val = 0
    final_i = 0
    for i in range(len(match)):
        if len(match[i]) > max_val:
            max_val = len(match[i])
            final_i = i

    fileText = gzinflate(match[final_i]).decode("utf-8")
    if fileText.find("<?php") != -1 and fileText.find(" ") != -1:
        print(fileText[2:])
        break
