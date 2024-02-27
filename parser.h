#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct TreeNode {
  Token token;
  struct TreeNode *parrent;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

extern TreeNode root;

void print_tree(TreeNode *tn, int level);
void free_tree(TreeNode *tn);
void parse(char *program, int len);

#endif // PARSER_H
