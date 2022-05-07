#!/bin/zsh
make clean
make && clear
./main inp.md > out.md
echo done!
node simulator.js