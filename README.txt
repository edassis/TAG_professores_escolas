# System Information #
g++ (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Integrantes:
 *  17/0098168 - Alexandre Souza Costa Oliveira;
 *  17/0102289 - Eduardo Ferreira de Assis.

# Como compilar:
* Na raiz do diretório, onde se encontram os códigos fontes, abra o terminal e execute:
    ** Para gerar o binário:
        make build 

# Como executar:
* Para rodar o programa, no diretório raiz, abra o terminal e execute:
    ** Para executar:
        make exec

# Limpar:
* Vai remover o binário e os arquivos *.o
    make clear

# Observação:
* Caso o Makefile não funcione, execute:
    $ g++ -std=c++14 main.cpp bipartido.cpp -g
    $ ./a.out