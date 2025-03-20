# 🌐 INTELIGÊNCIA ARTIFICIAL - DCC014 (UFJF)
Este repositório contém os trabalhos práticos da disciplina Inteligência Artificial, desenvolvidos como parte do curso de Ciência da Computação da Universidade Federal de Juiz de Fora.

## 👥 Desenvolvedores
  > Anna Julia de Almeida Lucas

  > Gustavo da Silva Monteiro

  > Kaio de Oliveira e Sousa

  > Vinicius Lattini Gonçalves

  > João Victor Manhães Senra


## 🚛 O Problema do Caixeiro Viajante  

O **Problema do Caixeiro Viajante (TSP - Traveling Salesman Problem)** é um dos desafios clássicos da **Otimização Combinatória** e da **Teoria dos Grafos**. Ele consiste em encontrar o menor caminho possível que um caixeiro deve percorrer para visitar **todas as cidades** de uma lista **exatamente uma vez** e retornar à cidade de origem.  

Este problema é **NP-difícil**, o que significa que **não existe um algoritmo eficiente conhecido** que resolva todas as instâncias do problema de forma ótima em tempo polinomial. Portanto, são aplicadas diversas estratégias baseadas em **busca e heurísticas** para encontrar soluções próximas do ótimo de maneira eficiente.  

## 🔍 Algoritmos Implementados  

Para resolver o Problema do Caixeiro Viajante, este repositório inclui diferentes técnicas de busca informada e não informada, cada uma com características distintas:  

### 📌 Buscas Não Informadas  
Esses algoritmos não utilizam informações sobre o estado final para tomar decisões:  
- **Busca Irrevogável** - Explora os estados sem voltar atrás.  
- **Busca Backtracking** - Explora os caminhos, retrocedendo ao encontrar becos sem saída.  
- **Busca em Largura (BFS)** - Explora todos os nós de um nível antes de ir para o próximo.  
- **Busca em Profundidade (DFS)** - Explora um caminho completamente antes de retornar e explorar outro.  

### 📌 Buscas Informadas  
Esses algoritmos utilizam heurísticas para guiar a busca em direção ao objetivo:  
- **Busca Ordenada** - Explora os estados com base em um critério de ordenação.  
- **Busca Gulosa** - Seleciona sempre o próximo estado mais promissor com base em uma heurística.  
- **Busca A\*** - Considera tanto o custo percorrido quanto a estimativa do custo restante.  
- **Busca IDA\*** - Variante do A*, reduzindo o uso de memória ao explorar apenas estados dentro de um limite adaptativo.  

Cada algoritmo está implementado em sua respectiva pasta.  

### 🔹 Requisitos  
- **g++** (versão 10 ou superior)
- **Arquivos de entrada**: Arquivo de instância do problema em formato `.txt`

## 🚀 Como Usar em Windows 
Para rodar os algoritmos localmente, siga as instruções abaixo:

1. **Compilar o código**:
   ```bash
   g++ main.cpp bfs.cpp profundidade.cpp irrevogavel.cpp backtracking.cpp ordenada.cpp ida.cpp -o metodos-de-busca.exe

2. **Executar o código**:
   ```bash
   .\metodos-de-busca.exe instancia.txt

## 🚀 Como Usar em Linux   
Para rodar os algoritmos localmente, siga as instruções abaixo:

1. **Compilar e executar o código**:
   ```bash
   g++ main.cpp bfs.cpp profundidade.cpp irrevogavel.cpp backtracking.cpp ordenada.cpp ida.cpp -o metodos-de-busca.exe

2. **Executar o código**:
   ```bash
   .\metodos-de-busca.exe instancia.txt
