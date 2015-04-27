#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <stdio.h>
#include <curl/curl.h>

int download_webpage(char *url, char *filename);

#endif
