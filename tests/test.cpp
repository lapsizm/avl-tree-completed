#include "../include/avltree.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(DictTests, Construct) {
    BMSTU::dictionary<int, int> dict;
    EXPECT_EQ(dict.Size(), 0);
    EXPECT_EQ(dict.empty(), true);

    BMSTU::dictionary<int, std::string> dict2(2, "hello world");
    EXPECT_EQ(dict2[2], "hello world");
    EXPECT_EQ(dict2.Size(), 1);
    EXPECT_EQ(dict2.empty(), false);
}

TEST(DictTests, Functions) {
    BMSTU::dictionary<int, int> dict;
    dict.Insert(2, 3);
    dict.Insert(13, 12);
    dict.Insert(14, 13);
    EXPECT_EQ(dict.Size(), 3);
    EXPECT_EQ(dict.Find(13)->value, dict[13]);
    dict.Remove(13);
    EXPECT_EQ(dict.Contains(13), false);
    EXPECT_EQ(dict.Size(), 2);
    dict.Clear();
    EXPECT_EQ(dict.empty(), true);
}

TEST(AVLTreeTests, Construct){
    BMSTU::BstTree<int,int> tree;
    EXPECT_EQ(tree.height(), 0);
    EXPECT_EQ(tree.size(), 0);

    BMSTU::BstTree<char,std::string> tree2('a', "privet mir");
    EXPECT_EQ(tree2.height(), 1);
    EXPECT_EQ(tree2.size(), 1);
    EXPECT_EQ(tree2.Contains('a'), true);
}

TEST(AVLTreeTests, InsertRotates){
    BMSTU::BstTree<int,int> tree;
    tree.Insert(1,1);
    tree.Insert(2,2);
    tree.Insert(3,3);
    //Single Rotate left
    EXPECT_EQ(tree.height(), 2);
    EXPECT_EQ(tree.GetRoot()->key, 2);
    EXPECT_EQ(tree.GetRoot()->left->key, 1);
    EXPECT_EQ(tree.GetRoot()->right->key, 3);

    BMSTU::BstTree<int,int> tree2;
    tree2.Insert(3,3);
    tree2.Insert(2,2);
    tree2.Insert(1,1);
    //Single Rotate right
    EXPECT_EQ(tree2.height(), 2);
    EXPECT_EQ(tree2.GetRoot()->key, 2);
    EXPECT_EQ(tree2.GetRoot()->left->key, 1);
    EXPECT_EQ(tree2.GetRoot()->right->key, 3);

    BMSTU::BstTree<int,int> tree3;
    tree3.Insert(20,1);
    tree3.Insert(10,2);
    tree3.Insert(30,3);
    tree3.Insert(25,4);
    tree3.Insert(26,3);
    //Double Rotate Right
    EXPECT_EQ(tree3.height(), 3);
    EXPECT_EQ(tree3.GetRoot()->key, 20);
    EXPECT_EQ(tree3.GetRoot()->left->key, 10);
    EXPECT_EQ(tree3.GetRoot()->right->key, 26);
    EXPECT_EQ(tree3.GetRoot()->right->left->key, 25);
    EXPECT_EQ(tree3.GetRoot()->right->right->key, 30);

    BMSTU::BstTree<int,int> tree4;
    tree4.Insert(20,1);
    tree4.Insert(10,2);
    tree4.Insert(30,3);
    tree4.Insert(12,3);
    tree4.Insert(11,3);
    //Double Rotate left
    EXPECT_EQ(tree4.height(), 3);
    EXPECT_EQ(tree4.GetRoot()->key, 20);
    EXPECT_EQ(tree4.GetRoot()->left->key, 11);
    EXPECT_EQ(tree4.GetRoot()->right->key, 30);
    EXPECT_EQ(tree4.GetRoot()->left->left->key, 10);
    EXPECT_EQ(tree4.GetRoot()->left->right->key, 12);
}

TEST(AVLTreeTests, RemoveTests){
    BMSTU::BstTree<int,int> tree4;
    tree4.Insert(20,1);
    tree4.Insert(10,2);
    tree4.Insert(30,3);
    tree4.Insert(12,3);
    tree4.Insert(11,3);

    tree4.Remove(11);
    EXPECT_EQ(tree4.height(), 3);
    EXPECT_EQ(tree4.GetRoot()->key, 20);
    EXPECT_EQ(tree4.GetRoot()->left->key, 10);
    EXPECT_EQ(tree4.GetRoot()->right->key, 30);
    EXPECT_EQ(tree4.GetRoot()->left->left, nullptr);
    EXPECT_EQ(tree4.GetRoot()->left->right->key, 12);

    tree4.Remove(20);
    EXPECT_EQ(tree4.height(), 2);
    EXPECT_EQ(tree4.size(), 3);
    EXPECT_EQ(tree4.GetRoot()->key, 12);
    EXPECT_EQ(tree4.GetRoot()->left->key, 10);
    EXPECT_EQ(tree4.GetRoot()->right->key, 30);
}

