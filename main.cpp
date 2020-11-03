/**
 * @file main.cpp
 * @author 17/0102289 - Eduardo F. Assis;
 * @author 17/0098168 - Alexandre S. C. Oliveira;
 * @version 0.1
 * @date 2019-06-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <utility>
#include <vector>
#include "bipartido.h"

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main () {
    vector<Professores> grupoA;
    vector<Escolas> grupoB;
    
    string bipartido_name = "bipartido.txt", curso;

    system(CLEAR);
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << '\n';
    cout << "> Digite o <nome do arquivo>.txt (e.g., bipartido.txt):" << '\n';
    cout << ">> ";
    cin >> bipartido_name;

    int leu = ler_txt(bipartido_name, grupoA, grupoB);
    int tamanho = 0;
    if (leu) {
        system(CLEAR);
        tamanho = alg_assoc(grupoA, grupoB);
        printa_bipartido(grupoA, grupoB);

        cout << "========================================================" << '\n';
        cout << "> Tamanho do emparelhamento estável: " << tamanho << "\n";
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << '\n';
        cout << "> Pressione ENTER para sair!";
        getchar(); 
        getchar(); 
    }
    else {
        cout << "========================================================" << '\n';
        cout << "> Não foi possível ler o arquivo (" << bipartido_name << ')' << '\n';
    }

    return 0;
} // end main();
