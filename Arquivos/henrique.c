#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "henrique.h"  // Inclusão de um arquivo de cabeçalho personalizado


// Função para calcular o planejamento de gastos mensais
// Divide a renda em três categorias: essencial, desejo pessoal e reserva
void planejamentoGasto(float renda, float essencial[], float desejoPessoal[], float reserva[]) {
    int i;

    // Loop para preencher os arrays de essencial, desejo pessoal e reserva
    for (i = 0; i < 12; i++) {
        essencial[i] = renda / 2;
        desejoPessoal[i] = (renda * 30) / 100;
        reserva[i] = (renda * 20) / 100;
    }
}

// Função para adicionar um gasto ao registro
void adicionarGasto(int num, float valores[], char descricoes[][100], int categorias[], int *totalGastos) {
    // Verifica se o limite máximo de gastos foi atingido
    if (*totalGastos >= 100) {
        printf("Erro: Limite maximo de gastos atingido.\n");
        return;
    }

    printf("============================\n");
    // Solicita o valor do gasto
    printf("Informe o valor do gasto[R$]: ");
    scanf("%f", &valores[*totalGastos]);

    // Solicita a descrição do gasto
    printf("Informe a descricao do gasto[...]: ");
    scanf(" %[^\n]s", descricoes[*totalGastos]);

    // Verifica se o gasto é essencial ou não essencial
    if (num == 1) { // Gasto Essencial
        printf("\n\n==== Categorias Essenciais ====\n");
        printf("1. Alimentacao\n");
        printf("2. Educacao\n");
        printf("3. Saude\n");
        printf("4. Transporte\n");
        printf("5. Roupas\n");
        printf("\n=== Contas ===\n");
        printf("6. Aluguel\n");
        printf("7. Conta de energia\n");
        printf("8. Conta de agua\n");
        printf("9. Conta de Internet\n");
        printf("10. Gas de cozinha\n\n");
        printf("Informe a categoria: ");
    } else if (num == 2) { // Gasto Não Essencial
        printf("\n\n==== Categorias Nao Essenciais ====\n");
        printf("1. Viagens\n");
        printf("2. Lazer (restaurante, cinema, entre outros)\n");
        printf("3. Televisao (streaming/cabo)\n");
        printf("4. Compras de produtos nao essenciais\n");
        printf("\nInforme a categoria: ");
    }

    // Solicita a categoria do gasto
    scanf("%d", &categorias[*totalGastos]);

    // Adiciona uma constante para diferenciar as categorias de essencial e não essencial
    if (num == 1) {
        categorias[*totalGastos] += 0; // Não há alteração na categoria
        // Garante que a categoria esteja no intervalo [1, 10]
        if (categorias[*totalGastos] > 10 || categorias[*totalGastos] < 1) {
            categorias[*totalGastos] = 11;
        }
    } else if (num == 2) {
        categorias[*totalGastos] += 11; // Adiciona 11 para diferenciar categorias não essenciais
        // Garante que a categoria esteja no intervalo [11, 15]
        if (categorias[*totalGastos] > 15 || categorias[*totalGastos] < 1) {
            categorias[*totalGastos] = 16;
        }
    }

    // Incrementa o contador de total de gastos
    (*totalGastos)++;

    // Limpa a tela
    limpa();
}


// Função para listar detalhes de uma compra específica
void listarGastos(int i, float valores[], char descricoes[][100], int categorias[], int quant) {
    printf("======= Compra n%i =======\n", quant);
    printf("Valor: R$ %.2f\n", valores[i]);
    printf("Descricao: %s\n", descricoes[i]);
    printf("Categoria: ");
    
    // Exibe a categoria com base no código
    switch (categorias[i]) {
        case 1:
            printf("Alimentacao\n");
            break;
        case 2:
            printf("Educacao\n");
            break;
        case 3:
            printf("Saude\n");
            break;
        case 4:
            printf("Transporte\n");
            break;
        case 5:
            printf("Roupas\n");
            break;
        case 6:
            printf("Aluguel\n");
            break;
        case 7:
            printf("Conta de energia\n");
            break;
        case 8:
            printf("Conta de agua\n");
            break;
        case 9:
            printf("Conta de Internet\n");
            break;
        case 10:
            printf("Gas de cozinha\n");
            break;
        case 11:
            printf("Sem categoria(ESSENCIAL)\n");
            break;
        case 12:
            printf("Viagens\n");
            break;
        case 13:
            printf("Lazer\n");
            break;
        case 14:
            printf("Televisao\n");
            break;
        case 15:
            printf("Produto\n");
            break;
        case 16:
            printf("Sem categoria(NAO ESSENCIAL)\n");
            break;
    }
}

