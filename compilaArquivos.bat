@echo off
echo Compilando programa


gcc -Wall -c queue.c
ar rvs libQueue.a queue.o
gcc -Wall testafila.c -o testafila libQueue.a

echo Feito!
pause