#include "grafo.h"
#include <queue>
#include <fstream>
#include <chrono>

using namespace std;


pair<int, int> Grafo::bfs(string arq) {
    // Marca o início do tempo
    auto start = chrono::high_resolution_clock::now();

    int solOtima = numeric_limits<int>::max(); // Inicializa a solução ótima com o maior valor possível
    vector<int> rotaOtima;
    int nosVisitados = 0;
    int nosVisitadosFinal = 0;

    // Fila para realizar a busca em largura (BFS)
    queue<pair<vector<int>, int>> q;

    // Inicia a busca com o vértice 0 e custo 0
    q.push({vector<int>(1, 0), 0});

    // Enquanto a fila não estiver vazia, continua a busca
    while (!q.empty()) {
        nosVisitados++;

        // Obtém o primeiro elemento da fila (a rota parcial e seu valor) e remove da fila
        auto parRotaValor = q.front();
        q.pop();

        // Desempacota o par em rota e valor (o custo acumulado até agora)
        vector<int> rota = parRotaValor.first;
        int valor = parRotaValor.second;

        // Se a rota contém todos os vértices (o tamanho da rota é igual ao número de vértices),
        // verifica se é uma solução válida e compara o custo para encontrar a melhor solução
        if (rota.size() == num_vertices) {
            valor += dist[rota.back()][rota[0]]; // Adiciona o custo de retornar ao vértice inicial

            // Se o custo encontrado for menor que o custo da melhor solução, atualiza a solução ótima
            if (valor < solOtima) {
                solOtima = valor;
                rotaOtima = rota;
                nosVisitadosFinal = nosVisitados;
            }
        } else {
            // Itera sobre todos os vértices para tentar adicioná-los à rota, seguindo a ordem ordinária
            for (int i = 0; i < num_vertices; i++) {
                bool visitada = false;

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
                vector<int> filho = rota;
                filho.push_back(i);

                // Adiciona a nova rota à fila, com o valor atualizado (soma da distância entre o último vértice e o novo vértice)
                q.push({filho, valor + dist[rota.back()][i]});
            }
        }
    }

    // Escreve a solução encontrada no arquivo de saída
    ofstream fout("source/" + arq);
    fout << num_vertices << "\n";

    for (int i = 0; i < num_vertices - 1; i++)
        fout << rotaOtima[i] + 1 << " " << rotaOtima[i + 1] + 1 << " "
             << dist[rotaOtima[i]][rotaOtima[i + 1]] << "\n";
    fout << rotaOtima.back() + 1 << " " << rotaOtima[0] + 1 << " "
         << dist[rotaOtima.back()][rotaOtima[0]] << "\n";

    // Marca o fim do tempo e calcula o tempo de execução
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return {solOtima, nosVisitadosFinal};
}
