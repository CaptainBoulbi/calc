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
    case MIN:
      return evaluate(tn->left) - evaluate(tn->right);
      break;
    case MUL:
      return evaluate(tn->left) * evaluate(tn->right);
      break;
    case DIV:
      return evaluate(tn->left) / evaluate(tn->right);
      break;
    case MOD:
      {
        int l = evaluate(tn->left);
        int r = evaluate(tn->right);
        return l % r;
      }
      break;
    case EQ:
      return evaluate(tn->left) == evaluate(tn->right);
      break;
    case NE:
      return evaluate(tn->left) != evaluate(tn->right);
      break;
    case LT:
      return evaluate(tn->left) < evaluate(tn->right);
      break;
    case LE:
      return evaluate(tn->left) <= evaluate(tn->right);
      break;
    case GT:
      return evaluate(tn->left) > evaluate(tn->right);
      break;
    case GE:
      return evaluate(tn->left) >= evaluate(tn->right);
      break;
    case AND:
      return evaluate(tn->left) && evaluate(tn->right);
      break;
    case OR:
      return evaluate(tn->left) || evaluate(tn->right);
      break;
    case NUMBER:
      return tn->token.number;
      break;
    case DECIMAL:
      return tn->token.decimal;
      break;
    default:
      return 0.0f;
      break;
  }
}
