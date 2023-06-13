#include "stdio.h"
#include <stdlib.h>
#include <cstring>
#include <string>

int main(int argc, char** argv){
  
  if(argc < 2){
    printf("No test specified!\n");
    return 1;
  }
  
  std::string exe = argv[1];

  std::string base_filename = exe.substr(exe.find_last_of("/\\") + 1);

  printf("RUNNING %s\t", base_filename.c_str());

  FILE *fp;
  char out[6556];
  
  fp = popen(argv[1], "r");

  if(fp == NULL){
    printf("[FAIL]\n");
    return 1;
  }
  
  std::string path = "out/";
  path = path.append(base_filename).append(".test");

  FILE *of;

  of = fopen(path.c_str(), "w");
	
  char c;
  while ((c = fgetc(fp)) != -1) {
    fputc(c, of);
  }

  fclose(of);

  int exit_code = pclose(fp);
  
  printf("(%d)\t", exit_code);
  
  if(exit_code != 0){
    printf("[FAIL]\n");
    return 1;
  }

  printf("[OK]\n");

  return 0;

}
