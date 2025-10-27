//
// Created by Anthony Villalobos on 10/23/25.
//

#include "HuffmanTree.hpp"

#include "PriorityQueue.hpp"

void HuffmanTree::destroy(TreeNode *n) noexcept {
    if (n == nullptr)
        return;
    destroy(n->leftSubtree());
    destroy(n->rightSubtree());
    delete n;
}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string, int> > &counts) {
    std::vector<TreeNode*> leaves;
    for (const auto & count : counts) {
        TreeNode* newnode = new TreeNode(count.first);
        newnode->setCount(count.second);
        leaves.push_back(newnode);
    }
    PriorityQueue pq(leaves);

    while (pq.size() > 1) {
        TreeNode* left = pq.extractMin();
        TreeNode* right = pq.extractMin();

        std::string smallest;
        if (left->value() < right->value())
            smallest = left->value();
        else
            smallest = right->value();

        TreeNode* parent = new TreeNode(smallest);
        parent->setCount(left->getCount() + right->getCount());
        parent->leftSubtree(left);
        parent->rightSubtree(right);
        pq.insert(parent);
    }
    HuffmanTree tree;
    tree.root_ = pq.extractMin();
    return tree;

}

void HuffmanTree::assignCodesDFS(const TreeNode *n, std::string &prefix, std::vector<std::pair<std::string, std::string> > &out) {
    if (n == nullptr)
        return;

    if (n->leftSubtree() == nullptr && n->rightSubtree() == nullptr) {
        if (prefix == "")
            out.push_back(std::make_pair(n->value(), "0"));
        else
            out.push_back(std::make_pair(n->value(), prefix));
    }

    prefix.push_back('0');
    assignCodesDFS(n->leftSubtree(), prefix, out);
    prefix.pop_back();

    prefix.push_back('1');
    assignCodesDFS(n->rightSubtree(), prefix, out);
    prefix.pop_back();
}

void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string> > &out) const {
    std::string prefix = "";
    assignCodesDFS(root_, prefix, out);
}

void HuffmanTree::writeHeaderPreorder(const TreeNode *n, std::ostream &os, std::string &prefix) {
    if (n == nullptr)
        return;

    if (n->leftSubtree() == nullptr && n->rightSubtree() == nullptr) {
        if (prefix == "")
            os << n->value() << " 0\n";
        else
            os << n->value() << " " << prefix << "\n";
    }

    prefix.push_back('0');
    writeHeaderPreorder(n->leftSubtree(), os, prefix);
    prefix.pop_back();

    prefix.push_back('1');
    writeHeaderPreorder(n->rightSubtree(), os, prefix);
    prefix.pop_back();
}

error_type HuffmanTree::writeHeader(std::ostream &os) const {
    std::string prefix = "";
    writeHeaderPreorder(root_, os, prefix);
    return error_type::NO_ERROR;
}

error_type HuffmanTree::encode(const std::vector<std::string> &tokens, std::ostream &os_bits, int wrap_cols) const {
    std::vector<std::pair<std::string, std::string >> codeList;
    assignCodes(codeList);
    int col = 0;

    for (auto word : tokens) {
        std::string code = "";

        for (auto & j : codeList){
            if (j.first == word) {
                code = j.second;
                break;
            }
        }
        if (code == "")
            continue;

        for (char k : code) {
            os_bits << k;
            col++;
            if (col == wrap_cols) {
                os_bits << '\n';
                col = 0;

            }
        }
    }
    if (col > 0)
        os_bits << '\n';
    return error_type::NO_ERROR;
}

