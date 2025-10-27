//
// Created by Anthony Villalobos on 10/15/25.
//
#include "PriorityQueue.hpp"


PriorityQueue::PriorityQueue(std::vector<TreeNode *> nodes) {
    for (auto & node : nodes) {
        insert(node);
    }
}


std::size_t PriorityQueue::size() const noexcept {
    return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

TreeNode *PriorityQueue::findMin() const noexcept {
    if (empty())
        return nullptr;
    return items_.back();
}

TreeNode *PriorityQueue::extractMin() noexcept {
    if (empty())
        return nullptr;
    TreeNode* node = items_.back();
    items_.pop_back();
    return node;
}

void PriorityQueue::deleteMin() noexcept {
    if (!empty())
        items_.pop_back();
}

bool PriorityQueue::higherPriority(const TreeNode *a, const TreeNode *b) noexcept {
    if (a->getCount() > b->getCount())
        return true;
    if (a->getCount() < b->getCount())
        return false;
    return a->value() < b->value();
}

void PriorityQueue::insert(TreeNode *node) {
    size_t idx = 0;
    while (idx < items_.size() && higherPriority(items_.at(idx), node))
        idx++;
    items_.insert(items_.begin() + idx, node);
}

bool PriorityQueue::isSorted() const {
    for (size_t i = 1; i < items_.size(); i++) {
        if (!higherPriority(items_.at(i - 1), items_.at(i)))
            return false;
    }
    return true;
}

void PriorityQueue::print(std::ostream &os) const {
    for (size_t i = 0; i < size(); i++)
        os << items_.at(i)->value() << " " << items_.at(i)->getCount() << '\n';
}

