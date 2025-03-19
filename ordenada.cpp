#include "grafo.h"
#include <fstream>
#include <chrono>
#include <limits>

using namespace std;

pair<int, int> Grafo::ordenada(string arq) {
    auto start = chrono::high_resolution_clock::now();

    // Criar a rota percorrendo os vértices sequencialmente
    vector<int> rota(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        rota[i] = i;
    }

    int solAchada = 0;
    int nosVisitados = num_vertices;

    // Calcular o custo total do caminho percorrido
    for (int i = 0; i < num_vertices - 1; i++) {
        solAchada += dist[rota[i]][rota[i + 1]];
    }
    solAchada += dist[rota[num_vertices - 1]][rota[0]]; // Fechando o ciclo

    // Salvar a solução encontrada em um arquivo
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";
    for (int i = 0; i < num_vertices - 1; i++) {
        fout << rota[i] + 1 << " " << rota[i + 1] + 1 << " " << dist[rota[i]][rota[i + 1]] << "\n";
    }
    fout << rota.back() + 1 << " " << rota[0] + 1 << " " << dist[rota.back()][rota[0]] << "\n";

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solAchada, nosVisitados};
}
