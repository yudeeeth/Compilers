Put together by Udith Kumar, [yudeeeth](https://github.com/yudeeeth)
# INTERPRETER

# Subtask 1

## Basic information
 - use the command 'make' to compile everything, and if it says up to date or something, do 'make clean' to clean up
 - only modify parser.y and lexel.l

### Forget about tree.hpp, just focus on implementing the following things
1. expr: a+b, a-b, a* b, a/b should be implemeted the syntax is the expression followed by ';'
```
(a*b)+c;
```
2. declaration: since we have no types (only integer), declaration is just variable followed by ';'
```
x;
```
3. assignment: assigning value to the variable, just do
```
x=5;
```

# Subtask 2
## basic info
 - only modify parser.y and lexel.l
### now implement IF, WHILE
1. IF: 
```
IF( ){ }ELSE{ }
```
2.WHILE:
```
WHILE( ){ }
```

# Subtask 3
## basic info
 - only modify parser.y,lexer.l and tree.hpp
### Fail subtask 2 and realise why  you failed. Then continue:


READ THE FOLLOWING ONLY AFTER IMPLEMENTING ALL OTHER FEATURES OTHER THAN IF AND WHILE,
Since we cannot interpret the program as we go(ex: if statements), we have to use two passes, once to contruct the syntax tree, and another to execute the sytax tree.
lets say we have to make a tree as follows:
![
(a + b) * c
                        expr1 --> first expr $1 -> expr2, $2 -> * , $3 -> c
                    /    |    \
                expr2    *     c --> second expr
             /    |    \
            a     +     b
](https://i.imgur.com/1ToFlIH.png)


we can construct this tree using the $$ feature of yacc as it parses the tokens.
i.e when match the first expression, we get 3 children as \$1,\$2,\$3, imagine instead of returning \$1 + \$2, you 
had a way to create a node with n children, then you can just do \l return the current expression to higher parts of the tree for construction, just like how when you call $1
a node with children a,+,b would be returned.
You would need to keep track of which type of statement the node is holding, in order to evaluate the node. you can do that in anyway you want.
One way to do it is hint1:

1. Think about how to implement the treenode so that it treats different statements diffrently. Hint 1 will give solve this task for you in case you want it

2. Implement the treenode and execute function.

# COMPILER
# Subtask 1
## basic info
 - install nasm using `sudo apt get install nasm`
Learn x86 nasm assembly.
Only the following operations and register info
Either watch [this](https://www.youtube.com/watch?v=wLXIWKUWpSs) first then read (optional)[this](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html).
Use [x86 reference](https://www.felixcloutier.com/x86/) as reference later.
### basic assembly program
 - write assembly code for fibonacci sequence

