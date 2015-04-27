#!/bin/bash

echo "Beginning tests"
echo "================================================="
echo "Test 1: Downloading files and computing md5sum"
if [ -d downloads ]; then
    rm downloads/*
fi
if [ -d ref ]; then
    rm ref/*
fi
if [ ! -d downloads ]; then
    mkdir downloads
fi
if [ ! -d ref ]; then
    mkdir ref
fi

URLS=`cat "test/urls.txt"`
COUNTER=1
for url in $URLS; do
    ./xjanci09 $url downloads/test_url"$COUNTER".html >/dev/null
    wget $url -O ref/test_url"$COUNTER".html >/dev/null 2>&1

    echo -n "Webpage $COUNTER: "
    if [ ! -f "ref/test_url"$COUNTER".html" ] || [ ! -f "downloads/test_url"$COUNTER".html" ]; then
        echo "Download FAILED"
        exit 1
    fi

    WGET_MD5SUM=`md5sum ref/test_url"$COUNTER".html | cut -c1-32`
    XJANCI09_MD5SUM=`md5sum ref/test_url"$COUNTER".html | cut -c1-32`
    
    if [ $WGET_MD5SUM = $XJANCI09_MD5SUM ]; then
        echo "Download OK"
    else 
        echo "Download FAILED"
        exit 1
    fi

    ((COUNTER++))
done

TFS=`ls "test/files"`
COUNTER=1

echo "================================================="
echo "Test 2: Computing even parity on predefined files"

for file in $TFS; do
    echo -n "File $COUNTER: "
    NUMBITS=`xxd -b -c 1 "test/files/$file" | cut -f 2 -d ' ' | grep -o "1" | wc -l`
    PARITY=$((NUMBITS%2))
    PARITY_XJANCI09=`./xjanci09 "test/files/$file"`
    if [ $PARITY -eq $PARITY_XJANCI09 ]; then
        echo "Parity OK"
    else
        echo "Parity FAILED"
    fi
    ((COUNTER++))
done

exit 0