// Função para chamar a lista de gastos com base na categoria (essencial, não essencial ou todos)
void chamaLista(int num, float valores[], char descricoes[][100], int categorias[], int *totalGastos, int cont) {
    int i, conta;

    // Lista de gastos essenciais
    if (num == 1) {
        if (cont == 0) {
            printf("Sem gastos essenciais adicionados!\n------------------------------------------------\n");
        } else {
            printf("==== Lista de Gastos Essenciais ====\n");
            conta = 0;
            
            // Loop para percorrer os gastos e exibir os essenciais
            for (i = 0; i < *totalGastos; i++) {
                if (categorias[i] <= 11) {
                    conta++;
                    listarGastos(i, valores, descricoes, categorias, conta);
                }
            }
        }
    }
    // Lista de gastos não essenciais
    else if (num == 2) {
        if (cont == 0) {
            printf("Sem gastos nao essenciais adicionados!\n------------------------------------------------\n");
        } else {
            conta = 0;
            printf("==== Lista de Gastos Nao Essenciais ====\n");
            
            // Loop para percorrer os gastos e exibir os não essenciais
            for (i = 0; i < *totalGastos; i++) {
                if (categorias[i] > 11) {
                    conta++;
                    listarGastos(i, valores, descricoes, categorias, conta);
                }
            }
        }
    }
    // Lista de todos os movimentos financeiros
    else if (num == 3) {
        if (cont == 0) {
            printf("Sem gastos adicionados!\n------------------------------------------------\n");
        } else if (num == 3) {
            conta = 0;
            printf("==== Lista de Movimentos financeiros ====\n");
            
            // Loop para percorrer todos os gastos
            for (i = 0; i < *totalGastos; i++) {
                conta++;
                listarGastos(i, valores, descricoes, categorias, conta);
            }
        }
    }
}

//Função usada para limpar a tela
void limpa() {
    system("cls");
}

// Função para excluir uma compra com base na posição informada
void excluirCompra(float valores[], char descricao[][100], int categorias[], int *totalGastos, int posicao, int *valorT, int *cont1, int *cont2, float essencial[], float desejoPessoal[]) {
    // Verifica se a posição informada é válida
    if (posicao > 0 && posicao <= *totalGastos + 1) {
        int i = 0, j = 0;

        // Verifica se a compra pertence à categoria essencial (1 a 11)
        if (categorias[posicao - 1] >= 1 && categorias[posicao - 1] <= 11) {
            (*cont1)--; // Reduz o contador de compras essenciais
            essencial[0] += valores[posicao - 1]; // Atualiza o total de gastos essenciais
        } else {
            (*cont2)--; // Reduz o contador de compras não essenciais
            desejoPessoal[0] += valores[posicao - 1]; // Atualiza o total de gastos não essenciais
        }

        *valorT = *valorT - valores[posicao - 1]; // Atualiza o valor total de gastos

        // Move os elementos seguintes uma posição para trás, sobrescrevendo a compra excluída
        for (i = posicao - 1; i < *totalGastos; i++) {
            categorias[i] = categorias[i + 1];
            valores[i] = valores[i + 1];
            for (j = 0; j < 100; j++) {
                descricao[i][j] = descricao[i + 1][j];
            }
        }

        limpa(); // Limpa a tela do console
        (*totalGastos)--; // Reduz o total de compras
        printf("Compra n%i excluida com sucesso!\n\n", posicao);
    } else {
        printf("Posicao invalida para exclusao.\n\n");
    }
}

