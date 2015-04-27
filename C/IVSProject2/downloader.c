#include "downloader.h"

//LOGIN: xjanci09
int download_webpage(char *url, char *filename) {
    CURL *curl;
    CURLcode res;
    FILE *fp;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "w");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 1;
        }
        fclose(fp);
    }
    curl_easy_cleanup(curl);
    return 0;
}
