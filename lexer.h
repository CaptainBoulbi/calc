#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType {
  FIRST,
  ADD, MIN, MUL, DIV, MOD,
  NUMBER, DECIMAL,
  PARENT, THESE,
  NOT,
  EQ, GE, GT, LE, LT, NE,
  AND, OR,
  EQ_ASS, ADD_ASS, MIN_ASS, MUL_ASS, DIV_ASS, MOD_ASS,
  AND_ASS, OR_ASS, XOR_ASS, NOT_ASS,
  LEFT_SHIFT_ASS, RIGHT_SHIFT_ASS,
  BIT_AND, BIT_OR, BIT_XOR, BIT_NOT,
  LEFT_SHIFT, RIGHT_SHIFT,
  TEXT,
  END, UNDEFINED,
  LAST,
} TokenType;

typedef double Decimal;

typedef struct Token {
  TokenType type;
  union {
    struct {
      char *text;
      int len;
    };
    int number;
    Decimal decimal;
  };
} Token;

int next_token(char *prog, Token *tok);

#endif // LEXER_H
