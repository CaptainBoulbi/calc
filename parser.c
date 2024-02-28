#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define PRIORITY(tok, p) ((tok) > (p) && (tok) < PRIORITY_END)

TreeNode root = {
    .token   = { .type = BEGIN },
    .parrent = NULL,
    .left    = NULL,
    .right   = NULL,
};
TreeNode *curr = &root;

void insert_parrent(Token tok){
    TreeNode * branch = curr;
    curr = curr->parrent;

    if (curr->left){
        curr->left = calloc(1, sizeof(TreeNode));
        curr->left->token = tok;

        curr->left->left = branch;
        curr->left->parrent = curr;
        curr = curr->left;
    } else{
        curr->right = calloc(1, sizeof(TreeNode));
        curr->right->token = tok;

        curr->right->left = branch;
        curr->right->parrent = curr;
        curr = curr->right;
    }
}

void insert_current(Token tok){
    TreeNode *to;
    if (curr->left){
        to = curr->right = calloc(1, sizeof(TreeNode));
    } else{
        to = curr->left = calloc(1, sizeof(TreeNode));
    }

    to->token = tok;
    to->parrent = curr;
    curr = to;
}

void parse(char *program, int len){
    if (len <= 0) return;
    int cursor = 0;
    Token tok = {0};

    while (cursor <= len && tok.type != END){
        cursor += next_token(program + cursor, &tok);
        switch (tok.type) {
            case MIN:
                // TODO: implement -NUMBER operation
            case ADD:
                while (PRIORITY(curr->parrent->token.type, P0)) curr = curr->parrent;
                insert_parrent(tok);
                break;
            case DIV:
            case MOD:
            case MUL:
                while (PRIORITY(curr->parrent->token.type, P1)) curr = curr->parrent;
                insert_parrent(tok);
                break;
            case NUMBER:
                insert_current(tok);
                break;
            case END:
                return;
                break;
            default:
                // TODO: implement default behavior
                printf("[%s] Not implemented yet.\n", lookup_TokenType[tok.type]);
                break;
        }
    }
}

void print_tree(TreeNode *tn, int level){
    if (tn == NULL) return;

    for (int i=0; i<level; i++) printf("  ");
    print_tok(tn->token);
    printf("\n");
    print_tree(tn->left, level+1);
    print_tree(tn->right, level+1);

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
