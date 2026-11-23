#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


Node* create_node(int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert(Node *root, int value) {
    if(root == NULL) {
        return create_node(value);
    }

    if( value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

Node* search(Node *root, int value) {
    if(root == NULL) {
        return NULL;
    }

    if( root->value == value) {
        return root;
    }

    if(value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

Node* search_iteractive(Node *root, int value) {
    Node *current = root;

    while(current != NULL) {
        if(current->value == value) {
            return current;
        }

        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

Node* find_min (Node *root) {
    Node *current = root;

    while(current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

Node * delete_node(Node *root, int value) {
    Node *current = root;
    if(current == NULL) {
        return NULL;
    }

    if(value < current->value) {
        current->left = delete_node(current->left, value);
    } else if (value > current->value) {
        current->right = delete_node(current->right, value);
    } else {
        if(current->left == NULL) {
            Node *temp = current->right;
            free(current);
            return temp;
        } else if (current->right == NULL) {
            Node *temp = current->left;
            free(current);
            return temp;
        }

        Node *temp = find_min(current->right);
        current->value = temp->value;
        current->right = delete_node(current->right, temp->value);
    }

    return current;
}

void print_in_order(Node *root) {
    if(root == NULL) return;

    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

void print_tree(Node *root, int level) {
    if(root != NULL) {
        print_tree(root->right, level + 1);
        for(int i = 0; i < level; i++) {
            printf("      ");
        }
        printf("%d\n", root->value);
        print_tree(root->left, level + 1);
    }
}
