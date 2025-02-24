#include "grafo.h"
#include <fstream>
#include <chrono>

using namespace std;


pair<int, int> Grafo::profundidade(string arq) {
    // Marca o início do tempo
    auto start = chrono::high_resolution_clock::now();

    vector<int> rota(num_vertices, -1);  // Rota com os vértices visitados, inicialmente com todos os valores -1 (não visitado)
    vector<int> rotaOtima(num_vertices); 
    
    rota[0] = 0;

    int solOtima = INF;
    int nosVisitados = 0;
    
    profundidade(rota, 1, 0, solOtima, rotaOtima, nosVisitados);

    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";

    // Escrita da rota ótima no arquivo de saída
    for(int i = 0; i < num_vertices - 1; i++)
        fout << rotaOtima[i] + 1 << " " << rotaOtima[i + 1] + 1 << " " << dist[rotaOtima[i]][rotaOtima[i + 1]] << "\n";
    fout << rotaOtima.back() + 1 << " " << rotaOtima[0] + 1 << " " << dist[rotaOtima.back()][rotaOtima[0]] << "\n";

    // Marca o fim do tempo e calcula o tempo de execucao
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solOtima, nosVisitados};
}

// Função recursiva que implementa a busca em profundidade.
void Grafo::profundidade(vector<int>& rota, int pos, int valor, int &solOtima, vector<int>& rotaOtima, int& nosVisitados) {
    nosVisitados++;

    // Poda: Se a solução parcial já for pior que a melhor solução até agora, a busca é interrompida
    if(valor > solOtima)
        return;

    // Caso a solução for completada (pos == num_vertices), ou seja, todos os vértices foram visitados
    if(pos == num_vertices) {
        valor += dist[rota[pos - 1]][rota[0]];

        // Se a solução encontrada for melhor que a melhor solução até o momento, atualiza as variáveis
        if(valor < solOtima) {
            solOtima = valor;
            rotaOtima = rota;  
        }

        return;
    }

    bool visitada;
    
    // Para cada vértice i que ainda não foi visitado
    for(int i = 0; i < num_vertices; i++) {
        visitada = false;

        // Verifica se o vértice já foi visitado na rota parcial
        for(int j = 0; j < pos; j++) 
            if(i == rota[j]) {
                visitada = true;
                break;
            }

        // Se o vértice já foi visitado, ignora ele e passa para o próximo
        if(visitada) continue;

        // Adiciona o vértice i à posição atual da rota.
        rota[pos] = i;

        profundidade(rota, pos + 1, valor + dist[rota[pos - 1]][rota[pos]], solOtima, rotaOtima, nosVisitados);

        rota[pos] = -1;
    }
}