// Função para registrar uma compra parcelada
void compraParcelada(int num, float dividas[][4], int *totaldividas, float *valTotDiv) {
    // Verifica se o limite de 15 dividas foi atingido
    if (*totaldividas >= 15) {
        printf("Erro: Limite de dividas atingido.\n");
        return;
    }

    int par = 0;
    int i = 0, cont = 0;
    float jurossimples = 0;
    float compraValor, valorParcela;

    // Verifica se já existe um financiamento registrado para a categoria num
    for (i = 0; i < *totaldividas; i++) {
        if (dividas[i][3] == num) {
            cont++;
        }
    }
    if (cont > 0) {
        printf("Financiamento ja registrado!\n");
        return;
    }

    printf("Digite o valor[R$]: ");
    scanf("%f", &compraValor);

    printf("Digite em quantas parcelas (max 12): ");
    scanf("%i", &par);

    if (par > 0 && par <= 12) {
        printf("Digite a taxa de juros [Se nao houver digite 0]: ");
        scanf("%f", &jurossimples);

        jurossimples /= 100;
        jurossimples *= compraValor;
        compraValor /= par;
        valorParcela = compraValor + jurossimples;

        compraValor = valorParcela * par;
        printf("Financiamento Registrado com sucesso!\n");
        printf("%i Parcelas de %.2f ------------- %.2f\n\n", par, valorParcela, compraValor);

        dividas[*totaldividas][0] = compraValor;
        dividas[*totaldividas][1] = valorParcela;
        dividas[*totaldividas][2] = par;
        *valTotDiv += compraValor;
        (*totaldividas)++;
        dividas[*totaldividas - 1][3] = num;

    } else {
        printf("Numero de parcelas deve estar entre 1 e 12.\n");
    }
}

// Função para calcular e registrar uma dívida com juros compostos
float jurosComposto(int num, float divida[][4], int *totaldividas, float *valTotDiv) {
    float valor = 0, juros = 0, taxajuros = 0, parcela = 0;
    int j, qtdpar;

    // Solicita o valor da dívida, a taxa de juros composto e o número de parcelas
    printf("Digite o valor[R$]: ");
    scanf("%f", &valor);
    printf("Digite a taxa de juros composto[%%]: ");
    scanf("%f", &taxajuros);
    printf("Quantas parcelas serao pagas (max 12): ");
    scanf("%i", &qtdpar);

    // Verifica se o número de parcelas é válido
    if (qtdpar > 12 || qtdpar < 1) {
        printf("\nNumero invalido de Parcelas!\n");
        return 0;
    }

    // Calcula os juros compostos se a taxa for maior que zero
    if (taxajuros > 0) {
        taxajuros = taxajuros / 100;
        for (j = 0; j < qtdpar; j++) {
            juros = valor * taxajuros;
            valor += juros;
        }
    }

    parcela = valor / qtdpar;

    // Registra a dívida com os dados calculados
    divida[*totaldividas][0] = valor;
    *valTotDiv += valor;
    divida[*totaldividas][1] = parcela;
    divida[*totaldividas][2] = qtdpar;

    // Define a categoria da dívida com base no parâmetro num
    if (num == 1) {
        divida[*totaldividas][3] = 3; // Categoria 3: Empréstimo
        printf("Emprestimo registrado com sucesso\n");
    } else {
        divida[*totaldividas][3] = 4; // Categoria 4: Conta em atraso
        printf("Conta em atraso registrada com sucesso\n");
    }

    (*totaldividas)++; // Incrementa o total de dívidas
    printf("%i Parcelas de %.2f ------------- %.2f\n\n", qtdpar, parcela, valor);

    return valor;
}

// Função para registrar movimentações financeiras
void registraFunc(float *totalAr, float valores[], float *totalGeral, int *cont, int totalGastos, float area[0]) {
    *totalAr = *totalAr + valores[totalGastos - 1];
    *totalGeral = *totalGeral + valores[totalGastos - 1];
    (*cont)++;
    area[0] = area[0] - valores[totalGastos - 1];
}

// Função para verificar se houve alteração no total de dívidas
int verify(int confere, int totaldividas) {
    if (confere == totaldividas) {
        return 0; // Sem alteração
    } else {
        return 1; // Houve alteração
    }
}

// Função para registrar dívidas e atualizar a reserva
void registraDiv(float dividas[][4], float reserva[], int totaldividas, int num) {
    int j = 0;
    int verifica[12] = {0};

    // Se num for 0, não há nada para registrar
    if (num == 0) {
        return;
    }

    // Se a dívida for de empréstimo, adiciona ao saldo da reserva
    if (dividas[totaldividas - 1][3] == 3) {
        reserva[0] += dividas[totaldividas - 1][0];
    }

    // Atualiza a reserva para cada parcela da dívida
    for (j = 0; j < dividas[totaldividas - 1][2]; j++) {
        if (verifica[j] == 0) {
            reserva[j] -= dividas[totaldividas - 1][1];
            verifica[j]++;
        }
    }
}

