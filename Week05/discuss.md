My personal favorite application of linked lists is actually as a core language component of a Lisp dialect.  The word Lisp derives from the phrase LISt Processer.  Writing Lisp code is essentially directly writing a string representation of an AST, and in it's p[urest form (found in languages like Scheme), linked lists are the only structure you have to work with.

To demonstrate, I'll walk through the evaluation of a very simple form: `(eval (cons (head '(+ -)) '(1 2)))`.  This Lisp function call is expected to evaluate 3.

To call a function in a Lisp, you use a construct called an "s-expression", which is a notation for a list surrounded by parenthesis.  These s-expressions are actually linked lists.  Each element is known as a "cons cell", which means an atomic element connected to *another* linked list.  To say connected to, you often see the symbol `:`, prnounced "cons".  An empty list counts:  `()`.  A list containing a single element is kind of like a element attached to an empty list:  `(1)` can be thought of as `1 : []`, or the `1` element "cons" an empty list.  Multiple elements are much the same: `(1 2)` is actually `1 : 2 : []`.

If it feels like a linked list node, that's because it is:

```cpp
template <class T>
struct LLNode
{
    T val;
    LLNode *next;
}
```

Each element is a linked list node "consed" to another linked list through a `next` pointer!  These lists, or s-expressions, can either represent data, as in a list of values, or code, like a function call: `(+ 1 2)`.  This is a list containing the addition function and the integers one and two, but Lisp interpreters know that when they encounter a linked list that begins with a function, it represents a function call.  This will cause the interpreter to step into to addition function and use all provided arguments as the operands.  This flexible sysntax scales to more arguments: `(+ 1 2 3)` will evaluate to `6`.  THe interpreter program will liekly have a line like this pseudo-C++:

```cpp
while(travPtr->next != nullptr)
{
    travPtr = travPtr->next;
    args.push_back(travPtr->val);
}
```

Once we reach `nullptr`, we know we've fully consumed the list and arrived at the final element.

Stepping back up to the top, `(eval (cons (head '(+ -)) '(1 2)))` will recursively evaluate sublists until it gets to one final function call.  We'll get intermediate steps:

```
(eval (cons + '(1 2)))
(eval (+ 1 2))
(+ 1 2)
3
```
