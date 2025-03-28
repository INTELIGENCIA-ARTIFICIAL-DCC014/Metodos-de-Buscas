#include <vector>
#include <iostream>
#include <climits>

using namespace std;

#define Matriz vector<vector<int>>
#define INF INT_MAX/2

struct No {
    int idx;

    No() { }

    No(int indice) {
        idx = indice;
    }
};

struct Aresta {
    int idx1, idx2;
    int peso;

    Aresta() { }

    Aresta(int indice1, int indice2, int peso_aresta) {
        idx1 = indice1;
        idx2 = indice2;
        peso = peso_aresta;
    }
};

class Grafo {
    private:
        int num_vertices = 0;

        vector<No> nos;
        vector<Aresta> arestas;

        Matriz dist;

    public:
        Grafo(int n) {
            num_vertices = n;

            // Criação da lista de nós.
            nos = vector<No>(n, 0);
            for(int i = 0; i < n; i++)
                nos[i] = No(i);

            dist = Matriz(n, vector<int>(n));
        }

        void addAresta(int idx1, int idx2, int peso) {
            arestas.push_back(Aresta(idx1, idx2, peso));
            arestas.push_back(Aresta(idx2, idx1, peso));

            dist[idx1][idx2] = peso;
            dist[idx2][idx1] = peso;
        }

        int getPeso(int idx1, int idx2) {
            return dist[idx1][idx2];
        }

        void printMatrizDistancias() {
            cout << "  ";
            for(int i = 0; i < num_vertices; i++) 
                std::cout << i+1 << " ";
            cout << "\n";
            
            cout << " ";
            for(int i = 0; i < num_vertices; i++)
                cout << "--";
            cout << "\n";
            
            for(int i = 0; i < num_vertices; i++) {
                cout << i+1 << "|";
                for(int j = 0; j < num_vertices; j++) {
                    cout << dist[i][j] << " ";
                }
                cout << "\n";
            }
        }

        // Método da heurística de vizinho mais próximo (passar o nó atual e vetor de cidades visitadas como parâmetro)
        int vizinhoMaisProximo(int noAtual, vector<bool>& visitados) {
            int vizinhoMaisProximo = -1;
            int menorDistancia = INF;
            for (int i = 0; i < num_vertices; i++) {
                if (!visitados[i] && i != noAtual && dist[noAtual][i] < menorDistancia){
                    menorDistancia = dist[noAtual][i];
                    vizinhoMaisProximo = i;
                }
            }
            return vizinhoMaisProximo;
        }

        // Métodos de Busca

        pair<int, int> backtracking(string arq);
        void backtracking(vector<int>& rota, int pos, int valor, int& solAchada, vector<int>& rotaAchada, int& nosVisitados);

        pair<int, int> bfs(string arq);

        pair<int, int> profundidade(string arq);
        void profundidade(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados, int& nosVisitadosFinal);

        pair<int, int> ordenada(string arq);
        void ordenada(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados);

        pair<int, int> gulosa(string arq);
        void gulosa(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados);
        
        pair<int, int> a_estrela(string arq);
        void a_estrela(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados);

        pair<int, int> ida(string arq);
        void ida(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados, int limite, int &novoLimite, vector<bool>& visitada);
};