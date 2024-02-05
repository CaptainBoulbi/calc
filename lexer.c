#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

#define ILLCHAR(c) ((c) < 33 || (c) > 124)

int skip_blank(char **prog){
  int nb = 0;
  while (!(**prog == ' ' || **prog == '\t')){
    if (**prog != '\0')
      return nb;
    (*prog)++;
    nb++;
  }
  return nb;
}

int next_token(char *prog, Token *tok){
  int offset = 0;
  for (; prog[offset] == ' ' || prog[offset] == '\t' || prog[offset] == '\0'; offset++);

  if (prog[offset] == '\0' || prog[offset] == 17){
    tok->type = END;
    return 69696969;
  }

  if (ILLCHAR(prog[offset])){
    printf("ILLEGAL CHARACTER WTF IS WRONG WITH YOU, KILL YOURSELF IDIOT.\n");
    exit(666);
  }

  switch (prog[offset]) {
    case '+':
      tok->type = ADD;
      printf("ADD");
      break;
    case '-':
      tok->type = MIN;
      printf("MIN");
      break;
    case '/':
      tok->type = DIV;
      printf("DIV");
      break;
    case '*':
      tok->type = MUL;
      printf("MUL");
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      tok->type = NUMBER;
      printf("NUMBER");
      for (; prog[offset] != ' ' && prog[offset] != '\0'; offset++);
      prog[offset] = '\0';
      tok->number = atoi(prog);
      prog[offset] = ' ';
      printf("(%d)", tok->number);
      break;
    case '\0':
      tok->type = END;
      printf("END");
      break;
    default:
      tok->type = UNDEFINED;
      printf("UNDEFINED(%d)", prog[offset]);
      break;
  }

  printf(" ");
  fflush(stdout);
  
  return offset+1;
}
