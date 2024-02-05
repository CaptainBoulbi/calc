#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType {
  FIRST,
  ADD, MIN, MUL, DIV,
  NUMBER, DECIMAL,
  END, UNDEFINED,
  LAST,
} TokenType;

typedef struct Token {
  TokenType type;
  union {
    const char *text;
    int number;
    float decimal;
  };
} Token;

int next_token(char *prog, Token *tok);

#endif // LEXER_H
