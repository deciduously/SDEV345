My personal favorite application of linked lists is actually as a core language component of a Lisp dialect.  The word Lisp derives from the phrase LISt Processer.  Writing Lisp code is essentially directly writing a string representation of an AST, and in it's p[urest form (found in languages like Scheme), linked lists are the only structure you have to work with.

To demonstrate, I'll walk through the evaluation of a very simple form: `(eval (cons (head '(+ -)) '(1 2)))`.  This Lisp function call is expected to evaluate 3.

To call a function in a Lisp, you use a construct called an "s-expression", which is a notation for a list surrounded by parenthesis.  These s-expressions are actually linked lists.  Each element is known as a "cons cell", which means an atomic element connected to *another* linked list.  To say connected to, you often see the symbol `:`, prnounced "cons".  An empty list counts:  `()`.  A list containing a single element is kind of like a element attached to an empty list:  `(1)` can be thought of as `1 : []`, or the `1` element "cons" an empty list.  Multiple elements are much the same: `(1 2)` is actually `1 : 2 : []`.

This should feel pretty familiar - it's like a linked list node:

```cpp
template <class T>
struct LLNode
{
    T val;
    LLNode *next;
}
```
