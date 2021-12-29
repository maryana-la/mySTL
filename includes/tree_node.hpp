/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:32 by                   #+#    #+#             */
/*   Updated: 2021/12/29 15:29:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_TREE_NODE_HPP_
#define INCLUDES_TREE_NODE_HPP_

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

#endif  // INCLUDES_TREE_NODE_HPP_
