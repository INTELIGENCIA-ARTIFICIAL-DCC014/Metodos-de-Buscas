#include "grafo.h"
#include <fstream>
#include <chrono>

using namespace std;

pair<int, int> Grafo::irrevogavel(string arq) {
    // Marca o início do tempo
    auto start = chrono::high_resolution_clock::now();

    vector<int> rota(num_vertices, -1);
    vector<int> rotaAchada(num_vertices);
    rota[0] = 0;

    int solAchada = -1;
    int nosVisitados = 0;

    irrevogavel(rota, 1, 0, solAchada, rotaAchada, nosVisitados);
    
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";


    for(int i = 0; i < num_vertices - 1; i++)
        fout << rotaAchada[i] + 1 << " " << rotaAchada[i + 1] + 1 << " " << dist[rotaAchada[i]][rotaAchada[i + 1]] << "\n";
    fout << rotaAchada.back() + 1 << " " << rotaAchada[0] + 1 << " " << dist[rotaAchada.back()][rotaAchada[0]] << "\n";

    // Verifica se foi encontrada uma solução válida ou se ocorreu um fracasso
    if(solAchada == INF)
        cout << "Fracasso!\n";
    else 
        cout << "Sucesso!\n";

    // Marca o fim do tempo e calcula o tempo de execucao
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;
    
    return {solAchada, nosVisitados};
}

// Função recursiva que busca a solução do problema do caixeiro viajante
void Grafo::irrevogavel(vector<int>& rota, int pos, int valor, int& solAchada, vector<int>& rotaAchada, int& nosVisitados) {
    nosVisitados++;

    // Verifica se encontrou ciclo (impasse), ou seja, se algum vértice foi visitado mais de uma vez
    vector<bool> visitada(num_vertices, false);
    for(int i = 0; i < pos; i++) {
        if(visitada[rota[i]]) {
            solAchada = INF;  // Se ciclo encontrado, marca a solução como inválida
            return;
        }
        visitada[rota[i]] = true;
    }

    // Se todos os vértices foram visitados, calcula o valor da solução e retorna.
    if(pos == num_vertices) {
        valor += dist[rota[pos-1]][rota[0]];  // Adiciona o custo de retorno à cidade de origem
        solAchada = valor;  
        rotaAchada = rota;  
        return; 
    }

    bool adicionada;
    for(int i = 0; i < num_vertices; i++) {
        // Se uma solução já foi encontrada, interrompe a busca
        if(solAchada != -1) 
            return;

        // Verifica se a cidade 'i' já foi adicionada à rota
        adicionada = false;
        for(int j = 0; j < pos; j++) 
            if(i == rota[j]) {
                adicionada = true;  
                break;
            }
        // Se a cidade já foi adicionada à rota, pula a iteração
        if(adicionada) continue;

        
        rota[pos] = i;
        irrevogavel(rota, pos + 1, valor + dist[rota[pos - 1]][rota[pos]], solAchada, rotaAchada, nosVisitados);
        
        rota[pos] = -1;
    }
}
