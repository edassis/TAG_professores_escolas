/**
 * @file bipartido.cpp
 * @author 17/0102289 - Eduardo F. Assis;
 * @author 17/0098168 - Alexandre S. C. Oliveira;
 * @brief Funções para manipulação do digrafo.
 * 
 * @version 0.1
 * @date 2019-06-01
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "bipartido.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

int cvt_string(string number) {
    char id[number.length() + 1];
    int k = 0;

    /* procurando número na string */
    for (int i = 0; number[i] != '\0'; i++) {
        if (number[i] >= '0' && number[i] <= '9') {
            id[k] = number[i];
            k++;
        }
    }
    id[k] = '\0';

    return stoi(id);
} // end cvt_string();

int grafo_no_busca(vector<Professores> &grafo, int no) {
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].id == no) {
            return i;
        }
    }

    return -1;
} // end grafo_no_busca();

void printa_bipartido(vector<Professores> professores, vector<Escolas> escolas){
    cout << "========================================================" << '\n';
    cout << "> Lista de Professores:\n";

    for(int i = 0 ; i < professores.size(); i++){
        cout << "-> Professor(" << professores[i].id << "): " << '\n';
        cout << "\t# Habilidade: " << professores[i].habilidades << '\n';
        cout << "\t# Escolas Preferidas: ";

        for(int j = 0; j < professores[i].preferencias.size(); j++){
            cout << professores[i].preferencias[j]->id;

            if(j != professores[i].preferencias.size()-1)
                cout << " - ";
        }
        cout << '\n';
    }
    
    cout << "========================================================" << '\n';
    cout << "> Lista de Escolas:\n";
    for(int i = 0 ; i < escolas.size(); i++){
        cout << "-> Escola(" << escolas[i].id << "): " << '\n';
        cout << "\t# Vagas: " << escolas[i].habilidades.size() << '\n';
        cout << "\t# Requisitos Habilidade: ";

        for(int j = 0; j < escolas[i].habilidades.size(); j++){
            cout << escolas[i].habilidades[j];

            if(j != escolas[i].habilidades.size()-1)
                cout << " - ";
        }
        cout << '\n';

        cout << "\t# Contratados: " << escolas[i].contratados.size() << '\n';

        if(escolas[i].contratados.size() > 0){
            cout << "\t# Professores: ";
            for(int j = 0; j < escolas[i].contratados.size(); j++){
                cout << escolas[i].contratados[j]->id;
                if(j != escolas[i].contratados.size()-1){
                    cout << " - ";
                }
            }
            cout << "\n";
            cout << "\t# Habilidades dos Professores: ";
            for(int j = 0; j < escolas[i].contratados.size(); j++){
                cout << escolas[i].contratados[j]->habilidades;
                if(j != escolas[i].contratados.size()-1){
                    cout << " - ";
                }
            }
            cout << "\n";
        }
    }
} // end printa_bipartido();

int ler_txt(string file_name, vector<Professores> &professores, vector<Escolas> &escolas) {
    fstream myfile;
    string line, in;

    myfile.open(file_name);
    
    if (!myfile.is_open()) {
        cout << "ERRO! Não foi possível encontrar o arquivo!" << '\n';
        return 0;
    }
    
    /* Primeiro, encontra os vertices do grafo bipartido */
    while (!myfile.eof()) {
        string no = "";
        getline(myfile, line); // Pega linha do arquivo.
        
        /* encontrando o vertice */
        if (line.find("//", 0) == -1 && line.find("(", 0) != -1) { // ignora comentarios e somente aceita linhas verdadeiras
            /* Pegando somente o que esta no primeiro conjunto de '()' */
            no = line.substr(1, line.find(')', 0)-1);

            // para professor
            if(no[0] == 'P'){
                /* encontrando id e habilidade */
                string teacher = no.substr(0, no.find(',', 0));
                string habilidade = no.substr(no.find(',', 0), no.size()-1);
                
                Professores novo;
                novo.id = cvt_string(teacher);
                novo.habilidades = cvt_string(habilidade);

                professores.push_back(novo);

            }
            // para escola
            else if(no[0] == 'E'){
                Escolas nova;
                nova.id = cvt_string(no);
                nova.ocupadas = 0;
                escolas.push_back(nova);
            }
        }    
    }

    myfile.seekg(0); // volta ao inicio do arquivo

    /* Encontrando arestas e preferencias */
    while (!myfile.eof()) {
        string no = "";
        
        getline(myfile, line); // Pega linha do arquivo.
    
        if (line.find("//", 0) == -1 && line.find("(", 0) != -1) { // ignora comentarios e somente aceita linhas verdadeiras
            no = line.substr(1, line.find(')', 0)-1);

            // arestas para professor
            if(no[0] == 'P'){
                // encontra o professor
                string teacher = no.substr(0, no.find(',', 0));
                // variavel auxiliar para encontrar separadamente escolas de preferencia
                string school = ""; 
                // todas as escolas de preferencia juntas
                string schools = line.substr(line.find(':', 0)+1); 
                // Pega somente a parte da string com conjunto de professores '(...)'
                schools = schools.substr(schools.find('(')+1, schools.find(')')-2);

                // variavel para armazenar posicao do professor no vetor
                int posicao = 0;
                
                // encontrando o professor no grafo
                for(int i = 0; i < professores.size(); i++){
                    if(professores[i].id == cvt_string(teacher)){
                        posicao = i;
                        break;
                    }
                }

                schools+=','; // para o algoritmo identificar a ultima escola
                for(int i = 0; i < schools.size(); i++){
                    // se ainda esta identificando a escola
                    if(schools[i] != ','){
                        school += schools[i];
                    }

                    // se terminou de identificar a escola
                    else{
                        // salva o id da escola
                        int id_escola = cvt_string(school);
                        school = ""; // reseta auxiliar

                        // adiciona nas preferencias do professor
                        for(int j = 0; j < escolas.size(); j++){
                            if(escolas[j].id == id_escola){
                                professores[posicao].preferencias.push_back(&escolas[j]);
                                break;
                            }
                        }
                    }
                }
            }

            // Preferencias das escolas
            else if(no[0] == 'E'){
                // encontra todo o conjunto de habilidades
                string habils = line.substr(line.find(':', 0)+1);
                // auxiliar para armazenar separadamente as habilidades
                string habil = "";

                // posicao da escola
                int posicao = 0;
                for(int i = 0; i < escolas.size(); i++){
                    if(escolas[i].id == cvt_string(no)){
                        posicao = i;
                        break;
                    }
                }

                // faz o algoritmo identificar a ultima habilidade
                habils+=':';
                for(int i = 0; i < habils.size(); i++){
                    // se ainda esta identificando habilidade
                    if(habils[i] != ':'){
                        // le somente o numero ( podemos tirar depois )
                        if( habils[i] != '(' && habils[i] != ')')
                            habil += habils[i];
                    }
                    // se terminou de identificar habilidade
                    else{
                        // converte para numero
                        int habilidade = cvt_string(habil);
                        habil = ""; // reseta

                        // aumenta vagas e salva a habilidade preferencial
                        escolas[posicao].habilidades.push_back(habilidade);
                    }
                }
            }            
        }    
    }
    if(myfile.is_open()) myfile.close();
    return 1;
} // end ler_txt();

