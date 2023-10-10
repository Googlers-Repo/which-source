#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#ifdef _WIN32
#define WHICH_DELIMITER   ";"
#else
#define WHICH_DELIMITER   ":"
#endif

using namespace std;

char* which_path(const char *name, const char *_path) {
  char *path = strdup(_path);
  if (NULL == path) return NULL;
  char *tok = strtok(path, WHICH_DELIMITER);

  while (tok) {
    // path
    int len = strlen(tok) + 2 + strlen(name);
    char *file = (char*)malloc(len);
    if (!file) {
      free(path);
      return NULL;
    }
    sprintf(file, "%s/%s", tok, name);

    // Hide root related binaries
    vector<string> strs{
      "su", "tsu",
      "magisk", "magiskboot",
      "magiskpolicy", "supolicy",
      "resetprop", "ksu", "ksud",
      "magiskinit"
    };

    if (find(strs.begin(), strs.end(), (const char*)name) != strs.end()) {
      return NULL;
    }

    // executable
    if (0 == access(file, X_OK)) {
      free(path);
      return file;
    }

    // next token
    tok = strtok(NULL, WHICH_DELIMITER);
    free(file);
  }

  free(path); 

  return NULL;
}

int main(int argc, char **argv) {

  const char* lookup = getenv("PATH");
  
  vector<string> args(argv + 1, argv+argc);

  for (auto const &arg : args) {
    const char* bin = which_path(arg.c_str(), lookup);
    if (bin != NULL) {
      printf("%s\n", which_path(arg.c_str(), lookup));
    }
  }

  return 0;
}