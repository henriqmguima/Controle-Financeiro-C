#ifndef HENRIQUE_H_INCLUDED
#define HENRIQUE_H_INCLUDED

void adicionarGasto(int num, float valores[], char descricoes[][100], int categorias[], int *totalGastos); // Registra as commpras e suas caracter�sticas

void listarGastos(int i, float valores[], char descricoes[][100], int categorias[], int quant); // lista as compras do usu�rio

float somarVetor(float vetor[], int tamanho); // Fun��o recursiva que soma todas as posi��es de um vetor pra saber o saldo futuro

float percorreDividas(float dividas[][4], int totaldividas, int num); // percorre as dividas, somando o que foi pago e guardando o total

float mediaDividas(float *valTotDiv, float somames); // calcula quanto % das d�vidas ainda falta ser pago

float reservaEmergencial(float reservaIdeal, int num, float reserva[]); // calcula se a reserva emergencial j� est� na margem ideal

void planejamentoGasto(float renda, float essencial[], float desejoPessoal[], float reserva[]); // Otimizar a renda informada dentro da t�cnica 50 30 20

void chamaLista(int num, float valores[], char descricoes[][100], int categorias[], int *totalGastos, int cont); // chama a funcao de listar gastos dependendo da aba do menu

void excluirCompra(float valores[], char descricao[][100], int categorias[], int *totalGastos, int posicao, int *valorT, int *cont1, int *cont2, float essencial [], float desejoPessoal[]); // Excluir vetores e strings

void compraParcelada(int num, float dividas[][4], int *totaldividas, float *valTotDiv); // financiamentos imobili�rios e automotivos

float jurosComposto(int num, float divida[][4], int *totaldividas, float *valTotDiv); // calculo de juros composto

void registraFunc(float *totalAr, float valores[], float *totalGeral, int *cont, int totalGastos, float area[0]); // registra um gasto em uma �rea

void registraDiv(float dividas [][4], float reserva[], int totaldividas, int num); // registra um divida reduzindo a partir da reserva

void listadividas(float dividas[][4], int totaldividas); // chama todas as ocorrencias de dividas

float cdi(float reserva[], int num); // Calcula 100% do CDI

void limpa ();

int verify (int confere, int totaldividas); // verifica se houve alguma ocorr�ncia

void verificaNegativo(int num, float essencial[], float desejoPessoal[], float reserva[], float divida[][4], int *totaldividas, float *totalDiv); //verifica se a pessoa est� negativa

int planoMeses(float renda, float reserva[], int num, float reservaIdeal, int totaldividas, float dividas[][4]); // Verifica em quantos meses os planos do sistema ir�o funcionar

float *alocarVetor(int tamanho); // Aloca um vetor dinamicamente

void liberarVetor(float *vetor); // Libera a mem�ria alocada para um vetor

void gerarExtrato(int total, float valores[], char descricoes[][100], int categorias[], char *nomeArquivo);// gera extrato das compras realizadas

void extratoDividas(float dividas[][4], int totaldividas); // gera extrato das d�vidas do usu�rio em um arquivo txt
#endif
