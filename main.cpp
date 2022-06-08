#include <iostream>
#include <memory>

namespace BMSTU {
    template<typename K, typename V>
    class dictionary;

    template<typename K, typename V>
    class BstTree {
        friend class dictionary<K, V>;

    public:
        BstTree() : root_(nullptr), size_(0) {}

// "Публичные методы"
        void Insert(K value) {
            Insert(value, root_);
        }



//        bool Contains(K value) {
//
//        }
//
        void Remove(K value) {
            Remove(value, root_);
        }
//
//        size_t size() const {}
//
//        size_t height() {
//            return root_->height;
//        }
//
//        void Print() const {}
//
//        void Draw() {}
//
//        void inorderTraversal() {}
//
//        void preorderTraversal() {}
//
//        void postorderTraversal() {}

    private:
// "Узел дерева"
        struct TreeNode {
            TreeNode(K data) : key(data), value(V()), height(1), left(nullptr), right(nullptr) {};

            TreeNode(K data, V value_) : key(data), value(value_), height(1), left(nullptr), right(nullptr) {};
            K key;
            V value;
            uint8_t height;
            std::unique_ptr<TreeNode> left;
            std::unique_ptr<TreeNode> right;
        };

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
            if (t->left && t->right && t->right->height - t->left->height == 2 ||
                t->left == nullptr && t->right && t->right->height == 2) {
                if (t->right->left == nullptr || t->right->left->height <= t->right->right->height) {
                    RotateWithLeftChild(t);
                } else {
                    RotateDoubleWithLeftChild(t);
                }
                return;
            }
            if (t->left && t->right && t->right->height - t->left->height == -2 ||
                t->right == nullptr && t->left && t->left->height == 2) {
                if (t->left->right == nullptr || t->left->left && t->left->right->height <= t->left->left->height) {
                    RotateWithRightChild(t);
                } else {
                    RotateDoubleWithRightChild(t);
                }
                return;
            }
        }

        std::unique_ptr<TreeNode> &Insert(K value, std::unique_ptr<TreeNode> &node) {
            if (!node) {
                node = std::make_unique<TreeNode>(value);
                ++size_;
                return node;
            }
            if (value < node->key) {
                Insert(value, node->left);
            } else if (value > node->key) {
                Insert(value, node->right);
            } else {
                return node;
            }
            Balance(node);
        }

        bool Contains(K value, std::unique_ptr<TreeNode> &node) {
            TreeNode* temp = Search(value, node);
            return temp != nullptr;
        }

        TreeNode *Search(K key, std::unique_ptr<TreeNode> &node) {
            if(!node){
                return nullptr;
            }
            if(node->key == key){
                return node.get();
            }
            if(key < node->key){
                return Search(key, node->left);
            }
            if(key > node->key){
                return Search(key, node->right);
            }

        }

//
        void Remove(K value, std::unique_ptr<TreeNode> &node) {
            if(!node){
                return;
            }
            else if(value < node->key){
                Remove(value, node->left);
            }
            else if(value > node->key){
                Remove(value, node->right);
            }
            else if(value == node->key && !node->left && !node->right){
                node.release();
                --size_;
            }
            else if(value == node->key && !node->left){
                TreeNode* temp = node.release();
                node.reset(temp->right.release());
                --size_;
            }
            else if(value == node->key && !node->right){
                TreeNode* temp = node.release();
                node.reset(temp->left.release());
                --size_;
            }
            else{
                TreeNode* temp = node.release();
                node.reset(findMax(temp->left).release());
                --size_;
            }
            if(node){
                Balance(node);
            }
        }

        std::unique_ptr<TreeNode> &findMin(std::unique_ptr<TreeNode> &node) {
            if(!node->left){
                return node;
            }
            else{
                findMin(node->left);
            }
        }

        std::unique_ptr<TreeNode> &findMax(std::unique_ptr<TreeNode> &node) const {
            if(!node->right){
                return node;
            }
            else{
                findMax(node->right);
            }
        }


// "Печать на экран"
        void PrintTree(const std::unique_ptr<TreeNode> &node, int space) const {}

        uint8_t HeightOfTree(std::unique_ptr<TreeNode> &node) {
            if (node) {
                return node->height;
            }
            return 0;
        }

// "Oбходы"
        void inorderTraversal(std::unique_ptr<TreeNode> &node) {}

        void preorderTraversal(std::unique_ptr<TreeNode> &node) {}

        void postorderTraversal(std::unique_ptr<TreeNode> &node) {}

        std::unique_ptr<TreeNode> root_;
        size_t size_;
    };

    template<typename K, typename V>
    class dictionary {
    public:
        dictionary() : search_tree_(BstTree<K, V>()) {}

        V &operator[](K key) {}

    public:
        void Insert(K key, V value) {}

        BstTree<K, V> search_tree_;
    };
}

int main() {
    BMSTU::BstTree<int, int> tree;
    tree.Insert(20);
    tree.Insert(10);
    tree.Insert(30);
    tree.Insert(12);
    tree.Remove(20);
    return 0;
}
