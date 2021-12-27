#ifndef _TREE_NODE_HPP
#define _TREE_NODE_HPP

namespace ft {
    enum Color {
        RED,
        BLACK
    };

    template<typename T>
    struct TreeNode {
        T value;
        Color color;
        struct TreeNode *left;
        struct TreeNode *right;
        struct TreeNode *parent;
    };  // TreeNode

}  // namespace ft

#endif //_TREE_NODE_HPP
