#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ILLCHAR(c) (((c) < 33 && (c) != 10) || (c) > 126)
#define ISBLANKCHAR(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define ISNUM(c) ((c) >= 48 && (c) <= 57)
#define ISLETTER(c) (((c) >= 65 && (c) <= 90) || ((c) >= 97 && (c) <= 122))
#define ISNAME(c) ((c) == '_' || ISLETTER(c) || ISNUM(c))

char *lookup_TokenType[] = {
  [UNDEFINED] = "UNDEFINED", [BEGIN] = "BEGIN",
  [ADD] = "ADD", [MIN] = "MIN", [MUL] = "MUL", [DIV] = "DIV", [MOD] = "MOD",
  [NUMBER] = "NUMBER", [DECIMAL] = "DECIMAL",
  [PARENT] = "PARENT", [THESE] = "THESE",
  [NOT] = "NOT",
  [EQ] = "EQ", [GE] = "GE", [GT] = "GT", [LE] = "LE", [LT] = "LT", [NE] = "NE",
  [AND] = "AND", [OR] = "OR",
  [EQ_ASS] = "EQ_ASS", [ADD_ASS] = "ADD_ASS", [MIN_ASS] = "MIN_ASS", [MUL_ASS] = "MUL_ASS", [DIV_ASS] = "DIV_ASS", [MOD_ASS] = "MOD_ASS",
  [AND_ASS] = "AND_ASS", [OR_ASS] = "OR_ASS", [XOR_ASS] = "XOR_ASS", [NOT_ASS] = "NOT_ASS",
  [LEFT_SHIFT_ASS] = "LEFT_SHIFT_ASS", [RIGHT_SHIFT_ASS] = "RIGHT_SHIFT_ASS",
  [BIT_AND] = "BIT_AND", [BIT_OR] = "BIT_OR", [BIT_XOR] = "BIT_XOR", [BIT_NOT] = "BIT_NOT",
  [LEFT_SHIFT] = "LEFT_SHIFT", [RIGHT_SHIFT] = "RIGHT_SHIFT",
  [TEXT] = "TEXT",
  [END] = "END",
};

int next_token(char *prog, Token *tok){
  int offset = 0;
  while (ISBLANKCHAR(prog[offset])) offset++;

  if (prog[offset] == '\0' || prog[offset] == 17){
    tok->type = END;
    return 69696969;
  }

  if (ILLCHAR(prog[offset])){
    printf("(%d) ILLEGAL CHARACTER: WTF IS WRONG WITH YOU, KILL YOURSELF IDIOT.\n", prog[offset]);
    exit(666);
  }

  switch (prog[offset]) {
    case '(':
      tok->type = PARENT;
      break;
    case ')':
      tok->type = THESE;
      break;
    case '+':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = ADD_ASS;
      } else{
        tok->type = ADD;
      }
      break;
    case '-':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = MIN_ASS;
      } else {
        tok->type = MIN;
      }
      break;
    case '/':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = DIV_ASS;
      } else {
        tok->type = DIV;
      }
      break;
    case '*':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = MUL_ASS;
      } else {
        tok->type = MUL;
      }
      break;
    case '%':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = MOD_ASS;
      } else {
        tok->type = MOD;
      }
      break;
    case '=':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = EQ_ASS;
      } else {
        tok->type = EQ;
      }
      break;
    case '<':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = LE;
      } else if (prog[offset+1] == '<'){
        offset++;
        if (prog[offset+1] == '='){
          offset++;
          tok->type = LEFT_SHIFT_ASS;
        } else {
          tok->type = LEFT_SHIFT;
        }
      } else {
        tok->type = LT;
      }
      break;
    case '>':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = GE;
      } else if (prog[offset+1] == '>'){
        offset++;
        if (prog[offset+1] == '='){
          offset++;
          tok->type = RIGHT_SHIFT_ASS;
        } else {
          tok->type = RIGHT_SHIFT;
        }
      } else {
        tok->type = GT;
      }
      break;
    case '!':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = NE;
      } else {
        tok->type = NOT;
      }
      break;
    case '&':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = AND_ASS;
      } else if (prog[offset+1] == '&'){
        offset++;
        tok->type = AND;
      } else {
        tok->type = BIT_AND;
      }
      break;
    case '~':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = NOT_ASS;
      } else {
        tok->type = BIT_NOT;
      }
      break;
    case '^':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = XOR_ASS;
      } else {
        tok->type = BIT_XOR;
      }
      break;
    case '|':
      if (prog[offset+1] == '='){
        offset++;
        tok->type = OR_ASS;
      } else if (prog[offset+1] == '|'){
        offset++;
        tok->type = OR;
      } else {
        tok->type = BIT_OR;
      }
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
      if (ISNAME(prog[offset])){
        tok->type = TEXT;
        int onset = 0;
        while (ISNAME(prog[offset+onset])) onset++;
        tok->text = malloc(onset);
        assert(tok->text && "ram issue");
        tok->len = onset;
        strncpy(tok->text, &prog[offset], onset);
        offset += onset-1;
      }else{
        tok->type = UNDEFINED;
      }
      break;
  }
  
  return offset+1;
}

void print_tok(Token tok){
  if (tok.type > END || tok.type < BEGIN) return;

  printf("%s", lookup_TokenType[tok.type]);
  fflush(stdout);
  switch (tok.type) {
    case NUMBER:
      printf("(%d) ", tok.number);
      break;
    case DECIMAL:
      printf("(%.2f) ", tok.decimal);
      break;
    case TEXT:
      printf("(%.*s) ", tok.len, tok.text);
      break;
    default:
      break;
  }
}

int token_equals(Token tok1, Token tok2){
  if (tok1.type != tok2.type) {
    return 0;
  }

  switch (tok1.type) {
    case NUMBER:
      return tok1.number == tok2.number;
    case DECIMAL:
      return tok1.decimal == tok2.decimal;
    case TEXT:
      if (tok1.len != tok2.len)
        return 0;
      return strncmp(tok1.text, tok2.text, tok1.len);
    default:
      return 1;
  }
}
