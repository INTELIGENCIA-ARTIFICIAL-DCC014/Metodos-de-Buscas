#include <chrono>
#include <fstream>

#include "grafo.h"

using namespace std;

pair<int, int> Grafo::backtracking(string arq) {
    // Marca o início do tempo
    auto start = chrono::high_resolution_clock::now();

    vector<int> rota(num_vertices, -1);
    vector<int> rotaAchada(num_vertices);
    rota[0] = 0;

    int nosVisitados = 0;
    int solAchada = -1;  // Quando a solução é encontrada, o valor é atualizado

    backtracking(rota, 1, 0, solAchada, rotaAchada, nosVisitados);

    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";

    for (int i = 0; i < num_vertices - 1; i++)
        fout << rotaAchada[i] + 1 << " " << rotaAchada[i + 1] + 1 << " "
             << dist[rotaAchada[i]][rotaAchada[i + 1]] << "\n";
    fout << rotaAchada.back() + 1 << " " << rotaAchada[0] + 1 << " "
         << dist[rotaAchada.back()][rotaAchada[0]] << "\n";

    // Marca o fim do tempo e calcula o tempo de execucao
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solAchada, nosVisitados};
}

// Função recursiva que implementa o algoritmo de backtracking para encontrar a
// solução
void Grafo::backtracking(vector<int>& rota, int pos, int valor, int& solAchada,
                         vector<int>& rotaAchada, int& nosVisitados) {
    nosVisitados++;

    // Verifica se encontrou um ciclo (impasse), ou seja, se o vértice já foi
    // visitado
    vector<bool> visitada(num_vertices, false);
    for (int i = 0; i < pos; i++) {
        if (visitada[rota[i]])
            return;  // Se já foi visitado, a busca é interrompida
        visitada[rota[i]] = true;
    }

    // Se chegou à solução viável (todos os vértices foram visitados), calcula o
    // valor da solução
    if (pos == num_vertices) {
        valor += dist[rota[pos - 1]][rota[0]];
        solAchada = valor;
        rotaAchada = rota;
        return;
    }

    // Tenta adicionar cada vértice na posição 'pos' da rota e chama
    // recursivamente para o próximo vértice
    for (int i = 0; i < num_vertices; i++) {
        // Se uma solução já foi encontrada, interrompe a busca
        if (solAchada != -1) return;

        bool visitada;
        int melhorVizinho = -1;
        int menorDistancia = numeric_limits<int>::max();

        // Para cada vértice i que ainda não foi visitado
        for (int i = 0; i < num_vertices; i++) {
            visitada = false;

            // Verifica se o vértice já foi visitado na rota parcial
            for (int j = 0; j < pos; j++) {
                if (i == rota[j]) {
                    visitada = true;
                    break;
                }
            }

            // Se o vértice já foi visitado, ignora ele e passa para o próximo
            if (visitada) continue;

            if (dist[rota[pos - 1]][i] < menorDistancia) {
                melhorVizinho = i;
                menorDistancia = dist[rota[pos - 1]][i];
            }
        }

        if (melhorVizinho == -1) {
            return;
        }

        rota[pos] = melhorVizinho;

        backtracking(rota, pos + 1, valor + dist[rota[pos - 1]][rota[pos]],
                     solAchada, rotaAchada, nosVisitados);

        rota[pos] = -1;
    }
}
