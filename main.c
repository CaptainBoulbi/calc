#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NB 64
#define INIT_SIZE_BUFFER 1024

void getFileName(const int argc, char ** argv, char **buffer, int *file_len, int *skip_buffer, int *skip_len, const int max){
  *skip_len = 0;
  *file_len = 0;
  for (int i=1; i<argc-1; i++){
    if (*file_len >= max){
      printf("ERROR: cannot parse more than %d file.\n", MAX_FILE_NB);
      exit(-1);
    }

    if (strncmp(argv[i], "--file", 6) == 0){
      skip_buffer[(*skip_len)++] = i;
      if (*(argv[i]+6) != '\0')
        buffer[(*file_len)++] = argv[i]+2;
      else{
        buffer[(*file_len)++] = argv[++i];
        skip_buffer[(*skip_len)++] = i;
      }
    }
  }
}

void cleanArgv(const int argc, char **argv, char *buffer, int *buffer_len, const int *skip, const int skip_len, const int init_len){
  int skip_cursor = 0;
  *buffer_len = 0;
  for (int i=1; i<argc; i++){
    if (skip_cursor < skip_len && skip[skip_cursor] == i){
      skip_cursor++;
      continue;
    }

    for (int j=0; j<1024 && *(argv[i]+j) != '\0'; j++){
      if (*buffer_len >= init_len) break;
      buffer[(*buffer_len)++] = *(argv[i]+j);
    }
  }
}

int main(int argc, char **argv){
  int skip[MAX_FILE_NB] = {0};
  int skip_len = 0;
  char *file[MAX_FILE_NB] = {0};
  int file_len = 0;
  getFileName(argc, argv, file, &file_len, skip, &skip_len, MAX_FILE_NB);

  char buffer[INIT_SIZE_BUFFER] = {0};
  int buffer_len = 0;
  cleanArgv(argc, argv, buffer, &buffer_len, skip, skip_len, INIT_SIZE_BUFFER-1);

  for (int i=0; i<file_len; i++) printf("file %d: %s\n", i, file[i]);
  printf("---\n");
  for (int i=0; i<skip_len; i++) printf("skip %d: %s\n", skip[i], argv[skip[i]]);
  printf("---\n");
  printf("%s\n", buffer);
  printf("len: %d\n", buffer_len);
  
	return 0;
}
