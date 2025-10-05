/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programaçãoo Paralela.
Autor.....: Ana Souza
Objetivo..: Lista de exercício
Bimestre..: 02/2025
Solucao...: Lista de Exercícios — Programação Paralela (OpenMP)
Arquivo...: exercicio04.cpp
--------------------------------------------------------------------------------------------------------------------------
Data Criação.................: 03/10/2025
Data Alteração...............: 03/10/2025
Alteração Feita..............: Arquivo inicial
Exercício 4 — Medindo tempo por thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo.
--------------------------------------------------------------------------------------------------------------------------
Versão 1.0
*/
#include <iostream> // std::cout
#include <omp.h> // API do OpenMP
#include <vector>
#include <iomanip> //para controlar a formatação de textos e números que você exibe na tela

const size_t TAMANHO = 1000000;

int main(){
    //Preparação dos Dados
    std::vector<double> a(TAMANHO);
    std::vector<double> x(TAMANHO, 1.5);
    std::vector<double> y(TAMANHO, 2.5);
    std::vector<double> z(TAMANHO, 3.5);

    // Variáveis para armazenar nossos resultados de medição
    int num_threads_utilizadas = 0;
    std::vector<double> tempos_por_thread;

    //a) Medir e exibir o tempo total de execução.
    double inicio_total = omp_get_wtime();

    // Inicia a região paralela.
    #pragma omp parallel
    {
        //pega o ID  desta thread específica.
        int id_thread = omp_get_thread_num();

        //Apenas a primeira thread que chegar aqui  executará este bloco.
        #pragma omp single
        {
            // c) Mostrar quantas threads foram utilizadas no cálculo.
            num_threads_utilizadas = omp_get_num_threads();
            std::cout << "Calculando com uma equipe de " << num_threads_utilizadas << " threads." << std::endl;
            // Prepara o vetor de tempos para ter o tamanho exato do número de threads.
            tempos_por_thread.resize(num_threads_utilizadas);

        }
        //b) Medir e exibir o tempo gasto por cada thread.
        double inicio_thread = omp_get_wtime();
        // schedule(static) divide o trabalho em blocos iguais
        #pragma omp for schedule(static)
        for (size_t i = 0; i < TAMANHO; ++i) {
            a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }

        double fim_thread = omp_get_wtime();

        // Cada thread calcula sua própria duração e a armazena na sua posição correspondente do vetor tempos_por_thread
        tempos_por_thread[id_thread] = fim_thread - inicio_thread;

    } // Fim da região paralela.

    double fim_total = omp_get_wtime();
    double tempo_total = fim_total - inicio_total;

    std::cout << "\n--- Resultados Detalhados ---" << std::endl;

    // a) Tempo total
    std::cout << "a) Tempo de execucao total: " << std::fixed << std::setprecision(6) << tempo_total << " segundos." << std::endl;

    // c) Número de threads (reiterando a informação)
    std::cout << "c) Total de threads utilizadas: " << num_threads_utilizadas << std::endl;

    // b) Tempo por thread
    std::cout << "b) Tempo gasto por cada thread:" << std::endl;
    for (int i = 0; i < num_threads_utilizadas; ++i) {
        // std::setw(2)-->Define a largura mínima do campo para o próximo item a ser impresso. usado para alinhar texto em colunas.
        // std::fixed--> formato decimal normal em vez de notação científica
        //std::setprecision(6)-->Define quantas casas decimais aparecerá na saída
        std::cout << "Thread " << std::setw(2) << i << ": " << std::fixed << std::setprecision(6) << tempos_por_thread[i] << " segundos." << std::endl;
    }


    return 0;
}