// Função para listar todas as dívidas registradas
void listadividas(float dividas[][4], int totaldividas) {
    int i = 0;

    // Verifica se há dívidas registradas
    if (totaldividas > 0) {
        for (i = 0; i < totaldividas; i++) {
            printf("-------------------------------------------------------------------------\n");
            // Identifica o tipo de dívida com base na categoria
            if (dividas[i][3] == 1) {
                printf("%i Financiamento Imobiliario ----- ", i + 1);
            } else if (dividas[i][3] == 2) {
                printf("%i- Financiamento Automotivo ---- ", i + 1);
            } else if (dividas[i][3] == 3) {
                printf("%i- Emprestimo ------------------ ", i + 1);
            } else if (dividas[i][3] == 4) {
                printf("%i- Conta em atraso ------------- ", i + 1);
            }
            // Exibe as informações da dívida
            printf("%.0f vezes de R$%.2f ------------ R$%.2f(total)\n", dividas[i][2], dividas[i][1], dividas[i][0]);
            printf("-------------------------------------------------------------------------\n\n");
        }
    } else {
        printf("Sem dividas registradas!\n");
        return;
    }
}

// Função para calcular o rendimento da reserva considerando a taxa CDI mensal
float cdi(float reserva[], int num) {
    float taxames = 0.1349 / 12.0; // taxa mensal do CDI
    float rends = 0;
    int i = 0;

    // Itera sobre os meses até o número especificado
    for (i = 0; i <= num; i++) {
        rends += reserva[i];
        rends = rends * (1 + taxames);
    }

    return rends;
}

// Função para calcular o valor da reserva emergencial subtraindo o rendimento CDI
float reservaEmergencial(float reservaIdeal, int num, float reserva[]) {
    float sub = 0, emergencial;
    sub = cdi(reserva, num);
    emergencial = reservaIdeal;
    emergencial -= sub;

    // Se o valor emergencial for negativo ou zero, retorna 0.0
    if (emergencial <= 0) {
        return 0.0;
    }

    return emergencial;
}

// Função para calcular a soma de um vetor de floats
float somarVetor(float vetor[], int tamanho) {
    if (tamanho == 0) {
        return 0;
    } else {
        return vetor[tamanho - 1] + somarVetor(vetor, tamanho - 1);
    }
}

// Função para calcular a média das dívidas em relação ao total de dívidas
float mediaDividas(float *valTotDiv, float somames) {
    if (*valTotDiv == 0) {
        return 0.0;
    }
    
    somames *= 100;
    somames = somames / (*valTotDiv);
    
    return somames;
}

// Função para calcular o somatório das parcelas de dívidas até um determinado número de meses
float percorreDividas(float dividas[][4], int totaldividas, int num) {
    int i = 0, j = 0;
    float somames = 0;

    // Itera sobre o número de meses
    for (i = 0; i < num; i++) {
        // Itera sobre as dívidas registradas
        for (j = 0; j < totaldividas; j++) {
            // Adiciona as parcelas das dívidas cujo número de parcelas é maior que o mês atual
            if (dividas[j][2] > i) {
                somames += dividas[j][1];
            }
        }
    }

    return somames;
}


