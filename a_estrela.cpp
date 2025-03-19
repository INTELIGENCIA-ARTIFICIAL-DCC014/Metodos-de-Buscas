#include "grafo.h"
#include <fstream>
#include <chrono>
#include <algorithm>
#include <limits>
#include <queue> // Para a fila de prioridade

using namespace std;

// Estrutura para representar um nó na busca A*
struct NoA {
    int cidade;
    int custoReal; // Custo real do caminho até o momento
    int estimativaTotal; // Custo real + heurística
    vector<int> rota;
    vector<bool> visitada;

    // Construtor
    NoA(int cidade, int custoReal, int estimativaTotal, vector<int> rota, vector<bool> visitada)
        : cidade(cidade), custoReal(custoReal), estimativaTotal(estimativaTotal), rota(rota), visitada(visitada) {}

    // Ordenação para a fila de prioridade (menor estimativaTotal primeiro)
    bool operator<(const NoA& outro) const {
        return estimativaTotal > outro.estimativaTotal; // Ordena em ordem crescente
    }
};

// Função heurística: estimativa do custo restante
int heuristica(int cidadeAtual, const vector<bool>& visitada, const vector<vector<int>>& dist) {
    int menorDistancia = numeric_limits<int>::max();
    for (int i = 0; i < visitada.size(); i++) {
        if (!visitada[i] && dist[cidadeAtual][i] < menorDistancia) {
            menorDistancia = dist[cidadeAtual][i];
        }
    }
    return menorDistancia;
}

pair<int, int> Grafo::a_estrela(string arq) {
    auto start = chrono::high_resolution_clock::now();

    priority_queue<NoA> fila;

    vector<int> rotaInicial = {0};
    vector<bool> visitadaInicial(num_vertices, false);
    visitadaInicial[0] = true;
    int estimativaInicial = heuristica(0, visitadaInicial, dist);
    fila.push(NoA(0, 0, estimativaInicial, rotaInicial, visitadaInicial));

    int solAchada = numeric_limits<int>::max();
    int nosVisitados = 0;
    int nosVisitadosFinal;

    while (!fila.empty()) {
        NoA atual = fila.top();
        fila.pop();
        nosVisitados++;

        if (atual.rota.size() == num_vertices) {
            int custoTotal = atual.custoReal + dist[atual.rota.back()][0];
            if (custoTotal < solAchada) {
                nosVisitadosFinal = nosVisitados;
                solAchada = custoTotal;
                ofstream fout("source/" + arq);
                fout << num_vertices << "\n";
                for (int i = 0; i < num_vertices - 1; i++)
                    fout << atual.rota[i] + 1 << " " << atual.rota[i + 1] + 1 << " " << dist[atual.rota[i]][atual.rota[i + 1]] << "\n";
                fout << atual.rota.back() + 1 << " " << atual.rota[0] + 1 << " " << dist[atual.rota.back()][atual.rota[0]] << "\n";
            }
            continue;
        }

        for (int i = 0; i < num_vertices; i++) {
            if (!atual.visitada[i]) {
                int novoCustoReal = atual.custoReal + dist[atual.cidade][i];
                vector<int> novaRota = atual.rota;
                novaRota.push_back(i);
                vector<bool> novaVisitada = atual.visitada;
                novaVisitada[i] = true;
                int novaEstimativaTotal = novoCustoReal + heuristica(i, novaVisitada, dist);
                fila.push(NoA(i, novoCustoReal, novaEstimativaTotal, novaRota, novaVisitada));
            }
        }
    }

    if (solAchada == numeric_limits<int>::max())
        cout << "Fracasso!\n";
    else 
        cout << "Sucesso!" << "\n";

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solAchada, nosVisitadosFinal};
}