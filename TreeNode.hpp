//
// Created by Anthony Villalobos on 10/14/25.
//

#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <string>

class TreeNode {
public:

    TreeNode( const std::string& w ): left(nullptr), right(nullptr), word(w), count(1) {}
    ~TreeNode() {
        leftSubtree(nullptr);
        rightSubtree(nullptr);
    }

    TreeNode *leftSubtree() { return left; }
    TreeNode *rightSubtree() { return right; }

    const TreeNode *leftSubtree() const { return left; }
    const TreeNode *rightSubtree() const { return right; }
    int getCount() const {return count; }
    void setCount(int c){count = c;}

    void leftSubtree( TreeNode *newLeft ) { left = newLeft; }
    void rightSubtree(TreeNode *newRight) { right = newRight; }
    void incrementCount() {count++; }

    std::string& value() { return word; }
    const std::string& value() const{ return word; }

private:
    TreeNode *left, *right;
    std::string word;
    int count;
};

#endif //TREENODE_HPP
