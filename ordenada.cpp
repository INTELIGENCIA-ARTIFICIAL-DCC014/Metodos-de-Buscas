#include "grafo.h"
#include <queue>
#include <fstream>
#include <chrono>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

// Estrutura para representar um nó na fila de prioridade
struct Node {
    vector<int> rota; // Rota parcial
    int custo;        // Custo acumulado da rota

    // Sobrecarga do operador para ordenar os nós pelo custo (menor custo primeiro)
    bool operator>(const Node& other) const {
        return custo > other.custo;
    }
};

pair<int, int> Grafo::ordenada(string arq) {
    // Marca o início do tempo
    auto start = chrono::high_resolution_clock::now();

    int solOtima = INF;          // Custo da solução ótima
    vector<int> rotaOtima;       // Rota ótima
    int nosVisitados = 0;        // Contador de nós visitados

    // Fila de prioridade para realizar a busca ordenada (menor custo primeiro)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Inicia a busca com o vértice 0 e custo 0
    pq.push({vector<int>(1, 0), 0});

    // Enquanto a fila não estiver vazia, continua a busca
    while (!pq.empty()) {
        nosVisitados++;

        // Obtém o nó de menor custo da fila de prioridade
        Node atual = pq.top();
        pq.pop();

        // Desempacota a rota e o custo acumulado
        vector<int> rota = atual.rota;
        int custo = atual.custo;

        // Se a rota contém todos os vértices (o tamanho da rota é igual ao número de vértices),
        // verifica se é uma solução válida e compara o custo para encontrar a melhor solução
        if (rota.size() == num_vertices) {
            custo += dist[rota.back()][rota[0]]; // Adiciona o custo de retornar ao início

            // Se o custo encontrado for menor que o custo da melhor solução, atualiza a solução ótima
            if (custo < solOtima) {
                solOtima = custo;
                rotaOtima = rota;
            }
        } else {
            bool visitada;

            // Itera sobre todos os vértices para tentar adicioná-los à rota
            for (int i = 0; i < num_vertices; i++) {
                visitada = false;

                // Verifica se o vértice i já foi visitado na rota parcial
                for (int j = 0; j < rota.size(); j++) {
                    if (i == rota[j]) {
                        visitada = true;
                        break;
                    }
                }

                // Se o vértice i já foi visitado, não adiciona à rota
                if (visitada) continue;

                // Cria uma nova rota com o vértice i adicionado
                vector<int> novaRota = rota;
                novaRota.push_back(i);

                // Calcula o novo custo acumulado
                int novoCusto = custo + dist[rota.back()][i];

                // Adiciona a nova rota à fila de prioridade
                pq.push({novaRota, novoCusto});
            }
        }
    }

    // Escreve a solução ótima no arquivo de saída
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";

    for (int i = 0; i < num_vertices - 1; i++) {
        fout << rotaOtima[i] + 1 << " " << rotaOtima[i + 1] + 1 << " " << dist[rotaOtima[i]][rotaOtima[i + 1]] << "\n";
    }
    fout << rotaOtima.back() + 1 << " " << rotaOtima[0] + 1 << " " << dist[rotaOtima.back()][rotaOtima[0]] << "\n";

    // Marca o fim do tempo e calcula o tempo de execução
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solOtima, nosVisitados};
}