#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

#define ILLCHAR(c) ((c) < 33 || (c) > 124)
#define ISNUM(c) ((c) >= 48 && (c) <= 57)

int next_token(char *prog, Token *tok){
  int offset = 0;
  for (; prog[offset] == ' ' || prog[offset] == '\t' || prog[offset] == '\0'; offset++);

  if (prog[offset] == '\0' || prog[offset] == 17){
    tok->type = END;
    return 69696969;
  }

  if (ILLCHAR(prog[offset])){
    printf("(%d) ILLEGAL CHARACTER WTF IS WRONG WITH YOU, KILL YOURSELF IDIOT.\n", prog[offset]);
    exit(666);
  }

  switch (prog[offset]) {
    case '+':
      tok->type = ADD;
      break;
    case '-':
      tok->type = MIN;
      break;
    case '/':
      tok->type = DIV;
      break;
    case '*':
      tok->type = MUL;
      break;
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      tok->type = NUMBER;
      for (; ISNUM(prog[offset]); offset++);
      if (prog[offset] == '.'){
        tok->type = DECIMAL;
        offset++;
        for (; ISNUM(prog[offset]); offset++);
      }
      char swap = prog[offset];
      prog[offset] = '\0';
      if (tok->type == NUMBER)
        tok->number = atoi(prog);
      else if (tok->type == DECIMAL)
        tok->decimal = atof(prog);
      prog[offset] = swap;
      offset--;
      break;
    case '\0':
      tok->type = END;
      break;
    default:
      tok->type = UNDEFINED;
      break;
  }

  fflush(stdout);
  
  return offset+1;
}
