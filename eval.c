#include "eval.h"
#include "lexer.h"

Decimal evaluate(TreeNode *tn) {
  if (!tn) return 0.0f;

  switch (tn->token.type) {
    case BEGIN:
      return evaluate(tn->left);
      break;
    case ADD:
      return evaluate(tn->left) + evaluate(tn->right);
      break;
    case NUMBER:
      return tn->token.number;
      break;
    default:
      return 0.0f;
      break;
  }
}
