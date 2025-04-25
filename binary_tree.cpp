#include <stdio.h>
#include <stdlib.h>
#include <ctime>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Создание нового узла
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Рекурсивная вставка значения в дерево
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }
    
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

// Рекурсивный обход в прямом порядке (корень-лево-право)
void pre_order(Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        pre_order(root->left);
        pre_order(root->right);
    }
}

// Рекурсивный обход в симметричном порядке (лево-корень-право)
void in_order(Node* root) {
    if (root != NULL) {
        in_order(root->left);
        printf("%d ", root->value);
        in_order(root->right);
    }
}

// Рекурсивный обход в обратном порядке (лево-право-корень)
void post_order(Node* root) {
    if (root != NULL) {
        post_order(root->left);
        post_order(root->right);
        printf("%d ", root->value);
    }
}

// Рекурсивная очистка дерева
void clear_tree(Node* root) {
    if (root != NULL) {
        clear_tree(root->left);
        clear_tree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int i, count = 10;
    int min = 1, max = 100;
    
    srand(time(NULL));
    
    printf("Элементы: ");
    for (i = 0; i < count; i++) {
        int value = min + rand() % (max - min + 1);
        printf("%d ", value);
        root = insert(root, value);
    }
    printf("\n\n");
    
    // Обходы дерева
    printf("Узел - левое - правое: ");
    pre_order(root);
    printf("\n");
    
    printf("Левое - узел - правое: ");
    in_order(root);
    printf("\n");
    
    printf("Левое - правое - узел: ");
    post_order(root);
    printf("\n");
    
    // Очистка памяти
    clear_tree(root);
    
    return 0;
}
