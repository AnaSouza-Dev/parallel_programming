/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programaçãoo Paralela.
Autor.....: Ana Souza
Objetivo..: Lista de exercício
Bimestre..: 02/2025
Solucao...: Lista de Exercícios — Programação Paralela (OpenMP)
Arquivo...: exercicio01.cpp
--------------------------------------------------------------------------------------------------------------------------
Data Criação.................: 03/10/2025
Data Alteração...............: 03/10/2025
Alteração Feita..............: Arquivo inicial
Exercício 1 — “Hello World” Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads.
--------------------------------------------------------------------------------------------------------------------------
Versão 1.0
*/
#include <iostream> // std::cout
#include <omp.h> // API do OpenMP



int main() {
    
    omp_set_num_threads(4); // <--> c) Configure o programa para rodar com 4 threads.

    //a) Crie uma região paralela com #pragma omp parallel.
     #pragma omp parallel //cria times de threads

     {
        //b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
        int thread_id = omp_get_thread_num();
        
        std::cout << "Hello, world from thread " << thread_id  << std::endl;
        
     }
    std::cout << "\nRegiao paralela finalizada." << std::endl;

    return 0;
}

