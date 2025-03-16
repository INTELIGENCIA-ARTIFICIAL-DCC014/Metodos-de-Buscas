#include "grafo.h"
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

pair<int, int> Grafo::ida(string arq) {
    auto start = chrono::high_resolution_clock::now();

    vector<int> rota(num_vertices, -1);
    vector<int> rotaAchada(num_vertices);
    rota[0] = 0;

    int solAchada = -1;
    int nosVisitados = 0;

    ida(rota, 1, 0, solAchada, rotaAchada, nosVisitados);
    
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";

    for (int i = 0; i < num_vertices - 1; i++)
        fout << rotaAchada[i] + 1 << " " << rotaAchada[i + 1] + 1 << " " << dist[rotaAchada[i]][rotaAchada[i + 1]] << "\n";
    fout << rotaAchada.back() + 1 << " " << rotaAchada[0] + 1 << " " << dist[rotaAchada.back()][rotaAchada[0]] << "\n";

    if (solAchada == INF)
        cout << "Fracasso!\n";
    else 
        cout << "Sucesso!\n";

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;
    
    return {solAchada, nosVisitados};
}

void Grafo::ida(vector<int>& rota, int pos, int valor, int& solAchada, vector<int>& rotaAchada, int& nosVisitados) {
    nosVisitados++;
    
    vector<bool> visitada(num_vertices, false);
    for (int i = 0; i < pos; i++) {
        if (visitada[rota[i]]) {
            solAchada = INF;
            return;
        }
        visitada[rota[i]] = true;
    }
    
    if (pos == num_vertices) {
        valor += dist[rota[pos-1]][rota[0]];
        solAchada = valor;
        rotaAchada = rota;
        return;
    }
    
    vector<pair<int, int>> candidatos;
    for (int i = 0; i < num_vertices; i++) {
        bool adicionada = false;
        for (int j = 0; j < pos; j++) {
            if (i == rota[j]) {
                adicionada = true;
                break;
            }
        }
        if (!adicionada) {
            candidatos.emplace_back(dist[rota[pos - 1]][i], i);
        }
    }
    
    sort(candidatos.begin(), candidatos.end());
    
    for (const auto& par : candidatos) {
        int custo = par.first;
        int cidade = par.second;
    
        rota[pos] = cidade;
        ordenada(rota, pos + 1, valor + custo, solAchada, rotaAchada, nosVisitados);
        rota[pos] = -1;
    }
}
