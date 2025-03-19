#include "grafo.h"
#include <fstream>
#include <chrono>
#include <algorithm>
#include <limits>

using namespace std;

pair<int, int> Grafo::gulosa(string arq) {
    auto start = chrono::high_resolution_clock::now();

    vector<int> rota(num_vertices, -1);
    vector<bool> visitada(num_vertices, false);
    rota[0] = 0;
    visitada[0] = true;

    int solAchada = 0;
    int nosVisitados = 1;

    for (int i = 1; i < num_vertices; i++) {
        int cidadeAtual = rota[i - 1];
        int melhorVizinho = -1;
        int menorDistancia = numeric_limits<int>::max();

        // Escolhe o vizinho mais próximo (estratégia gulosa)
        for (int j = 0; j < num_vertices; j++) {
            if (!visitada[j] && dist[cidadeAtual][j] < menorDistancia) {
                melhorVizinho = j;
                menorDistancia = dist[cidadeAtual][j];
            }
        }

        if (melhorVizinho == -1) {
            solAchada = numeric_limits<int>::max();
            break;
        }

        rota[i] = melhorVizinho;
        visitada[melhorVizinho] = true;
        solAchada += menorDistancia;
        nosVisitados++;
    }

    // Fechando o ciclo
    solAchada += dist[rota[num_vertices - 1]][rota[0]];
    
    // Escrevendo a rota no arquivo
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";
    for (int i = 0; i < num_vertices - 1; i++)
        fout << rota[i] + 1 << " " << rota[i + 1] + 1 << " " << dist[rota[i]][rota[i + 1]] << "\n";
    fout << rota.back() + 1 << " " << rota[0] + 1 << " " << dist[rota.back()][rota[0]] << "\n";

    if (solAchada == numeric_limits<int>::max())
        cout << "Fracasso!\n";
    else 
        cout << "Sucesso!\n";

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;
    
    return {solAchada, nosVisitados};
}
