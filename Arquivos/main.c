#include <stdio.h>#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "henrique.h" // Inclusao de um arquivo de cabecalho personalizado

int main() {
    // Declaracao de variáveis
    int tamanho = 0, colunaMatriz = 0;
    tamanho = 12;
    float *essencial = alocarVetor(tamanho);
    float *desejoPessoal = alocarVetor(tamanho);
    float *reserva = alocarVetor(tamanho);
    tamanho = 100;
    float *valores = alocarVetor(tamanho);
    int *categorias = alocarVetor(tamanho);
    char descricoes[100][100] = {{0}};
    float dividas[15][4] = {{0}};
    float renda, totalEs, totalNes, totalDiv, total, reservaIdeal = 0, somames = 0;
    int posicao, escolha, totalGastos = 0, escolha_est, cont1 = 0, cont2 = 0, totaldividas = 0, i = 0;
    FILE *arquivoCompras;
    FILE *arquivoDividas;

    // Apresentacao do programa
    printf("============================\n");
    printf("============================\n");
    printf("== Planejamento de Gastos ==\n");
    printf("============================\n");
    printf("============================\n\n");
    printf("Digite sua renda mensal liquida: ");
    
    // Entrada da renda
    // Caso tenha adicionado um banco de dados, comente as duas próximas linhas
    scanf("%f", &renda);
    planejamentoGasto(renda, essencial, desejoPessoal, reserva); // Funcao para planejamento de gastos
    reservaIdeal = ((renda * 80) / 100) * 6;

    // Apresentacao das categorias e porcentagens
    printf("\nNecessidades: R$%.2f - 50%%\nDevem estar incluidas nessa categoria despesas necessarias para nossa\nsubsistencia basica, como por exemplo, aluguel, alimentacao, transporte etc", essencial[0]);
    printf("\n\nDesejos pessoais: R$%.2f - 30%%\nTodos os gastos com bens de consumo e servicos que nao forem essenciais\ndevem estar incluidos nessa categoria.\n", desejoPessoal[0]);
    printf("\nReserva e pagamento de dividas: R$%.2f - 20%%\nHora de separar uma parte da sua renda para quitar dividas, montar uma\nreserva financeira ou diversificar a carteira de investimentos. Esta parcela\nrepresenta suas economias e metas financeiras.\n", reserva[0]);
    printf("\n=================================================================================\n");

    // Loop principal
    while (1) {
        // Menu de opcões
        printf("\n1. Gerenciar Necessidades: [50%%]");
        printf("\n2. Gerenciar Desejos pessoais: [30%%]");
        printf("\n3. Gerenciar Reserva e dividas: [20%%]");
        printf("\n4. Excluir Registro");
        printf("\n5. Rendimentos e Pagamentos");
        printf("\n6. Gerar Extrato (.txt)");
        //Funcao abaixo verifica se o user está negativo em alguma área e libera uma nova opcao no menu
        verificaNegativo(1, essencial, desejoPessoal, reserva, dividas, &totaldividas, &totalDiv);
        printf("\n\n0. Encerrar\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &escolha);
        limpa();

        // Estrutura de selecao
        switch (escolha) {
            case 1:
                // Gerenciamento de compras essenciais
                while (1) {
                    printf("====Compras essenciais====\n");
                    printf("\n====Saldo - R$%.2f====\n", essencial[0]);
                    printf("1. Adicionar Gastos");
                    printf("\n2. Listar Gastos");
                    printf("\n3. Voltar\n");
                    printf("Digite a opcao desejada: ");
                    scanf("%i", &escolha_est);

                    // Switch interno para compras essenciais
                    switch (escolha_est) {
                        case 1:
                            // Adicao de gasto essencial
                            adicionarGasto(1, valores, descricoes, categorias, &totalGastos);
                            registraFunc(&totalEs, valores, &total, &cont1, totalGastos, essencial);
                            break;
                        case 2:
                            // Listagem de gastos essenciais
                            limpa();
                            chamaLista(1, valores, descricoes, categorias, &totalGastos, cont1);
                            break;
                        case 3:
                            // Voltar ao menu principal
                            limpa();
                            printf("--------------------------------\n");
                            printf("Voltando ao menu!\n");
                            escolha_est = 0;
                            break;
                        default:
                            limpa();
                            printf("\n!!OPCAO INVALIDA!!\n!!TENTE NOVAMENTE!!\n\n");
                            break;
                    }
                    // Se a escolha for 0, sai do loop interno
                    if (escolha_est == 0) {
                        break;
                    }
                }
                break;
            case 2:
    			// Loop para gerenciar gastos relacionados a desejos pessoais
    			while (1) {
        			printf("====Desejos Pessoais====\n");
        			printf("\n====Saldo - R$%.2f====\n", desejoPessoal[0]);
        			printf("1. Adicionar Gastos");
        			printf("\n2. Listar Gastos");
        			printf("\n3. Voltar\n");
        			printf("Digite a opcao desejada: ");
        			scanf("%i", &escolha_est);
        			
        			// Switch interno para a gestao de desejos pessoais
        			switch (escolha_est) {
            			case 1:
                			// Adicionar gasto relacionado a desejos pessoais
                			adicionarGasto(2, valores, descricoes, categorias, &totalGastos);
                			//Registra os dados nas variaveis e arrays
							registraFunc(&totalNes, valores, &total, &cont2, totalGastos, desejoPessoal);
                			break;
            			case 2:
                			// Listar gastos relacionados a desejos pessoais
                			limpa();
                			chamaLista(2, valores, descricoes, categorias, &totalGastos, cont2);
                			break;
            			case 3:
                			// Voltar ao menu principal
                			limpa();
                			printf("--------------------------------\n");
                			printf("Voltando ao menu!\n");
                			escolha_est = 0;
                			break;
            			default:
                			limpa();
                			printf("\n!!OPCAO INVALIDA!!\n!!TENTE NOVAMENTE!!\n\n");
                			break;
        			}
        			// Se a escolha for 0, sai do loop interno
        			if (escolha_est == 0) {
            			break;
        			}
    			}
    		break;
            case 3:
    			limpa();
    			while (1) {
        			// Exibicao do saldo poupado na reserva
        			printf("\n=== Saldo poupado - R$%.2f ===\n", reserva[0]);
        			printf("1. Financiamento Imobiliario\n");
        			printf("2. Financiamento Automotivo\n");
        			printf("3. Emprestimo\n");
        			printf("4. Conta em atraso\n");
        			printf("5. Visualizar Pendencias\n");
        			printf("6. Voltar\n");
        			printf("\nDigite a opcao desejada: ");
        			scanf("%i", &escolha_est);
        			
        			switch (escolha_est) {
            			int confere;
            			case 1:
                		// Financiamento Imobiliário
                			limpa();
                			confere = totaldividas;
                			compraParcelada(1, dividas, &totaldividas, &totalDiv);
                			registraDiv(dividas, reserva, totaldividas, verify(confere, totaldividas));
                			break;
            			case 2:
                			// Financiamento Automotivo
                			limpa();
                			confere = totaldividas;
                			compraParcelada(2, dividas, &totaldividas, &totalDiv);
                			registraDiv(dividas, reserva, totaldividas, verify(confere, totaldividas));
                			break;
            			case 3:
                			// Empréstimo
							limpa();
                			confere = totaldividas;
                			jurosComposto(1, dividas, &totaldividas, &totalDiv);
                			registraDiv(dividas, reserva, totaldividas, verify(confere, totaldividas));
                			break;
            				case 4:
                				// Conta em atraso
                				limpa();
                				confere = totaldividas;
                				jurosComposto(2, dividas, &totaldividas, &totalDiv);
                				registraDiv(dividas, reserva, totaldividas, verify(confere, totaldividas));
                				break;
            				case 5:
                				// Visualizar Pendências
                				limpa();
                				listadividas(dividas, totaldividas);
                				break;
            				case 6:
                				// Voltar ao menu principal
                				limpa();
                				printf("--------------------------------\n");
                				printf("Voltando ao menu!\n");
                				escolha_est = 0;
                				break;
            				default:
                				limpa();
                				printf("\n!!OPCAO INVÁLIDA!!\n!!TENTE NOVAMENTE!!\n\n");
                				break;
        				}
        				if (escolha_est == 0) {
            				break;
        				}
    				}
    			break;
            case 4:
    			limpa();
    			int cont3;
    			cont3 = cont1 + cont2;

    			// Verifica se há itens para excluir
    			if (totalGastos == 0) {
        		printf("Sem itens para excluir!\n\n");
        		break;
    			} else {
        		// Exibe a lista de compras para selecao
        			chamaLista(3, valores, descricoes, categorias, &totalGastos, cont3);
        			printf("\nSelecione qual compra excluir: ");
        			scanf("%i", &posicao);
        			// Exclui a compra selecionada
        			excluirCompra(valores, descricoes, categorias, &totalGastos, posicao, &total, &cont1, &cont2, essencial, desejoPessoal);
    			}
    			break;

			case 5:
    			limpa();
    			printf("===Rendimentos e Pagamentos===\n");
    			printf(" - O primeiro passo e reduzir as dividas e depois colocar\n na poupanca, criando assim uma reserva emergencial\n");
    			printf("\n - A reserva emergencial deve ser 6x o valor que você gasta");
    			printf("\n\n--- Sua reserva emergencial deve ser de: R$%.2f ----\n", reservaIdeal);
    			printf("--- Sua reserva esta guardada no Nubank - Rendendo 100%% do CDI---");
    
    			//Exibicao de dados que mostra a ineficácia da técnica 50 30 20 pra realidade do brasileiro
				printf("\n\n==========================DADOS GERAIS==========================\n");
    			printf("------------ Em %i meses quitara 100%% das suas Dividas -------------\n", planoMeses(renda, reserva, 1, reservaIdeal, totaldividas, dividas));
    			printf("-------- Em %i meses chegara na Reserva Emergencial IDEAL --------\n", planoMeses(renda, reserva, 2, reservaIdeal, totaldividas, dividas));
    			printf("=================================================================\n\n");

    			// Calcula informacões para o primeiro mês
    			printf("\n\n============================EM 1 MES============================\n");
    			somames = percorreDividas(dividas, totaldividas, 1);
    			reservaIdeal = ((renda * 80) / 100) * 6;
    			reservaIdeal = reservaEmergencial(reservaIdeal, 1, reserva);

    			// Exibe informacões sobre gastos, dividas e reserva
    			printf("Reserva Emergencial -------- R$%.2f | Faltam R$%.2f para o ideal \n", cdi(reserva, 1), reservaIdeal);
    			printf("Dividas Quitadas ----------- R$%.2f | Foram %.2f%% delas         \n", somames, mediaDividas(&totalDiv, somames));
    			printf("Gastos Necessarios --------- R$%.2f \n", somarVetor(essencial, 1));
    			printf("Gastos Nao Essenciais ------ R$%.2f \n", somarVetor(desejoPessoal, 1));
    
            	printf("\n\n============================EM 3 MES============================\n");
            	reservaIdeal = ((renda*80)/100)*6;
				reservaIdeal = reservaEmergencial(reservaIdeal, 3, reserva);
				somames = percorreDividas(dividas, totaldividas, 3);
            
				printf("Reserva Emergencial -------- R$%.2f | Faltam R$%.2f para o ideal \n", cdi(reserva, 3), reservaIdeal);
            	printf("Dividas Quitadas ----------- R$%.2f | Foram %.2f%% delas         \n", somames, mediaDividas(&totalDiv, somames));
            	printf("Gastos Necessarios --------- R$%.2f \n", somarVetor(essencial, 3));
            	printf("Gastos Nao Essenciais ------ R$%.2f \n", somarVetor(desejoPessoal,3));
            	
            	printf("\n\n===========================EM 6 MESES===========================\n");
            	reservaIdeal = ((renda*80)/100)*6;
				reservaIdeal = reservaEmergencial(reservaIdeal, 6, reserva);
				somames = percorreDividas(dividas, totaldividas, 6);
            
				printf("Reserva Emergencial -------- R$%.2f | Faltam R$%.2f para o ideal \n", cdi(reserva, 6), reservaIdeal);
            	printf("Dividas Quitadas ----------- R$%.2f | Foram %.2f%% delas         \n", somames, mediaDividas(&totalDiv, somames));
            	printf("Gastos Necessarios --------- R$%.2f \n", somarVetor(essencial, 6));
            	printf("Gastos Nao Essenciais ------ R$%.2f \n", somarVetor(desejoPessoal,6));
            	break;
            case 6:
    			limpa();
    			int escolha_ext;

    			// Loop para o menu de geracao de extrato
    			while (1) {
        			printf("===GERAR EXTRATO===\n");
        			printf("[1] - Compras\n");
        			printf("[2] - Dividas\n");
        			printf("[3] - Sair\n");
        			printf("Escolha a opcao: ");
        			scanf("%i", &escolha_ext);

        			switch (escolha_ext) {
            			case 1:
                		// Geracao de extrato para compras
                			gerarExtrato(totalGastos, valores, descricoes, categorias, "compras_extrato.txt");
                			break;
            			case 2:
                			// Geracao de extrato para dividas
                			extratoDividas(dividas, totaldividas);
                			break;
            			case 3:
                			// Sair do menu de geracao de extrato
                			printf("--------------------------------\n");
                			printf("Voltando ao menu.\n");
                			break;
            			default:
                			limpa();
                			printf("\n!!OPCAO INVaLIDA!!\n!!TENTE NOVAMENTE!!\n\n");
        			}
        			
        			// Se a escolha for 3 (Sair), encerra o loop
        			if (escolha_ext == 3) {
            			break;
        			}
    			}
    		break;
            case 7:
            	limpa();
            	//a funcao exibe um submenu com opcões para o usuario arrumar seu saldo
            	verificaNegativo(2, essencial, desejoPessoal, reserva, dividas, &totaldividas, &totalDiv);
			break;
            case 0:
            	//encerrando o programa
            	limpa();
            	liberarVetor(valores);
				liberarVetor(essencial);
				liberarVetor(desejoPessoal);
				liberarVetor(reserva);
				liberarVetor(categorias);
            	printf("--------------------------------\n");
                printf("  Saindo do programa. Ate mais!");
                exit(0);
            default:
            	limpa();
                printf("\n!!OPCAO INVALIDA!!\n!!TENTE NOVEMENTE!!\n\n");
        }
    }
    return 0;
}
