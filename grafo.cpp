#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <list>
#define INF 1e9
using namespace std;
grafo::grafo(int vertices)
{
    numvertices=vertices;
    matriz.resize(numvertices, vector<int>(numvertices, 0));
    matrizadj.resize(numvertices, vector<int>(numvertices, 0));
    numarestas=0;
    marcador=new bool[numvertices];

}
grafo::~grafo()
{
}
int grafo::getNumArestas()
{
    return numarestas;
}
void grafo::lerMatriz(string nomearquivo)
{

    fstream arquivo;
    arquivo.open(nomearquivo);
    //preenche matriz
    if(arquivo.is_open())
    {
        arquivo>>numvertices;//le primeiro elemento

        for (int i = 0; i < numvertices; ++i) //preenche matriz do arquivo
        {
            for (int j = 0; j < numvertices; ++j)
            {
                arquivo >> matriz[i][j];

            }

        }
        arquivo.close();
        //preenche matriz adjascente, tanto para grafo orientado quanto nao orientado.
        if(!orientado())
        {
            for (int i = 0; i < numvertices; i++)
            {
                for (int j = 0; j < numvertices; j++)
                {
                    if(matriz[i][j]!=999&&matriz[i][j]!=0)
                    {
                        matrizadj[i][j]=matriz[i][j];
                        matrizadj[j][i]=matriz[i][j];
                        numarestas++;
                    }

                }

            }

            adjParaIncidencia();
        }
        else
        {
            for (int i = 0; i < numvertices; ++i)
            {
                for (int j = 0; j < numvertices; j++)
                {
                    if(matriz[i][j]!=999&&matriz[i][j]!=0)
                    {
                        matrizadj[i][j]=matriz[i][j];
                        numarestas++;

                    }
                }
            }
            adjParaIncidencia();
        }

    }

    else
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }

}
void grafo::saidaTxtAdj()
{
    ofstream arq;
    arq.open("matrizAdj.txt");
    for(int i=0; i<numvertices; i++)
    {
        for(int j=0; j<numvertices; j++)
        {
            if(j==numvertices-1)
            {
                arq<<matrizadj[i][j]<<"\n";
            }
            else
            {
                arq<<matrizadj[i][j]<<" ";
            }
        }

    }
    arq.close();
}
void grafo::saidaTxtInc()
{
    ofstream arq2;
    arq2.open("matrizInc.txt");
    for(int i=0; i<numvertices; i++)
    {
        for(int j=0; j<numarestas; j++)
        {
            if(j==numarestas-1)
            {
                arq2<<matrizincidencias[i][j]<<"\n";
            }
            else
            {
                arq2<<matrizincidencias[i][j]<<" ";
            }
        }

    }
    arq2.close();
}
void grafo::imprimirMatrizAdj()
{
    cout<<"Matriz de adjacencias: "<<endl;
    for (int i = 0; i < numvertices; ++i)
    {
        for (int j = 0; j < numvertices; ++j)
        {
            cout << matrizadj[i][j] << " ";
        }
        cout <<endl;
    }
}
void grafo::imprimirMatrizInc()
{
    cout<<"Matriz de incidencias: "<<endl;
    for (int i = 0; i <numvertices ; ++i)
    {
        for (int j = 0; j < numarestas; ++j)
        {
            cout << matrizincidencias[i][j] << " ";
        }
        cout <<endl;
    }
}
void grafo::imprimirTabelaIncidencias()
{
    cout<<"Tabela de incidencias: "<<endl;
    for (int i = 0; i <numvertices ; ++i)
    {
        for (int j = 0; j < numarestas; ++j)
        {
            if(matrizincidencias[i][j]!=0)
            {
                cout << matrizincidencias[i][j] << " ";
            }
        }
        cout <<endl;
    }
}

bool grafo::orientado()
{

    if(matriz[1][0]==0)
        return false;
    else
        return true;
}

