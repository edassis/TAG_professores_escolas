/**
 * @file bipartido.h
 * @author 17/0102289 - Eduardo F. Assis;
 * @author 17/0098168 - Alexandre S. C. Oliveira;
 * @version 0.1
 * @date 2019-06-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _BIPARTIDO_H_
#define _BIPARTIDO_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** 
 * @brief Estrutura de cada escola.
 */
struct Escolas {
    int id;
    int ocupadas;
    vector<int> habilidades;
    vector<struct Professores*> contratados;
};

/**
 * @brief  Estrutura de cada professor.
 */
struct Professores {
    int id;
    int habilidades;
    vector<Escolas*> preferencias;
};

/**
 * @brief Converte um número do tipo \a char para \a int.
 * 
 * @param number \a String contendo o valor a ser convertido.
 * @return int Retorna o valor convertido.
 */
int cvt_string(string number);

/**
 * @brief Procura um nó que pode estar no grafo com id @p no.
 * 
 * @param grafo Referência para estrutura #vector<No>.
 * @param no Número do nó a ser procurado.
 * @return int 
 */
int grafo_no_busca(vector<Professores> &grafo, int no);


/**
 * @brief Função responsável por abrir e carregar o grafo bipartido na memória.
 * 
 * @param file_name \a String contendo o nome do arquivo a ser aberto.
 * @param professores Vetor passado por \b referência onde se deseja armazenar os professores.
 * @param escolas Vetor passado por \b referência onde se deseja armazenar as escolas.
 * @return 1(int) - Caso tenha êxito na leitura.
 * @return 0(int) - Caso falhe na leitura.
 */
int ler_txt(string file_name, vector<Professores> &professores, vector<Escolas> &escolas);

/**
 * @brief Printa o grafo bipartido na tela.
 * 
 * @param professores Vetor contendo professores (conjunto).
 * @param escolas Vetor contendo escolas (conjunto).
 */
void printa_bipartido(vector<Professores> professores, vector<Escolas> escolas);

/**
 * @brief Função responsável por fazer a associação entre o professor e a escola.
 * 
 * @param grupoA Vetor contendo professores (conjunto).
 * @param grupoB Vetor contendo escolas (conjunto).
 * @return int - Valor contendo quantos professores (@p &grupoA) foram alocados
 * estavelmente.
 * @note Esse algoritmo dá preferência para a preferência do prefessor.
 */
int alg_assoc(vector<Professores> &grupoA, vector<Escolas> &grupoB);
#endif