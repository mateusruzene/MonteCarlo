#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND ((double)rand() / RAND_MAX) // drand48()
#define SRAND(a) srand(a)                 // srand48(a)

// gcc -o main labMonteCarlo.c utils.c

double polinomio(double x)
{
  return x * (5 + x * (-16 + (x * x)));
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int dim)
{
  double resultado;
  double soma = 0.0;
  double x, y;

  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);

  double t_inicial = timestamp();

  for (int i = 0; i < namostras; i++)
  {
    for (int j = 0; j < dim; j++)
    {
      x = a + ((double)random() / RAND_MAX) * (b - a);
      soma += polinomio(x);
    }
  }

  resultado = ((soma / 2) / namostras) * (b - a);

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

  return resultado;
}

double retangulos_xy(double a, double b, int npontos)
{

  double h = (b - a) / npontos;
  double resultado;
  double soma = 0;

  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);

  double t_inicial = timestamp();

  for (int i = 0; i < npontos; i++)
  {
    soma += polinomio(a + h * i) * h;
  }

  resultado = soma;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

  return resultado;
}

int main(int argc, char **argv)
{

  if (argc < 5)
  {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  // INICIAR VALOR DA SEMENTE
  srand(20241);
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  double resultadoMonteCarlo = styblinskiTang(atof(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
  printf("Resultado do Metodo de Monte Carlo: %f \n", resultadoMonteCarlo);
  printf("\n ======================== \n", resultadoMonteCarlo);

  double resultadoRetangulos = retangulos_xy(atof(argv[1]), atof(argv[2]), atoi(argv[3]));
  printf("Resultado do Metodo dos Retangulos: %f \n", resultadoRetangulos);

  return 0;
}
