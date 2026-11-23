
typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
} Node;


// Criar um novo nó na memória
Node* create_node(int value);

// Inserir ium novo nó na árvore
Node* insert(Node *root, int value);

// Realizar uma busca recursiva na árvore
Node* search(Node *root, int value);

// Realizar uma busca iterativa na árvore
Node* search_iteractive(Node *root, int value);

Node* find_min (Node *root);

// Excluir um nó pela seu valor
Node * delete_node(Node *root, int value);

// Método auxiliar de impressão da árvore no console
void print_in_order(Node *root);

// Realizar a impressão da árvore no terminal
void print_tree(Node *root, int level);

