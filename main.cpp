#include <iostream>
#include <fstream> 
#include "grafo.h"

using namespace std;

int main() {
    int n, idx1, idx2, d;
    
    // Abrindo o arquivo de entrada
    ifstream arquivo("instancia.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    arquivo >> n; // Lendo o número de nós

    Grafo g(n);

    // Lendo as arestas do arquivo
    while (arquivo >> idx1 >> idx2 >> d) {
        // Adiciona a aresta ao grafo (ajustando os índices para zero-based)
        g.addAresta(idx1 - 1, idx2 - 1, d);
    }

    // Fechando o arquivo de entrada
    arquivo.close();

    cout << "Busca Irrevogavel\n";
    auto resultado = g.irrevogavel("solucao_irrevogavel.txt");
    cout << "Solucao irrevogavel: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "Busca Backtracking\n";
    resultado = g.backtracking("solucao_backtracking.txt");
    cout << "Solucao backtracking: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "Busca em Largura\n";
    resultado = g.bfs("solucao_bfs.txt");
    cout << "Solucao em  Largura: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "Busca em Profundidade\n";
    resultado = g.profundidade("solucao_profundidade.txt");
    cout << "Solucao em Profundidade: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";


    return 0;
}