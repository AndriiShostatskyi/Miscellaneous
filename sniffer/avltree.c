#include "avltree.h"

// Get height of the tree
int height(struct Node *n)
{
    return n ? n->height : 0;
}

// Get maximum of two integers
int max(int a, int b)
{
    return a > b ? a : b;
}

// Allocates a new node with the given ip (ip) and NULL left and right pointers.
struct Node* newNode(unsigned int ip)
{
  struct Node* n = (struct Node*) malloc(sizeof(struct Node));
  n->ip     = ip;
	n->cnt    = n->height = 1;
  n->left   = n->right = NULL;
  return n;
}

// Iterative function to find the node that has the given ip (ip) or is the closest to that
struct Node *_find(struct Node *r, unsigned int ip) {
  struct Node *root = r;
	while(root) {
	  if(root->ip > ip)
			root = root->left;
		else if (root->ip < ip)
			root = root->right;
		else return root;
	}
	return root;
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

// Left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert ip (ip) in subtree rooted with node and returns new root of subtree.
struct Node* insert(struct Node* node, unsigned int ip)
{
    // 1.  Perform the normal BST insertion

    if (!node) return newNode(ip);
    if (ip < node->ip)
        node->left  = insert(node->left, ip);
    else if (ip > node->ip)
        node->right = insert(node->right, ip);
    else
        return node;

    // 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && ip < node->left->ip)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && ip > node->right->ip)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && ip > node->left->ip)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && ip < node->right->ip)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void saveInPreOrder(struct Node *root, FILE *fp)
{
  static char str[32];
  if(root) {
    saveInPreOrder(root->left, fp);
    saveInPreOrder(root->right, fp);
    strcpy(str, (char*)_unhash(root->ip));
	//	printf("%s", str);
    fputs(str, fp);
		int i = sprintf(str,"%u", root->cnt);
    strcat(str, "\n");
  //  printf("%u\n", root->cnt);
    fputs(str, fp);
  }
}

void preOrder(struct Node *root)
{
	FILE *fp = fopen("ips_stat.txt", "a+b");
  saveInPreOrder(root, fp);
  fclose(fp), fp = NULL;
}