// Função para verificar e lidar com saldos negativos nas categorias de gastos
void verificaNegativo(int num, float essencial[], float desejoPessoal[], float reserva[], float dividas[][4], int *totaldividas, float *totalDiv) {
    int cont = 0, parcela = 0, i = 0;
    float devendo, caixa;

    // Verifica saldos negativos nas categorias selecionadas
    if (num == 1) {
        if (essencial[0] < 0 || desejoPessoal[0] < 0 || reserva[0] < 0) {
            printf("\n7. SALDO NEGATIVO! em");

            // Identifica e imprime categorias com saldos negativos no menu principal
            if (essencial[0] < 0) {
                printf(" Compras essenciais");
                cont++;
            }
            if (reserva[0] < 0) {
                cont += 17;
            }
            if (desejoPessoal[0] < 0) {
                if (cont == 17 || cont == 0) {
                    printf(" Compras nao essenciais");
                }
                if (cont == 1) {
                    printf(" e Compras nao essenciais");
                } else if (cont == 18) {
                    printf(", Compras nao essenciais e Dividas");
                    cont++;
                }
            } else if (cont == 17) {
                printf(" Dividas");
            }
        }
    } else if (num == 2) {
        int escolha;
        int organiza[3] = {0};

        printf("Voce esta com SALDO NEGATIVO!\nEscolha uma opcao para parcelar");

        // Imprime opções disponíveis para parcelamento que estão negativas
        if (essencial[0] < 0) {
            printf("\n[1] - Compras essenciais --------- Saldo de: R$%.2f", essencial[0]);
            organiza[0] = 1;
        } if (desejoPessoal[0] < 0) {
            printf("\n[2] - Compras nao essenciais ----- Saldo de: R$%.2f", desejoPessoal[0]);
            organiza[1] = 1;
        } if (reserva[0] < 0) {
            printf("\n[3] - Dividas -------------------- Saldo de: R$%.2f", reserva[0]);
            organiza[2] = 1;
        }

        printf("\n[0] - Sair\n");
        printf("Digite aqui: ");
        scanf("%i", &escolha);
        cont = 0;

        // Estrutura de switch para lidar com a escolha do usuário
        switch (escolha) {
    		case 1:
        		// Caso o usuário escolha parcelar Compras Essenciais

        		if (organiza[0] == 0) {
            		printf("\nOPCAO INVALIDA!!");
            		break;
        		}

        		// Calcula o valor total devido nas Compras Essenciais
        		devendo = fabs(essencial[0]);
        		printf("Parcelar R$%.2f em quantas vezes? ", devendo);
        		*totalDiv += devendo;

        		// Lê o número de parcelas desejado
        		scanf("%i", &parcela);

        		for (i = 0; i < parcela; i++) {
            		caixa += reserva[i];
        		}

        		// Verifica se há saldo suficiente nas reservas
        		if (caixa < devendo) {
            		// Procura uma alternativa utilizando as Compras Não Essenciais
            		for (i = 0; i < parcela; i++) {
                		caixa += desejoPessoal[i];
                		if (caixa > devendo) {
                    		cont = i;
                		}
            		}

            		// Caso ainda não haja saldo suficiente, informa que o número de parcelas é inválido
            		if (caixa < devendo) {
                		printf("\nNumero de parcelas Invalido!\n");
                		return;
            		} else {
                		// Realiza o parcelamento e atualiza os saldos
                		printf("\n");
                		cont += parcela;
                		dividas[*totaldividas][0] = devendo;
                		devendo /= cont;
                		dividas[*totaldividas][1] = devendo;
                		dividas[*totaldividas][2] = parcela;
                		dividas[*totaldividas][3] = 4;

                		for (i = 0; i < parcela; i++) {
                    		reserva[i] -= devendo;
                    		printf("%i - RESERVA: R$%.2f\n", i + 1, reserva[i]);
                		}

                		printf("\n");

                		for (i = 0; i < cont; i++) {
                    		desejoPessoal[i] -= devendo;
                    		printf("%i - NAO ESSENCIAL: R$%.2f\n", i + 1, desejoPessoal[i]);
                		}

                		essencial[0] += devendo * 2;
            		}
        		} else {
            		// Realiza o parcelamento e atualiza os saldos
            		dividas[*totaldividas][0] = devendo;
            		devendo /= parcela;
            		dividas[*totaldividas][1] = devendo;
            		dividas[*totaldividas][2] = parcela;
            		dividas[*totaldividas][3] = 4;
            		essencial[0] += devendo;

            		for (i = 0; i < parcela; i++) {
                		reserva[i] -= devendo;
                		printf("%i - RESERVA: R$%.2f\n", i + 1, reserva[i]);
            		}
        		}

        		(*totaldividas)++;
        		devendo = fabs(essencial[0]);

        		// Verifica se o saldo de Compras Essenciais é suficiente após o parcelamento
        		if (essencial[0] <= 0) {
            		// Se houver saldo em Compras Não Essenciais, atualiza os saldos
            		if (desejoPessoal[0] > 0) {
                		if (desejoPessoal[0] > devendo) {
                    		essencial[0] = desejoPessoal[0];
                    		desejoPessoal[0] = 0;
                		} else {
                    		devendo -= desejoPessoal[0];
                    		essencial[0] += desejoPessoal[0];
                    		desejoPessoal[0] = 0;

                    		devendo -= reserva[0];
                    		essencial[0] += reserva[0];
                    		reserva[0] = 0;

                    		if (devendo > 0) {
                        		printf("\nNECESSIDADE DE EMPRESTIMO!!\n");
                        		return;
                    		}
                		}
            		} else {
                		// Se não houver saldo em Compras Não Essenciais, atualiza os saldos
                		devendo -= reserva[0];
                		essencial[0] += reserva[0];
                		reserva[0] = 0;

                		if (devendo > 0) {
                    		printf("\nNECESSIDADE DE EMPRESTIMO!!\n");
                    		return;
                		}
            		}
        		}
        		break;

    		case 2:
        		// Caso o usuário escolha parcelar Compras Não Essenciais

        		if (organiza[1] == 0) {
            		printf("\nOPCAO INVALIDA!!");
            		break;
        		}

        		// Calcula o valor total devido em Compras Não Essenciais
        		devendo = fabs(desejoPessoal[0]);
        		printf("Parcelar R$%.2f em quantas vezes? ", devendo);
        		*totalDiv += devendo;

        		// Lê o número de parcelas desejado
        		scanf("%i", &parcela);

        		for (i = 0; i < parcela; i++) {
            		caixa += reserva[i];
        		}

        		// Verifica se há saldo suficiente nas reservas
        		if (caixa < devendo) {
            		// Procura uma alternativa utilizando as Compras Essenciais
            		for (i = 0; i < parcela; i++) {
                	caixa += desejoPessoal[i];
                		if (caixa > devendo) {
                    	cont = i;
                	}
            	}

            		// Caso ainda não haja saldo suficiente, informa que o número de parcelas é inválido
            		if (caixa < devendo) {
                		printf("\nNumero de parcelas Invalido!\n");
                		return;
            		} else {
                		// Realiza o parcelamento e atualiza os saldos
                		printf("\n");
                		cont += parcela;
                		dividas[*totaldividas][0] = devendo;
                		devendo /= cont;
                		dividas[*totaldividas][1] = devendo;
                		dividas[*totaldividas][2] = parcela;
                		dividas[*totaldividas][3] = 4;

                		for (i = 0; i < parcela; i++) {
                    		reserva[i] -= devendo;
                    		printf("%i - RESERVA: R$%.2f\n", i + 1, reserva[i]);
                		}

                		printf("\n");

                		for (i = 0; i < cont; i++) {
                    		desejoPessoal[i] -= devendo;
                    		printf("%i - NAO ESSENCIAL: R$%.2f\n", i + 1, desejoPessoal[i]);
                		}

                		desejoPessoal[0] += devendo * 2;
            		}
        		} else {
            		// Realiza o parcelamento e atualiza os saldos
            		dividas[*totaldividas][0] = devendo;
            		devendo /= parcela;
            		dividas[*totaldividas][1] = devendo;
            		dividas[*totaldividas][2] = parcela;
            		dividas[*totaldividas][3] = 4;
            		desejoPessoal[0] += devendo;

            		for (i = 0; i < parcela; i++) {
                		reserva[i] -= devendo;
                		printf("%i - RESERVA: R$%.2f\n", i + 1, reserva[i]);
            		}
        		}

        		(*totaldividas)++;
        		devendo = fabs(desejoPessoal[0]);

        		// Verifica se o saldo de Compras Não Essenciais é suficiente após o parcelamento
        		if (desejoPessoal[0] <= 0) {
            		// Se houver saldo em Reservas, atualiza os saldos
            		if (reserva[0] > 0) {
                		if (reserva[0] > devendo) {
                    		desejoPessoal[0] += devendo;
                    		reserva[0] -= devendo;
                		} else {
                    		devendo -= reserva[0];
                    		essencial[0] += reserva[0];
                    		reserva[0] = 0;

                    		if (devendo > 0) {
                        		printf("\nNECESSIDADE DE EMPRESTIMO!!\n");
                        		return;
                    		}
                		}
            		}
        		}
        		break;

            case 3:
    			// Caso o usuário escolha parcelar Dívidas

   				if (organiza[2] == 0) {
        			printf("\nOPCAO INVALIDA!!");
        			break;
    			}

    			// Calcula o valor total devido em Dívidas
    			devendo = fabs(reserva[0]);
    			printf("Parcelar R$%.2f em quantas vezes? ", devendo);
    			*totalDiv += devendo;

    			// Lê o número de parcelas desejado
    			scanf("%i", &parcela);

    			caixa = devendo;

    			for (i = 0; i < parcela; i++) {
        			caixa += reserva[i];
    			}

    			// Verifica se há saldo suficiente nas reservas
    			if (caixa < devendo) {
        			// Procura uma alternativa utilizando as Compras Não Essenciais
        			for (i = 0; i < parcela; i++) {
            			caixa += desejoPessoal[i];
            			if (caixa > devendo) {
                			cont = i;
            			}
        			}

        			// Caso ainda não haja saldo suficiente, informa que o número de parcelas é inválido
        			if (caixa < devendo) {
            			printf("\nNumero de parcelas Invalido!\n");
            			return;
        			} else {
            			// Realiza o parcelamento e atualiza os saldos
            			printf("\n");
            			cont += parcela;
            			*totalDiv += devendo;
            			dividas[*totaldividas][0] = devendo;
            			devendo /= cont;
            			dividas[*totaldividas][1] = devendo;
            			dividas[*totaldividas][2] = parcela;
            			dividas[*totaldividas][3] = 4;

            			for (i = 0; i < parcela; i++) {
                			reserva[i] -= devendo;
            			}

            			printf("\n");

            			for (i = 0; i < cont; i++) {
                			desejoPessoal[i] -= devendo;
           				}
        			}
    			} else {
        			// Realiza o parcelamento e atualiza os saldos
        			dividas[*totaldividas][0] = devendo;
        			reserva[0] += devendo;
        			devendo /= parcela;
        			dividas[*totaldividas][1] = devendo;
        			dividas[*totaldividas][2] = parcela;
        			dividas[*totaldividas][3] = 4;

        			for (i = 0; i < parcela; i++) {
            			reserva[i] -= devendo;
        			}
    			}

    			// Verifica se há saldo em Compras Não Essenciais após o parcelamento
    			if (desejoPessoal[0] > 0) {
        			devendo = fabs(reserva[0]);

        			// Se houver, verifica se o saldo em Reservas é suficiente
        			if (desejoPessoal[0] > devendo) {
            			desejoPessoal[0] -= devendo;
            			reserva[0] += fabs(reserva[0]);
        			} else {
            			reserva[0] += desejoPessoal[0];
            			desejoPessoal[0] = 0;

						printf("\nNECESSIDADE DE EMPRESTIMO!!\n");
            			return;
        			}
    			}
    			break;
			//Voltando ao menu
            case 0:
                printf("\nVoltando ao Menu!\n");
                return;
            default:
                limpa();
                printf("\n!!OPCAO INVALIDA!!\n!!TENTE NOVAMENTE!!\n\n");
        }
    }
}

