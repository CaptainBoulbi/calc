#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

TreeNode root = {0};
TreeNode *curr = &root;

void parse(Token tok){
  curr->left = malloc(sizeof(TreeNode));
  assert(curr->left && "ram issue");
  curr->left->token = tok;
  curr = curr->left;
}

void print_tree(TreeNode *tn){
  if (tn == NULL) return;

  print_tok(tn->token);
  print_tree(tn->left);
  print_tree(tn->right);

  return;
}

void free_tree(TreeNode *tn){
  if (tn == NULL) return;

  free_tree(tn->left);
  free_tree(tn->right);
  free(tn);

  return;
}
