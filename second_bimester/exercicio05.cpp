/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programaçãoo Paralela.
Autor.....: Ana Souza
Objetivo..: Lista de exercício
Bimestre..: 02/2025
Solucao...: Lista de Exercícios — Programação Paralela (OpenMP)
Arquivo...: exercicio05.cpp
--------------------------------------------------------------------------------------------------------------------------
Data Criação.................: 03/10/2025
Data Alteração...............: 03/10/2025
Alteração Feita..............: Arquivo inicial
Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados.
--------------------------------------------------------------------------------------------------------------------------
Versão 1.0
*/
#include <iostream> // std::cout
#include <omp.h> // API do OpenMP
#include <vector>
#include <iomanip> //para controlar a formatação de textos e números que você exibe na tela

const size_t TAMANHO = 1000000;


int main() {
    // preparando os dadso
    std::vector<double> a(TAMANHO);
    std::vector<double> x(TAMANHO, 1.5);
    std::vector<double> y(TAMANHO, 2.5);
    std::vector<double> z(TAMANHO, 3.5);

    // Vetor com as quantidades de threads que vamos testar
    std::vector<int> threads_para_testar = {2, 4, 8};
    
    std::cout << "Iniciando comparativo de escalonamento (static vs. dynamic)..." << std::endl;
    std::cout << "Tamanho dos vetores: " << TAMANHO << " elementos." << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "Threads" << std::left << 
    std::setw(25) << "Escalonamento" << std::left << std::setw(15) << "Tempo (s)" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    //b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
     for (int num_threads : threads_para_testar) {
        // Define o número de threads para as próximas regiões paralelas
        omp_set_num_threads(num_threads);
     
        // a) com schedule(static)
        double inicio_static = omp_get_wtime();

        #pragma omp parallel for schedule(static)
        for (size_t i = 0; i < TAMANHO; ++i) {
            a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }
        double fim_static = omp_get_wtime();
        double tempo_static = fim_static - inicio_static;
        
        std::cout << std::left << std::setw(10) << num_threads << std::left << std::setw(25) << "schedule(static)" << std::fixed << std::setprecision(6) << tempo_static << std::endl;

        // a) com schedule(dynamic, 1000)
        double inicio_dynamic = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, 1000)
        for (size_t i = 0; i < TAMANHO; ++i) {
            a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }
        double fim_dynamic = omp_get_wtime();
        double tempo_dynamic = fim_dynamic - inicio_dynamic;

        std::cout << std::left << std::setw(10) << num_threads << 
        std::left << std::setw(25) << "schedule(dynamic, 1000)"<< 
        std::fixed << std::setprecision(6) << tempo_dynamic << std::endl;
    }

    //c) Explique em quais situações static e dynamic são mais adequados.

    /*
    1. static--> o trabalho é divido em partes iguais antes de começar, 
    ideal para laços de repetição onde o custo de cada iteração é uniforme e previsível, 
    como em operações matemáticas simples sobre vetores, pois ele minimiza o custo de gerenciamento ao dividir o trabalho em blocos iguais antes do início da execução
    2. dynamic--> existe uma "fila de tarefas". Quem termina o seu trabalho primeiro, volta para a fila e pega a próxima tarefa disponível. 
    É mais adequado para situações com carga de trabalho irregular ou imprevisível, 
    como ao processar dados de tamanhos variados ou em algoritmos recursivos, pois ele permite que threads ociosas peguem novas porções de trabalho dinamicamente, 
    garantindo um melhor balanceamento de carga ao custo de um overhead um pouco maior.

    */

return 0;
}