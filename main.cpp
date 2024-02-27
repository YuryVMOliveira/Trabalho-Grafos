#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <vector>
using namespace std;

int main()
{
    int vertices;

    string nome="arquivo.txt";
    fstream arquivo;
    arquivo.open(nome);
    arquivo>>vertices;
    arquivo.close();
    grafo grafo(vertices);
    cout<<"Numero de vertices: "<<vertices<<endl;



    grafo.lerMatriz(nome);
    cout <<"Orientacao do grafo: "<< grafo.orientado()<<endl;
    cout << "numero de arestas: "<<grafo.getNumArestas()<<endl;
    grafo.imprimirMatrizAdj();
    grafo.imprimirMatrizInc();
    grafo.imprimirTabelaIncidencias();
    grafo.saidaTxtAdj();
    grafo.saidaTxtInc();
    grafo.buscaEmLargura(0);
    grafo.buscaEmProfundidade(0);
    grafo.prim();
    grafo.dijkstra(3);
    grafo.ordenacaoTopologica();
    grafo.cicloEuleriano();
    return 0;
}