int alg_assoc(vector<Professores> &grupoA, vector<Escolas> &grupoB) {
    int estabilidade = 0 ;

    // Professores livres
    vector<Professores> livres = grupoA;

    /* Iniciando todos Livres */
    for (int i = 0 ; i < grupoB.size(); i++) {
        grupoB[i].contratados.clear();
        grupoB[i].ocupadas = 0;
    }

    // =================== Filosofia ===============================
    // Só contrata provisoriamente, se ainda há vagas na escola
    // Caso, não ha vagas: verifica se há contratado provisório, se houver, retira e poe o permanente.
    // Caso, não há vagas e não há provisórios, volta para a fila sem preferir a mesma escola.
    // Caso, não há vagas e nao possui requisito, volta para a fila sem preferir a mesma escola.
    // ========================================================================

    while (!livres.empty()) {
        // 1 prof da lista
        Professores &elemento = livres[0];
        if (!elemento.preferencias.empty()) {
            Escolas *preferencia = livres[0].preferencias[0];
            // contrata provisorio se escola nao estiver cheia
            if(preferencia->contratados.size() < preferencia->habilidades.size()){
                preferencia->contratados.push_back(&grupoA[elemento.id - 1]);
            }
            // ( escola esta cheia )
            else{
                vector<int> habilidades = preferencia->habilidades;
                
                bool possui_requisito = false;
                for(int i = 0; i < habilidades.size() && !possui_requisito ; i++){
                    if(elemento.habilidades >= habilidades[i]){
                        possui_requisito = true;
                    }
                }
                // caso 1
                if(possui_requisito){
                    // Verifica se há contratos provisórios
                    // Se contratado_habilidade < habilidades_escola
                    int provisorio = -1;
                    for(int i = 0; i < preferencia->contratados.size(); i++){
                        bool nao_provisorio = false;
                        for(int j = 0; j < habilidades.size() && !nao_provisorio; j++){
                            if(preferencia->contratados[i]->habilidades >= habilidades[j]){
                                nao_provisorio = true;
                                habilidades.erase(habilidades.begin() + j);
                            }
                        }
                        if(!nao_provisorio){
                            provisorio = i;
                        }
                    }

                    if(provisorio != -1){   // se n for provisorio
                        // retira preferencia do provisorio
                        preferencia->contratados[provisorio]->preferencias.erase(preferencia->contratados[provisorio]->preferencias.begin());
                        // poe o provisorio na fila
                        livres.push_back(*preferencia->contratados[provisorio]);
                        // tira associação do provisorio
                        preferencia->contratados.erase(preferencia->contratados.begin() + provisorio);
                        // contrata o mais habilidoso ( melhor )
                        preferencia->contratados.push_back(&grupoA[elemento.id - 1]);
                    }
                    // caso 2
                    // Nao há provisórios
                    else{
                        // Poe novamente na fila
                        elemento.preferencias.erase(elemento.preferencias.begin()); // retira escola da preferencia
                        livres.push_back(elemento);
                    }
                }
                // caso 3
                // Nao possui requisito
                else{
                    // Poe novamente na fila
                    elemento.preferencias.erase(elemento.preferencias.begin()); // retira escola da preferencia
                    livres.push_back(elemento);
                }
            }
        }   
        // Retira atual da fila
        livres.erase(livres.begin());

    }
    for(int i = 0; i < grupoB.size(); i++){
        estabilidade += grupoB[i].contratados.size();
    }

    return estabilidade;
} // end alg_assoc();