// Função que calcula o número de meses necessários para atingir a reserva ideal.
int planoMeses(float renda, float reserva[], int num, float reservaIdeal, int totaldividas, float dividas[][4]) {
    // Calcula 20% da renda para ser adicionado à reserva a cada mês.
    float reserva_ = (renda * 20) / 100;
    int i = 0, j = 0;
    float mes = 0, mesIdeal = 0, reservaMensal = 0, divida = 0;

    // Encontra o prazo máximo das dívidas.
    for (i = 0; i < totaldividas; i++) {
        if (dividas[i][2] > mes) {
            mes = dividas[i][2];
        }
    }

    // Itera sobre os meses até atingir a reserva ideal.
    for (i = 1; i <= mes; i++) {
        divida = 0;

        // Calcula o total das dívidas que vencem no mês atual.
        for (j = 0; j < totaldividas; j++) {
            if (reservaMensal <= reservaIdeal) {
                if (dividas[j][2] >= i) {
                    divida += dividas[j][1];
                }
            }
        }

        // Atualiza a reserva mensal, subtraindo as dívidas e adicionando a reserva esperada.
        reservaMensal += reserva_ - divida;

        // Verifica se a reserva mensal atingiu ou ultrapassou a reserva ideal.
        if (reservaMensal >= reservaIdeal) {
            if (mesIdeal == 0) {
                mesIdeal = i;
            }
        }
    }

    // Retorna o número de meses total ou o número de meses necessários para atingir a reserva ideal.
    if (num == 1) {
        return mes;
    } else { // Verifica se o código já tem a quantidade meses para atingir a reserva ideal
        i = mes;
        if (mesIdeal == 0) {
            do { // Casso não tenha, entra em um laço de repetição até descobrir o mês que atingirá a reserva ideal
                i++;
                reservaMensal += reserva_;
                mesIdeal++;
            } while (reservaMensal < reservaIdeal);
        }
    }

    return mesIdeal + mes;
}

