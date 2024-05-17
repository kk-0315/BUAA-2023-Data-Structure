#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

typedef struct _Node {
    char value;
    struct _Node *left;
    struct _Node *right;
} Node;

int get_index(char c, const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            return i;
        }
    }
    return -1;
}

Node *build_tree(const char *preorder, const char *inorder, int size) {
    if (size == 0) {
        return NULL;
    }

    char value = preorder[0];
    int index = get_index(value, inorder);

    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->left = build_tree(preorder+1, inorder, index);
    node->right = build_tree(preorder+1+index, inorder+1+index, size-1-index);

    return node;
}

void postorder_traversal(Node *node) {
    if (node == NULL) {
        return;
    }

    postorder_traversal(node->left);
    postorder_traversal(node->right);
    printf("%c ", node->value);
}

int main() {
    char preorder[MAX_NODES];
    char inorder[MAX_NODES];
    printf("Please enter the preorder sequence: ");
    scanf("%s", preorder);
    printf("Please enter the inorder sequence: ");
    scanf("%s", inorder);

    Node *root = build_tree(preorder, inorder, strlen(preorder));
    printf("The postorder sequence is: ");
    postorder_traversal(root);

    return 0;
}