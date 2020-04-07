We've already discussed Binary Trees, and more specifically Binary Search Trees.  As it turns out, you're already most of the way there to understanding Red-Black trees with that.   Any read-only operation over a Red-Black tree will in fact be identical to performing the same on a Binary Search Tree.

The differences come into play during insertion and deletion, any time we're modifying the contents of the tree.  With a plain BST, we perform a very simple check at each node as we traverse to locate the proper location.  While this does result in a properly sorted tree, depending on the order of the inputs entered we can end up with a highly askew tree.  If your root node is low, like `2`, there only only onw positive integer that could even even end up to the left of it.  Thus, all your nodes will cluster on the right, and in the very worst case wherein the inputs were already sorted, you've actually just built your

Any locate operation on a tree has a runtime of `O(l)`, where `l`.  With a red-black tree, we are able to ensure that your tree has `O(log(n))` levels, which in guarantees `O(log(n))` search times even if the values were all inserted in sorted order.

The drawback over a BST is that you're doing a lot more *stuff* every time you add or remove a node, because we always have to make sure the tree is balanced.  The way that balance is maintained is by associating an extra bit of information with each node - and luckily, this can quite literally be one single bit.  The most natural implementation in C++ will be somthing like `enum class NODE_COLOR { BLACK, RED }`, but there's no reason you could just toggle a boolean: `bool red` can be `true` for red nodes or `false` for black nodes, and while it is implementation dependent `sizeof(bool)` may in fact be `1` on your system.

To detect whether a rebalance is necessary, a set of properties much always hold:

1. Each node is *either* red or black (terminating `nullptr` "nodes" are always considered black).

2. The root of the whole tree is black.

3. A red node can only have a black parent and black children.

4. Every path from any given node to any of it's `nullptr` children will have the *same* number of black nodes - this is the "balanced" part, ensuring all paths are about the same length.

It's relatively simple in rule form, but does get a little bit complicated in practice.  When you insert a new node to a Red-Black tree, you run the risk of violating one of these principles.  Should that occur, it becomes necessary to actually change the structure of your tree such that the properties can hold again before passing control back to the caller.  To xdo this, you can either **recolor** any given node or **rotate** the tree.  Recoloring is simpler and gets tried first, and if it is still not possible to construct a valid tree, we use a combination rotation.

Rotating a tree means shifting the structure of a tree without shifting the origin.  One node will move up a level, and another will move down:

```
       B
     /   \
   A      C
 /   \
E     F

    becomes

   A
 /   \
E     B
    /   \
   F     C
```

I think I did that correctly, please correct me if I missed the mark.

With the new tree structure, you will be able to apply node coloring such that the four properties all hold, and your tree remains balanced.

Deletion is similarly complicated.  We first perform a regular old BST deletion, but then must inspect the siblings and the new node in its place to ensure the properties still hold.  If the new node that replaces a deleted black node is itself black, we call it "double black", and must rebalance the tree such that we can reduce it back to single black.

I also came across this [awesome visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html) that walks you through insertion and deletion operations.

Works cited:

“Red-Black Tree: Set 1 (Introduction).” GeeksforGeeks, 27 Nov. 2019, www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/.

“Red-Black Tree: Set 3 (Delete).” GeeksforGeeks, 27 Nov. 2019, https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/.