// Função que aloca dinamicamente um vetor de floats.
float *alocarVetor(int tamanho) {
    return (float *)malloc(tamanho * sizeof(float));
}

// Função que libera a memória alocada para um vetor de floats.
void liberarVetor(float *vetor) {
    free(vetor);
}


// Função que gera um extrato com base nas informações fornecidas e salva em um arquivo.
void gerarExtrato(int total, float valores[], char descricoes[][100], int categorias[], char *nomeArquivo) {
    // Abre o arquivo especificado para escrita.
    FILE *arquivo = fopen(nomeArquivo, "w");

    // Verifica se ocorreu algum erro na abertura do arquivo.
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrever.\n");
        return;
    }

    // Escreve o cabeçalho do extrato no arquivo.
    fprintf(arquivo, "======= Extrato =======\n");

    int i = 0;
    // Loop para percorrer todas as compras no extrato.
    for (i = 0; i < total; ++i) {
        // Escreve informações sobre cada compra no arquivo.
        fprintf(arquivo, "======= Compra n%i =======\n", i + 1);
        fprintf(arquivo, "Valor: R$ %.2f\n", valores[i]);
        fprintf(arquivo, "Descricao: %s\n", descricoes[i]);
        fprintf(arquivo, "Categoria: ");

        // Switch para identificar e escrever a categoria da compra no arquivo.
        switch (categorias[i]) {
            case 1:
                fprintf(arquivo, "Alimentacao\n");
                break;
            case 2:
                fprintf(arquivo, "Educacao\n");
                break;
            case 3:
                fprintf(arquivo, "Saude\n");
                break;
            case 4:
                fprintf(arquivo, "Transporte\n");
                break;
            case 5:
                fprintf(arquivo, "Roupas\n");
                break;
            case 6:
                fprintf(arquivo, "Aluguel\n");
                break;
            case 7:
                fprintf(arquivo, "Conta de energia\n");
                break;
            case 8:
                fprintf(arquivo, "Conta de agua\n");
                break;
            case 9:
                fprintf(arquivo, "Conta de Internet\n");
                break;
            case 10:
                fprintf(arquivo, "Gas de cozinha\n");
                break;
            case 11:
                fprintf(arquivo, "Sem categoria(ESSENCIAL)\n");
                break;
            case 12:
                fprintf(arquivo, "Viajens\n");
                break;
            case 13:
                fprintf(arquivo, "Lazer\n");
                break;
            case 14:
                fprintf(arquivo, "Televisao\n");
                break;
            case 15:
                fprintf(arquivo, "Produto\n");
                break;
            case 16:
                fprintf(arquivo, "Sem categoria(NAO ESSENCIAL)\n");
                break;
            default:
                fprintf(arquivo, "Categoria desconhecida\n");
        }

        fprintf(arquivo, "\n");
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivo);

    // Exibe mensagem de sucesso junto com o nome do arquivo gerado.
    printf("Extrato gerado com sucesso no arquivo: %s\n\n", nomeArquivo);
}


