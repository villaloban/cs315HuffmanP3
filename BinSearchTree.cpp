//
// Created by Anthony Villalobos on 10/14/25.
//
#include <optional>
#include "BinSearchTree.hpp"

void BinSearchTree::destroy(TreeNode *node) noexcept {
    if (node == nullptr)
        return;
    destroy(node->leftSubtree());
    destroy(node->rightSubtree());
    delete node;
}


BinSearchTree::~BinSearchTree() {
    destroy(root_);
}



void BinSearchTree::insert(const std::string &word) {
    root_ = insertHelper(this->root_, word);
}

TreeNode *BinSearchTree::insertHelper(TreeNode *node, const std::string &word) {
    if (node == nullptr)
        return new TreeNode(word);
    if (word < node->value() )
        node->leftSubtree(insertHelper(node->leftSubtree(), word));
    else if (word > node->value())
        node->rightSubtree(insertHelper(node->rightSubtree(), word));
    else
        node->incrementCount();
    return node;

}

void BinSearchTree::bulkInsert(const std::vector<std::string> &words) {
    for (const auto & word : words) {
        root_ = insertHelper(this->root_, word);
    }
}

bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(this->root_, word);

}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    const TreeNode* node = findNode(root_, word);
    if (node == nullptr)
        return 0;
    return  node->getCount();

}


const TreeNode *BinSearchTree::findNode(const TreeNode *node, std::string_view word) noexcept {
    if (node == nullptr)
        return nullptr;

    if (word < node->value())
        return findNode(node->leftSubtree(), word);
    if (word >node->value())
        return findNode(node->rightSubtree(), word);
    return node;
}


std::size_t BinSearchTree::sizeHelper(const TreeNode *node) noexcept {
    if (node == nullptr)
        return 0;
    return 1 + sizeHelper(node->leftSubtree()) + sizeHelper(node->rightSubtree());
}

std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(this->root_);
}

unsigned BinSearchTree::heightHelper(const TreeNode *node) noexcept {
    if (node == nullptr)
        return 0;
    return 1 + std::max(heightHelper(node->leftSubtree()), heightHelper(node->rightSubtree()));
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(this->root_);
}

void BinSearchTree::inorderHelper(const TreeNode *node, std::vector<std::pair<std::string, int> > &out) {
    if (node == nullptr)
        return;
    inorderHelper(node->leftSubtree(), out);
    //ide suggested to use emplaceback instead of pushback
    out.emplace_back(node->value(), node->getCount());
    inorderHelper(node->rightSubtree(), out);
}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int> > &out) const {
    inorderHelper(this->root_, out);
}

