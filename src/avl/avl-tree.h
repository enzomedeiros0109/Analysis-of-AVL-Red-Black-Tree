#ifndef AVL_TREE_H
#define AVL_TREE_H


typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
    long long rotations;
} AVLTree;

void avl_init(AVLTree *tree);

void avl_insert(AVLTree *tree, int key);

bool avl_search(const AVLTree *tree, int key);

int avl_get_height(const AVLTree *tree);

long long avl_get_rotations(const AVLTree *tree);

bool avl_validate(const AVLTree *tree);

void avl_free(AVLTree *tree);

#endif
