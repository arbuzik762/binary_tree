#include <cstdio>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    bool contains(Node* node, const T& value) const {
        if (!node) return false;
        if (node->data == value) return true;
        return value < node->data ? contains(node->left, value) : contains(node->right, value);
    }

    void inOrder(Node* node) const {
        if (!node) return;
        inOrder(node->left);
        printf("%d ", node->data);
        inOrder(node->right);
    }

    void preOrder(Node* node) const {
        if (!node) return;
        printf("%d ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) const {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        printf("%d ", node->data);
    }

    size_t size(Node* node) const {
        return node ? 1 + size(node->left) + size(node->right) : 0;
    }

    size_t height(Node* node) const {
        if (!node) return 0;
        size_t leftHeight = height(node->left);
        size_t rightHeight = height(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clear(root);
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    bool contains(const T& value) const {
        return contains(root, value);
    }

    void inOrder() const {
        inOrder(root);
        printf("\n");
    }

    void preOrder() const {
        preOrder(root);
        printf("\n");
    }

    void postOrder() const {
        postOrder(root);
        printf("\n");
    }

    size_t size() const {
        return size(root);
    }

    size_t height() const {
        return height(root);
    }

    bool empty() const {
        return !root;
    }
};

int main() {
    BinaryTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    printf("Левое - узел - правое: ");
    tree.inOrder();

    printf("Узел - левое - правое: ");
    tree.preOrder();

    printf("Левое - узел - правое: ");
    tree.postOrder();

    printf("Значение 1: %s\n", tree.contains(10) ? "Есть" : "Нет");
    printf("Значение 2: %s\n", tree.contains(90) ? "Есть" : "Нет");

    printf("Кол-во узлов: %zu\n", tree.size());
    printf("Высота дерева: %zu\n", tree.height());

    return 0;
}
