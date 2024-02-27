#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
class grafo
{
private:
    int numvertices;
    vector<vector<int>> matrizadj;
    vector<vector<int>> matriz;
    vector<vector<int>> matrizincidencias;
    int numarestas;
    bool *marcador;

public:
    grafo(int vertices);
    ~grafo();
    void lerMatriz(string nomearquivo);
    void imprimirMatrizAdj();
    bool orientado();
    int getNumArestas();
    void adjParaIncidencia();
    void imprimirMatrizInc();
    void imprimirTabelaIncidencias();
    void buscaEmProfundidade(int inicial);
    void buscaEmLargura(int inicial);
    void prim();
    void dijkstra(int inicial);
    void ordenacaoTopologica();
    int dfs(int i,int j,vector<bool> &visitados,vector<int> &result);
    void saidaTxtAdj();
    void saidaTxtInc();
    void cicloEuleriano();
    int calculaGrauVertice(int v);


    bool temArestasNaoVisitadas(int u, vector<int>& visit);
};

#endif // GRAFO_H_INCLUDED
