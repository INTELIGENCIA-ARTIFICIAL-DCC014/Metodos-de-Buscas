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

    // Fechando o arquivo 
    arquivo.close();

    cout << "BUSCA BACKTRACKING\n";
    auto resultado = g.backtracking("solucao_backtracking.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA EM LARGURA\n";
    resultado = g.bfs("solucao_bfs.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA EM PROFUNDIDADE\n";
    resultado = g.profundidade("solucao_profundidade.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA ORDENADA\n";
    resultado = g.ordenada("solucao_ordenada.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA GULOSA\n";
    resultado = g.gulosa("solucao_gulosa.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA A*\n";
    resultado = g.a_estrela("solucao_a_estrela.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";

    cout << "BUSCA IDA*\n";
    resultado = g.ida("solucao_ida.txt");
    cout << "Custo: " << resultado.first << "\n";
    cout << "Nos visitados: " << resultado.second << "\n\n";
    
    return 0;
}