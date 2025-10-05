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
#include <vector>