/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programaçãoo Paralela.
Autor.....: Ana Souza
Objetivo..: Lista de exercício
Bimestre..: 02/2025
Solucao...: Lista de Exercícios — Programação Paralela (OpenMP)
Arquivo...: exercicio03.cpp
--------------------------------------------------------------------------------------------------------------------------
Data Criação.................: 03/10/2025
Data Alteração...............: 03/10/2025
Alteração Feita..............: Arquivo inicial
Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão.
--------------------------------------------------------------------------------------------------------------------------
Versão 1.0
*/

#include <iostream> // std::cout
#include <omp.h> // API do OpenMP
#include <vector>  //maneira segura de criar listas ou arrays de tamanho dinâmico, sem nos preocuparmos com o gerenciamento manual da memória.
#include <cmath>

const size_t TAMANHO = 1000000;

int main(){
    //declara os vetores e aloca espaço para 1 milhão de números do tipo double para cada vetor.
     std::vector<double> a(TAMANHO);
     std::vector<double> x(TAMANHO);
     std::vector<double> y(TAMANHO);
     std::vector<double> z(TAMANHO);

    // Inicializa os vetores de entrada com valores de exemplo
    for (size_t i = 0; i < TAMANHO; ++i) {
        x[i] = static_cast<double>(i) * 0.1;
        y[i] = static_cast<double>(i) * 0.2;
        z[i] = static_cast<double>(i) * 0.3;
    }

    //a) Faça a versão sequencial.
    std::cout << "Iniciando a versao sequencial..." << std::endl;
    //cronômetro do OpenMP
    double inicio_seq = omp_get_wtime();
    for (size_t i = 0; i < TAMANHO; ++i) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }

    double fim_seq = omp_get_wtime();
    double tempo_seq = fim_seq - inicio_seq;

    //b) Paralelize com #pragma omp parallel for schedule(static). 
    std::cout << "Iniciando a versao paralela com schedule(static)..." << std::endl;
    // Resetando o vetor a
    a.assign(TAMANHO, 0.0);

    //cronômetro do OpenMP
    double inicio_par = omp_get_wtime();
    // #pragma omp parallel for divide as iteraçoes do loop entre as threads. schedule(static) Especifica que a divisão de threads 
    //deve ser feita em blocos iguais e distribuída estaticamente antes do loop começar. Um exemplo: 100 iterações e 4 threads, cada thread recebe 25 iterações.
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < TAMANHO; ++i) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
    // cronômetro do OpenMP
    double fim_par = omp_get_wtime();
    double tempo_par = fim_par - inicio_par;

    //c) Mostre o tempo total de execução em cada versão.
    std::cout << "\n--- Resultados ---" << std::endl;
    std::cout.precision(6);
    std::cout << std::fixed;
    std::cout << "Tempo de execucao sequencial: " << tempo_seq << " segundos." << std::endl;
    std::cout << "Tempo de execucao paralela:   " << tempo_par << " segundos." << std::endl;

    if (tempo_par > 0) {
        double speedup = tempo_seq / tempo_par;
        std::cout << "Speedup : " << speedup << "x" << std::endl;
    }
    
    return 0;
}