// Função que gera um extrato de dívidas em um arquivo.
void extratoDividas(float dividas[][4], int totaldividas) {
    // Abre o arquivo "extrato_dividas.txt" para escrita.
    FILE *arquivoExtrato = fopen("extrato_dividas.txt", "w");

    // Verifica se ocorreu algum erro na abertura do arquivo.
    if (arquivoExtrato == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrever.\n");
        return;
    }

    int i = 0;

    // Verifica se há dívidas registradas.
    if (totaldividas > 0) {
        // Loop para percorrer todas as dívidas registradas.
        for (i = 0; i < totaldividas; i++) {
            // Escreve uma linha de separação no arquivo.
            fprintf(arquivoExtrato, "-------------------------------------------------------------------------\n");

            // Identifica o tipo de dívida e escreve a descrição correspondente.
            if (dividas[i][3] == 1) {
                fprintf(arquivoExtrato, "%i Financiamento Imobiliario ----- ", i + 1);
            } else if (dividas[i][3] == 2) {
                fprintf(arquivoExtrato, "%i- Financiamento Automotivo ---- ", i + 1);
            } else if (dividas[i][3] == 3) {
                fprintf(arquivoExtrato, "%i- Emprestimo ------------------ ", i + 1);
            } else if (dividas[i][3] == 4) {
                fprintf(arquivoExtrato, "%i- Conta em atraso ------------- ", i + 1);
            }

            // Escreve as informações sobre a dívida no arquivo.
            fprintf(arquivoExtrato, "%.0f vezes de R$%.2f ------------ R$%.2f(total)\n", dividas[i][2], dividas[i][1], dividas[i][0]);

            // Escreve uma linha de separação no arquivo.
            fprintf(arquivoExtrato, "-------------------------------------------------------------------------\n\n");
        }
    } else {
        // Caso não haja dívidas registradas, escreve uma mensagem no arquivo.
        fprintf(arquivoExtrato, "Sem dividas registradas!\n");
    }

    // Fecha o arquivo após concluir a escrita.
    fclose(arquivoExtrato);

    // Exibe mensagem de sucesso junto com o nome do arquivo gerado.
    printf("Extrato gerado com sucesso no arquivo: extrato_dividas.txt\n\n");
}



