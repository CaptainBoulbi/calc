#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

TreeNode root = {0};
TreeNode *curr = &root;

void parse(char *program, int len){
  if (len <= 0) return;
  int cursor = 0;
  Token tok = {0};

  while (cursor <= len && tok.type != END){
    cursor += next_token(program + cursor, &tok);
    switch (tok.type) {
      case ADD:
        {
        TreeNode * branch = curr;
        curr = curr->parrent;

        if (curr->left){
          curr->right = calloc(1, sizeof(TreeNode));
          curr->right->token = tok;

          curr->right->left = branch;
          curr->right->parrent = curr;
          curr = curr->right;
        } else{
          curr->left = calloc(1, sizeof(TreeNode));
          curr->left->token = tok;

          curr->left->left = branch;
          curr->left->parrent = curr;
          curr = curr->left;
        }
        }
        break;
      case NUMBER:
        if (curr->left){
          curr->right = calloc(1, sizeof(TreeNode));
          curr->right->token = tok;

          TreeNode *swap = curr;
          curr = curr->right;
          curr->parrent = swap;
        } else{
          curr->left = calloc(1, sizeof(TreeNode));
          curr->left->token = tok;

          TreeNode *swap = curr;
          curr = curr->left;
          curr->parrent = swap;
        }
        break;
      default:
        // TODO: implement default behavior
        printf("Not implemented yet.\n");
        break;
    }
  }
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
  tn->left = NULL;
  free_tree(tn->right);
  tn->right = NULL;
  free(tn);

  return;
}
