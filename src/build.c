#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include "build.h"
#include "download.h"
#include "main.h"

static char *version;

void build() {
    checkIfBuildToolsExists();

    appendOutput(stradd("Building Spigot and Bukkit version ", version));
    appendOutput("This might take a few minutes...");

    system(stradd(stradd(stradd(stradd(stradd("cd ", buildToolsFolder), " && java -jar "), buildToolsFile), " --rev "), version));

    system(stradd(stradd("mv ", buildToolsFolder), "/craftbukkit* ."));
    system(stradd(stradd("mv ", buildToolsFolder), "/spigot* ."));

    appendOutput("Finished build");
}

void runBuildTools(char ver[]) {
    ver[0] = (char) tolower(ver[0]);

    version = ver;

    char ch = '-';
    pthread_t thread;

    pthread_create(&thread, NULL, (void *(*)(void *)) build, &ch);
}