void grafo::adjParaIncidencia()
{
    matrizincidencias.resize(numarestas, vector<int>(numarestas, 0));

    if(orientado())
    {
        int j=0;
        for (int a = 0; a < numvertices; ++a)
        {
            for (int b = 0; b < numvertices; ++b)
            {
                if(matrizadj[a][b]!=0)
                {
                    matrizincidencias[a][j]=matrizadj[a][b];
                    matrizincidencias[b][j]=-1*matrizadj[a][b];
                    j++;
                }
            }
        }
    }
    else
    {
        int j=0;
        for (int a = 0; a < numvertices; ++a)
        {
            for (int b = 0; b < numvertices; ++b)
            {
                if(matriz[a][b]!=0&&matriz[a][b]!=999)
                {
                    matrizincidencias[a][j]=matriz[a][b];
                    matrizincidencias[b][j]=matriz[a][b];
                    j++;
                }
            }
        }

    }


}
void grafo::buscaEmProfundidade(int inicial)
{
    cout<<endl<<"Busca em profundidade: "<<endl<<"Vertice inicial: "<<inicial<<endl;
    stack <int> pilha;
    vector<bool> visitado(numvertices,false);

    pilha.push(inicial);
    while(!pilha.empty())
    {
        int verticeatual=pilha.top();
        pilha.pop();
        if(!visitado[verticeatual])
        {
            visitado[verticeatual]=1;
            cout<<verticeatual<< "-> ";
        }
        for(int i=numvertices-1; i>=0; i--)
        {
            if(matrizadj[verticeatual][i]!=0&&!visitado[i])
            {
                pilha.push(i);
            }
        }
    }
    cout<<endl;
}
void grafo::buscaEmLargura(int inicial)
{
    cout<<endl<<"Busca em largura: "<<endl<<"Vertice inicial: "<<inicial<<endl;
    queue <int> fila;
    vector<bool> visitado(numvertices,false);

    visitado[inicial]=true;
    fila.push(inicial);

    while(!fila.empty())
    {
        int verticeatual=fila.front();
        cout<<verticeatual<<"-> ";
        fila.pop();
        for(int i=0; i<numvertices; i++)
        {
            if(matrizadj[verticeatual][i]!=0&&!visitado[i])
            {
                visitado[i]=true;
                fila.push(i);
            }
        }
    }
    cout<<endl;
}
void grafo::prim()
{
    cout<<endl<<"algoritmo de Prim: "<<endl;
    int pesototal=0;
    vector<bool> visitado(numvertices, false);
    vector<int> chave(numvertices, INF);
    vector<int> pai(numvertices, -1);
    priority_queue<pair<int,int>> pq;
    pq.push({0,0});
    chave[0]=0;// Inicializa a chave do primeiro vértice como 0

    while(!pq.empty())
    {
        int u= pq.top().second;
        pq.pop();
        visitado[u]=1;
        for(int i=0; i<numvertices; i++)
        {
            if(!visitado[i]&&matrizadj[u][i]<chave[i]&&matrizadj[u][i]!=0)
            {
                chave[i]=matrizadj[u][i];
                pq.push({-chave[i],i});
                pai[i]=u;
            }
        }
    }
//calcular peso da arv
    for(int j=0; j<chave.size(); j++)
    {
        pesototal=pesototal+chave[j];
    }
//imprimir arv
    cout<<"Arestas: ";
    for(int j=1; j<pai.size(); j++)
    {
        if(pai[j]<=0)
            cout<<"{0,"<<j<<"}";
        else if(j<pai[j])
            cout<<"{"<<j<<","<<pai[j]<<"}";
        else
            cout<<"{"<<pai[j]<<","<<j<<"}";
    }
    cout<<endl;
    cout<<"Peso da arvore geradora minima: "<<pesototal<<endl<<endl;
}
void grafo::dijkstra(int inicial)
{
    if(!orientado())
    {
        priority_queue<pair<int,int>> pq;
        vector<int> distancia(numvertices,INF);
        distancia[inicial]=0;
        vector<int> pai(numvertices,-1);
        pq.push({0,inicial});
        while(!pq.empty())
        {
            int v=pq.top().second;
            int custo=-pq.top().first;

            pq.pop();

            for(int i=0; i<numvertices; i++)
            {
                if(distancia[i] > distancia[v] + matrizadj[v][i]&&matrizadj[v][i]!=0)
                {
                    distancia[i]=distancia[v]+matrizadj[v][i];
                    pq.push({-distancia[i],i});
                    pai[i]=v;
                }
            }

        }
        cout<<"Dijkstra:"<<endl<<"Vertice inicial: "<<inicial<<endl;
        for(int i=0; i<numvertices; i++)
        {
            if(distancia[i]==INF)
                cout<<-1<<" ";
            else
            {
                cout<< "A distancia ate "<<i<<" eh "<<distancia[i]<<", Percurso: (";
                int j=i;
                while(j!=inicial && pai[j]!=-1)
                {
                    cout<<j<<"<-";
                    j=pai[j];
                }
                cout<<inicial<<") "<<endl;
            }
        }
    }
}
void grafo::ordenacaoTopologica()
{
    cout<<endl<<"ordenacao topologica"<<endl;
    int n=numvertices;
    vector<bool> v(numvertices,false);
    vector<int> result(numvertices,0);
    int i=n-1;

    for(int j=0; j<n; j++)
    {
        if(v[j]==false)
        {
            i=dfs(i, j,v,result);
        }
    }

    for(int x=0; x<numvertices; x++)
    {
        cout<<result[x]<<" ";
    }
    cout<<endl;

}
int grafo::dfs(int i,int j,vector<bool> &visitados,vector<int> &result)
{
    visitados[j]=true;

    for(int x=0; x<numvertices; x++)
    {
        if(matrizadj[j][x]!=0)
        {
            if(visitados[x]==false)
            {
                i=dfs(i,x,visitados,result);
            }
        }
    }
    result[i]=j;
    return i-1;
}

void grafo::cicloEuleriano()
{
    cout<<endl<<"Ciclo euleriano: "<<endl;

    vector<int> entrada(numvertices,0);
    for(int i=0; i<numvertices; i++)
    {
        entrada[i]=calculaGrauVertice(i);
    }




}
int grafo::calculaGrauVertice(int v)
{
    int grau=0;
    for(int j=0; j<numvertices; j++)
    {
        if(matrizadj[v][j]!=0)
        {
            grau++;
        }
    }

    return grau;
}

