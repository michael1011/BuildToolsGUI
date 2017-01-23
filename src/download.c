#include <sys/stat.h>
#include <zconf.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <pthread.h>
#include "main.h"
#include "download.h"

struct stat st = {0};

char buildToolsFolder[] = "BuildTools";
char buildToolsFile[] = "BuildTools.jar";

char buildToolsUrl[] = "https://hub.spigotmc.org/jenkins/job/BuildTools/lastSuccessfulBuild/artifact/target/BuildTools.jar";

void download() {
    appendOutput(stradd("Downloading ", buildToolsFile));

    CURL *curl = curl_easy_init();

    FILE *file = fopen(stradd(stradd(buildToolsFolder, "/"), buildToolsFile), "wb");

    curl_easy_setopt(curl, CURLOPT_URL, buildToolsUrl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(file);

    appendOutput("Finished download");
}

void checkIfBuildToolsExists() {
    if (stat(buildToolsFolder, &st) == -1) {
        mkdir(buildToolsFolder, 0700);
    }

    if (access(stradd(stradd(buildToolsFolder, "/"), buildToolsFile), F_OK) == -1) {
        appendOutput(stradd(stradd("'", buildToolsFile), "' not found"));

        download();
    }
}

void downloadBuildTools() {
    if (access(stradd(stradd(buildToolsFolder, "/"), buildToolsFile), F_OK) != -1) {
        appendOutput("Removing old files");

        system(stradd("rm -rf ", buildToolsFolder));
    }

    mkdir(buildToolsFolder, 0700);

    char ch = '-';
    pthread_t thread;

    pthread_create(&thread, NULL, (void *(*)(void *)) download, &ch);
}