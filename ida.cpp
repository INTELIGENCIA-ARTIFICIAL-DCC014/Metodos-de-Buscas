#include "grafo.h"
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

pair<int, int> Grafo::ida(string arq) {
    auto start = chrono::high_resolution_clock::now();

    vector<int> rotaOtima;
    vector<bool> visitada(num_vertices, false);
    int solOtima = INF;
    int nosVisitados = 0;

    // Inicializa a rota com o nó inicial (0)
    vector<int> rota;
    rota.push_back(0);
    visitada[0] = true; // Marca o nó inicial como visitado

    // Define o limite inicial como a heurística do nó inicial
    int limite = vizinhoMaisProximo(0, visitada);

    while (limite < INF) {
        int novoLimite = INF;
        ida(rota, 0, 0, solOtima, rotaOtima, nosVisitados, limite, novoLimite, visitada);

        if (solOtima != INF) {
            break; // Solução ótima encontrada
        }

        limite = novoLimite; // Atualiza o limite para a próxima iteração
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    // Retorna o custo da solução ótima e o número de nós visitados
    return {solOtima, nosVisitados};
}

void Grafo::ida(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados, int limite, int &novoLimite, vector<bool>& visitada) {
    int noAtual = rota[pos];
    nosVisitados++;

    // Poda: Se o custo atual já é maior que a solução ótima, não explore mais
    if (valor >= solOtima) {
        return;
    }

    // Verifica se a rota atual é uma solução completa
    if (rota.size() == num_vertices) {
        // Adiciona o custo de voltar ao nó inicial
        int custoTotal = valor + dist[noAtual][0];
        if (custoTotal < solOtima) {
            solOtima = custoTotal;
            rotaOtima = rota;
        }
        return;
    }

    // Explora os vizinhos do nó atual
    for (int i = 0; i < num_vertices; i++) {
        if (!visitada[i]) { // Verifica se o nó já foi visitado
            visitada[i] = true; // Marca o nó como visitado
            int custoEstimado = valor + dist[noAtual][i] + vizinhoMaisProximo(i, visitada);

            // Verifica se o custo estimado está dentro do limite
            if (custoEstimado <= limite) {
                rota.push_back(i);
                ida(rota, pos + 1, valor + dist[noAtual][i], solOtima, rotaOtima, nosVisitados, limite, novoLimite, visitada);
                rota.pop_back();
            } else {
                // Atualiza o novo limite para a próxima iteração
                novoLimite = min(novoLimite, custoEstimado);
            }
            visitada[i] = false;
        }
    }
}