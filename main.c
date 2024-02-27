#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "eval.h"
#include "lexer.h"
#include "parser.h"

#define MAX_FILE_NB 64
#define INIT_SIZE_BUFFER 1024

void getUserInput(int argc, char **argv, char **file, int *file_len,  char *program,  int *program_len, int *program_cap){
  int skip_buffer[MAX_FILE_NB];
  int skip_len = 0;
  *file_len = 0;
  for (int i=1; i<argc-1; i++){
    if (*file_len >= MAX_FILE_NB){
      printf("ERROR: cannot parse more than %d file.\n", MAX_FILE_NB);
      exit(-1);
    }

    if (strncmp(argv[i], "--file", 6) == 0){
      skip_buffer[skip_len++] = i;
      if (*(argv[i]+6) != '\0')
        file[(*file_len)++] = argv[i]+2;
      else{
        file[(*file_len)++] = argv[++i];
        skip_buffer[skip_len++] = i;
      }
    }
  }

  int skip_cursor = 0;
  *program_len = 0;
  for (int i=1; i<argc; i++){
    if (skip_cursor < skip_len && skip_buffer[skip_cursor] == i){
      skip_cursor++;
      continue;
    }

    for (int j=0; j<1024 && *(argv[i]+j) != '\0'; j++){
      if (*program_len >= *program_cap){
        *program_cap *= 2;
        program = realloc(program, *program_cap);
      }
      program[(*program_len)++] = *(argv[i]+j);
    }
    if (*program_len >= *program_cap){
      *program_cap *= 2;
      program = realloc(program, *program_cap);
    }
    program[(*program_len)++] = ' ';
  }
}

void interprete(char *program, int len){
  if (len <= 0) return;

  parse(program, len);
}

void interprete_from_file(char *file){
  FILE *f = fopen(file, "rb");
  if (!f){
    printf("ERROR: could not open file %s: %s\n", file, strerror(errno));
    exit(69);
  }

  if (fseek(f, 0, SEEK_END) < 0){
    printf("ERROR: could not seek file %s: %s\n", file, strerror(errno));
    exit(69);
  }

  long fsize = ftell(f);
  if (fsize < 0){
    printf("ERROR: could not tell file %s: %s\n", file, strerror(errno));
    exit(69);
  }

  /* same as rewind(f); */
  if (fseek(f, 0, SEEK_SET) < 0){
    printf("ERROR: could not seek file %s: %s\n", file, strerror(errno));
    exit(69);
  }

  char *buffer = malloc(fsize + 1);
  buffer[fsize] = 0;

  if (fread(buffer, fsize, 1, f) == 0){
    printf("ERROR: could not read file %s: %s\n", file, strerror(errno));
    exit(69);
  }
  fclose(f);

  interprete(buffer, fsize);
  free(buffer);
}

int main(int argc, char **argv){
  char *file[MAX_FILE_NB] = {0};
  int file_len = 0;
  char *program = malloc(INIT_SIZE_BUFFER);
  assert(program && "ram issue");
  int program_len = 0;
  int program_cap = INIT_SIZE_BUFFER;

  getUserInput(argc, argv, file, &file_len, program, &program_len, &program_cap);

  for (int i=0; i<file_len; i++){
    interprete_from_file(file[i]);
  }

  interprete(program, program_len);

#if 0
  Decimal resultat = evaluate(&root);
  printf("resultat = %f\n", resultat);
#endif

  print_tree(&root, 0);

  free_tree(root.left);
  free_tree(root.right);
  free(program);
	return 0;
}
