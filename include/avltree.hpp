#include <memory>

#include <iostream>

namespace BMSTU {
    template<typename K, typename V>
    class dictionary;

    template<typename K, typename V>
    class BstTree {
        friend class dictionary<K, V>;

    public:
        BstTree() : root_(nullptr), size_(0) {}

        BstTree(K key, V value) : root_(std::make_unique<TreeNode>(key, value)), size_(1) {}

// "Публичные методы"
        void Insert(K key, V value) {
            Insert(key, value, root_);
        }


        bool Contains(K key) {
            return Contains(key, root_);
        }

        void Remove(K key) {
            Remove(key, root_);
        }

        size_t size() const {
            return size_;
        }

        size_t height() {
            return HeightOfTree(root_);
        }

        void PrintOnTheSide() const {
            PrintTree(root_, 0);
        }

        void inorderTraversal() {
            inorderTraversal(root_);
        }

        void preorderTraversal() {
            preorderTraversal(root_);
        }

        void postorderTraversal() {
            postorderTraversal(root_);
        }

        struct TreeNode {
            TreeNode(K data) : key(data), value(V()), height(1), left(nullptr), right(nullptr) {};

            TreeNode(K data, V value_) : key(data), value(value_), height(1), left(nullptr), right(nullptr) {};
            K key;
            V value;
            uint8_t height;
            std::unique_ptr<TreeNode> left;
            std::unique_ptr<TreeNode> right;
        };

        std::unique_ptr<TreeNode>& GetRoot() {
            return root_;
        }

    private:
// "Узел дерева"


// "Хелперы для публичных методов"
        void RotateWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept {
            TreeNode *q = node->right.release();
            node->right.reset(q->left.release());
            TreeNode *temp = node.release();
            q->left.reset(temp);
            node.reset(q);
            FixHeight(node->left);
        }

        void RotateWithRightChild(std::unique_ptr<TreeNode> &node) noexcept {
            TreeNode *q = node->left.release();
            node->left.reset(q->right.release());
            TreeNode *temp = node.release();
            q->right.reset(temp);
            node.reset(q);
            FixHeight(node->right);
        }

        void RotateDoubleWithRightChild(std::unique_ptr<TreeNode> &node) noexcept {
            RotateWithLeftChild(node->left);
            RotateWithRightChild(node);
            FixHeight(node);
        }

        void RotateDoubleWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept {
            RotateWithRightChild(node->right);
            RotateWithLeftChild(node);
            FixHeight(node);
        }

        void FixHeight(std::unique_ptr<TreeNode> &t) noexcept {
            if (!t->right && !t->left) {
                t->height = 1;
                return;
            }
            uint8_t hl = t->left ? t->left->height : 0;
            uint8_t hr = t->right ? t->right->height : 0;
            t->height = (hl > hr ? hl : hr) + 1;
        }

        void Balance(std::unique_ptr<TreeNode> &t) {
            FixHeight(t);
            if ((t->left && t->right && t->right->height - t->left->height == 2) ||
                    (t->left == nullptr && t->right && t->right->height == 2)) {
                if ((t->right->left == nullptr) || (t->right->right && t->right->left->height <= t->right->right->height)) {
                    RotateWithLeftChild(t);
                } else {
                    RotateDoubleWithLeftChild(t);
                }
                return;
            }
            if ((t->left && t->right && t->right->height - t->left->height == -2) ||
                    (t->right == nullptr && t->left && t->left->height == 2)) {
                if ((t->left->right == nullptr) || (t->left->left && t->left->right->height <= t->left->left->height)) {
                    RotateWithRightChild(t);
                } else {
                    RotateDoubleWithRightChild(t);
                }
                return;
            }
        }

        std::unique_ptr<TreeNode> &Insert(K key, V value, std::unique_ptr<TreeNode> &node) {
            if (!node) {
                node = std::make_unique<TreeNode>(key, value);
                ++size_;
                return node;
            }
            if (key < node->key) {
                Insert(key, value, node->left);
            } else if (key > node->key) {
                Insert(key, value, node->right);
            } else {
                return node;
            }
            Balance(node);
            return node;
        }

        bool Contains(K key, std::unique_ptr<TreeNode> &node) {
            TreeNode *temp = Search(key, node);
            return temp != nullptr;
        }

        TreeNode *Search(K key, std::unique_ptr<TreeNode> &node) {
            if (!node) {
                return nullptr;
            }
            if (node->key == key) {
                return node.get();
            }
            if (key < node->key) {
                return Search(key, node->left);
            }
            return Search(key, node->right);

        }

        void Remove(K key, std::unique_ptr<TreeNode> &node) {
            if (!node) {
                return;
            } else if (key < node->key) {
                Remove(key, node->left);
            } else if (key > node->key) {
                Remove(key, node->right);
            } else if (key == node->key && !node->left && !node->right) {
                node.release();
                --size_;
            } else if (key == node->key && !node->left) {
                TreeNode *temp = node.release();
                node.reset(temp->right.release());
                --size_;
            } else if (key == node->key && !node->right) {
                TreeNode *temp = node.release();
                node.reset(temp->left.release());
                --size_;
            } else {
                TreeNode *temp = findMax(node->left).release();
                node->key = temp->key;
                if (node->left) {
                    Balance(node->left);
                }
                --size_;
            }
            if (node) {
                Balance(node);
            }
        }

        std::unique_ptr<TreeNode> &findMin(std::unique_ptr<TreeNode> &node) {
            if (!node->left) {
                return node;
            } else {
                findMin(node->left);
            }
        }

        std::unique_ptr<TreeNode> &findMax(std::unique_ptr<TreeNode> &node) const {
            if (!node->right) {
                return node;
            }
            return findMax(node->right);

        }


// "Печать на экран"
        void PrintTree(const std::unique_ptr<TreeNode> &node, int space) const {
            if (!node)
                return;
            space += 10;
            PrintTree(node->right, space);

            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << node->key << ", " << node->value << "\n";
            PrintTree(node->left, space);
        }

        uint8_t HeightOfTree(std::unique_ptr<TreeNode> &node) {
            if (node) {
                return node->height;
            }
            return 0;
        }

// "Oбходы"
        void inorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (!node) {
                return;
            }
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }

        void preorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (!node) {
                return;
            }
            std::cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }

        void postorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (!node) {
                return;
            }
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->key << " ";
        }

        std::unique_ptr<TreeNode> root_;
        size_t size_;
    };

    template<typename K, typename V>
    class dictionary {
    public:
        dictionary() : search_tree_(BstTree<K, V>()) {}

        dictionary(K key, V value) : search_tree_(key, value) {}

        V &operator[](K key) {
            return search_tree_.Search(key, search_tree_.root_)->value;
        }

        void Insert(K key, V value) {
            search_tree_.Insert(key, value);
        }

        void Remove(K key) {
            search_tree_.Remove(key);
        }

        void Print() {
            search_tree_.PrintOnTheSide();
        }

        size_t Size() {
            return search_tree_.size();
        }

        bool empty() const {
            return search_tree_.root_ == nullptr;
        }

        typename BstTree<K, V>::TreeNode *Find(K key) {
            typename BstTree<K, V>::TreeNode *temp = search_tree_.Search(key, search_tree_.root_);
            if (temp) {
                return temp;
            }
            return nullptr;
        }

        bool Contains(K key) {
            return search_tree_.Contains(key);
        }

        void Clear() {
            while (search_tree_.size() != 0) {
                search_tree_.Remove(search_tree_.root_->key);
            }
        }


    private:
        BstTree<K, V> search_tree_;
    };
}