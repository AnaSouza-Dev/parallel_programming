/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programaçãoo Paralela.
Autor.....: Ana Souza
Objetivo..: Lista de exercício
Bimestre..: 02/2025
Solucao...: Lista de Exercícios — Programação Paralela (OpenMP)
Arquivo...: exercicio02.cpp
--------------------------------------------------------------------------------------------------------------------------
Data Criação.................: 03/10/2025
Data Alteração...............: 03/10/2025
Alteração Feita..............: Arquivo inicial
Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária.
--------------------------------------------------------------------------------------------------------------------------
Versão 1.0
*/
#include <iostream> // std::cout
#include <omp.h> // API do OpenMP
using namespace std;

int main() {
    //a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
    int v[100];
    int i;
    
    for( i = 0; i < 100; i++) {
        v[i] = 1; // inicializa todos com 1
    }
    //b) Escreva um loop sequencial que soma todos os elementos.
    int soma_sequencial =0;
    for (i = 0; i < 100; i++){
        soma_sequencial += v[i]; // pega o valor atual da soma_sequencial e soma ao valor que está na posição i do vetor v e atribui esse novo valor à variável soma_sequencial
    }
    cout << "Soma sequencial = " << soma_sequencial << endl;

    //c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
    int soma_paralela = 0;
    #pragma omp parallel for reduction(+:soma_paralela)
    for (i = 0; i < 100; i++) {
        soma_paralela += v[i];
    }

    cout << "Soma paralela = " << soma_paralela << endl;

    //d) Compare os resultados e explique por que a diretiva reduction é necessária.

    // a diretiva reduction instrui o omp a criar cópias locais da variável e atribuir a cada thread,
    // cada thread executa sua parte no loop e guarda o resultado em sua cópia local sem interferir nas outras. Ao final do loop o omp reduz todas as cópias com operador + e armazena o resultado na variável global.
    //Sem a cláusula reduction, cada thread executaria partes diferentes do for, acessando a mesma variável soma_paralela simultaneamente.
    //Isso causaria uma condição de corrida (race condition), onde várias threads tentam atualizar soma ao mesmo tempo, gerando resultados incorretos.
    //Desse modo, usar a diretiva reduction garante a atomicidade do resultado
    int soma_paralela_sem_reduction = 0;
    #pragma omp parallel for
    for(i = 0; i<100 ; i++){
        soma_paralela_sem_reduction += v[i];
    }
    cout << "Soma paralela sem reduction = " << soma_paralela_sem_reduction << endl;
    
    return 0;

}