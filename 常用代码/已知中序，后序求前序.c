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

Node *build_tree(const char *inorder, const char *postorder, int size) {
    if (size == 0) {
        return NULL;
    }

    char value = postorder[size-1];
    int index = get_index(value, inorder);

    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->left = build_tree(inorder, postorder, index);
    node->right = build_tree(inorder+index+1, postorder+index, size-1-index);

    return node;
}

void preorder_traversal(Node *node) {
    if (node == NULL) {
        return;
    }

    printf("%c ", node->value);
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

int main() {
    char inorder[MAX_NODES];
    char postorder[MAX_NODES];
    printf("Please enter the inorder sequence: ");
    scanf("%s", inorder);
    printf("Please enter the postorder sequence: ");
    scanf("%s", postorder);

    Node *root = build_tree(inorder, postorder, strlen(inorder));
    printf("The preorder sequence is: ");
    preorder_traversal(root);

    return 0;
}