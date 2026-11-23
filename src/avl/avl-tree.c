#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

static int node_height(const AVLNode *node) {
    return node != NULL ? node->height : 0;
}

static int max_int(int a, int b) {
    return a > b ? a : b;
}

static void update_height(AVLNode *node) {
    node->height = 1 + max_int(node_height(node->left), node_height(node->right));
}

static int balance_factor(const AVLNode *node) {
    return node_height(node->left) - node_height(node->right);
}

static AVLNode *create_node(int key) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node == NULL) {
        fprintf(stderr, "Error: out of memory while creating AVL node\n");
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static AVLNode *rotate_right(AVLTree *tree, AVLNode *y) {
    AVLNode *x = y->left;

    y->left = x->right;
    x->right = y;

    update_height(y);
    update_height(x);

    tree->rotations++;
    return x;
}

static AVLNode *rotate_left(AVLTree *tree, AVLNode *x) {
    AVLNode *y = x->right;

    x->right = y->left;
    y->left = x;

    update_height(x);
    update_height(y);

    tree->rotations++;
    return y;
}

static AVLNode *rebalance(AVLTree *tree, AVLNode *node) {
    update_height(node);
    int balance = balance_factor(node);

    if (balance > 1 && balance_factor(node->left) >= 0) {
        return rotate_right(tree, node);
    }

    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = rotate_left(tree, node->left);
        return rotate_right(tree, node);
    }

    if (balance < -1 && balance_factor(node->right) <= 0) {
        return rotate_left(tree, node);
    }

    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rotate_right(tree, node->right);
        return rotate_left(tree, node);
    }

    return node;
}

static AVLNode *insert_node(AVLTree *tree, AVLNode *node, int key) {
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert_node(tree, node->left, key);
    } else if (key > node->key) {
        node->right = insert_node(tree, node->right, key);
    } else {
        return node;
    }

    return rebalance(tree, node);
}

static int validate_node(const AVLNode *node, long long lower, long long upper) {
    if (node == NULL) {
        return 0;
    }

    if (node->key <= lower || node->key >= upper) {
        fprintf(stderr, "AVL validation failed: key %d breaks the BST property\n", node->key);
        return -1;
    }

    int left_height = validate_node(node->left, lower, node->key);
    if (left_height < 0) {
        return -1;
    }

    int right_height = validate_node(node->right, node->key, upper);
    if (right_height < 0) {
        return -1;
    }

    int real_height = 1 + max_int(left_height, right_height);
    if (node->height != real_height) {
        fprintf(stderr, "AVL validation failed: node %d stores height %d but real height is %d\n",
                node->key, node->height, real_height);
        return -1;
    }

    int balance = left_height - right_height;
    if (balance < -1 || balance > 1) {
        fprintf(stderr, "AVL validation failed: node %d has balance factor %d\n", node->key, balance);
        return -1;
    }

    return real_height;
}

static void free_nodes(AVLNode *node) {
    if (node == NULL) {
        return;
    }

    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
}

void avl_init(AVLTree *tree) {
    tree->root = NULL;
    tree->rotations = 0;
}

void avl_insert(AVLTree *tree, int key) {
    tree->root = insert_node(tree, tree->root, key);
}

bool avl_search(const AVLTree *tree, int key) {
    const AVLNode *current = tree->root;

    while (current != NULL) {
        if (key == current->key) {
            return true;
        }

        current = key < current->key ? current->left : current->right;
    }

    return false;
}

int avl_get_height(const AVLTree *tree) {
    return node_height(tree->root);
}

long long avl_get_rotations(const AVLTree *tree) {
    return tree->rotations;
}

bool avl_validate(const AVLTree *tree) {
    return validate_node(tree->root, LLONG_MIN, LLONG_MAX) >= 0;
}

void avl_free(AVLTree *tree) {
    free_nodes(tree->root);
    avl_init(tree);
}
