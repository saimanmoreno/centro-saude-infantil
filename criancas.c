#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "users.h"


// declaração da lista (struct com campo de dados e ponteiro) /////////////////////////////////////////////////////////////////////////////////////////
typedef struct crianca {
	int bi;
	String nome;
	String dtnasc;
	String sexo;
	String tipopart;
	float tempgest;
	float pesonasc;
	float altnasc;
	float pcefnasc;
	int parentes[2];
	struct crianca *prox;  
} CRIANCA;


// variaveis globais
CRIANCA *criancas = NULL;	// inicialmente a lista esta vazia /////////////////////////////////////////////////////////////////////////////////////////



// funcao que guarda a lista de criancas num ficheiro txt /////////////////////////////////////////////////////////////////////////////////////////
void guardarListaCriancas() {

	FILE *file;
	CRIANCA *aux;

	file = fopen("base-dados/criancas.txt", "wb");

	if (file == NULL){
		printf("\n\n  ERRO NO ACESSO AO FICHEIRO! \n\n"); getchar(); getchar();
		exit(1);
	}

	aux = criancas;

	while (aux!=NULL){

		fwrite(aux, sizeof(CRIANCA), 1, file);
		aux = aux -> prox;
	}

	fclose(file);
}


// funcao que le os dados guardaddos no ficheiro e os carregue na lista de criancas /////////////////////////////////////////////////////////////////////////////////////////
CRIANCA* carregarListaCriancas() {

	FILE *file;
	CRIANCA *lista=NULL, *atual=NULL, temp, *novo_no;
	int i;

	file = fopen("base-dados/criancas.txt", "rb");

	if (file == NULL){
		system("clear"); printf("  ERRO NO ACESSO AO FICHEIRO! "); pause();
		exit(1);
	}

	while (fread(&temp, sizeof(CRIANCA), 1, file) != 0){

		novo_no = (CRIANCA *)malloc(sizeof(CRIANCA));

		novo_no->bi = temp.bi;
		strcpy(novo_no->nome, temp.nome);
		strcpy(novo_no->sexo, temp.sexo);
		strcpy(novo_no->dtnasc, temp.dtnasc);
		strcpy(novo_no->tipopart, temp.tipopart);
		novo_no->tempgest = temp.tempgest;
		novo_no->pesonasc = temp.pesonasc;
		novo_no->altnasc = temp.altnasc;
		novo_no->pcefnasc = temp.pcefnasc;

		if (lista == NULL) {
			
			lista = novo_no;
			atual = novo_no;
		
		} else{

			atual->prox = novo_no;
			atual = novo_no;
		}
	}

	novo_no->prox = NULL;

	fclose(file);

	return lista;
}


// funcao que verifica se a lista esta vazia /////////////////////////////////////////////////////////////////////////////////////////
int listaCriancaVazia() {

	if (criancas == NULL)
		return 1;
	else
		return 0;
}


// funcao que recebe memoria alocada e preenche os dados da nova crianca /////////////////////////////////////////////////////////////////////////////////////////
CRIANCA* preencherC(CRIANCA* novo){

	printf("  Numero do bi: "); scanf("%d", &novo->bi);
	printf("  Nome: "); scanf("%s", novo->nome); 
	printf("  Dt Nasc. (dd/mm/aaaa): "); scanf("%s", novo->dtnasc); 
	printf("  Sexo: "); scanf("%s", novo->sexo); 
	printf("  Tipo parto: "); scanf("%s", novo->tipopart); 
	printf("  Tempo gest.: "); scanf("%f", &novo->tempgest); 
	printf("  Peso nasc.: "); scanf("%f", &novo->pesonasc);
	printf("  Altura nasc.: "); scanf("%f", &novo->altnasc);
	printf("  P. cef. nasc.: "); scanf("%f", &novo->pcefnasc);

	return novo;
}


// funcao que recebe uma crianca e mostra os seus dados /////////////////////////////////////////////////////////////////////////////////////////
void mostrarDadosCrianca (CRIANCA *crianca){

	USER *pai, *mae;

	pai = getUserById(crianca->parentes[0]);
	mae = getUserById(crianca->parentes[1]);

	printf("\n\n  ------------------------------------------------------------------------\n");
	printf("  \n\t\t\t\t\t\t  BI: %d\n", crianca->bi);
	printf("  Nome: %s\n", crianca->nome);
	printf("  Data de nascimento.: %s\n", crianca->dtnasc);
	printf("  Sexo: %s\n", crianca->sexo);
	printf("  Pai: %s\n", pai->nome);
	printf("  Mae: %s\n", mae->nome);
	printf("  Tipo parto: %s\n", crianca->tipopart);
	printf("  Tempo gestacao.: %.1f semanas\n", crianca->tempgest);
	printf("  Peso a nascenca.: %.1f Kg.\n", crianca->pesonasc);
	printf("  Altura a nascenca.: %.1f cm.\n", crianca->altnasc);
	printf("  perimetro cefalico a nascenca: %.1fcm.\n", crianca->pcefnasc);
	printf("\n  ------------------------------------------------------------------------\n\n");
}


// funcao que adiciona uma novo crianca no final da lista de criancas /////////////////////////////////////////////////////////////////////////////////////////
void registarCrianca(){

	CRIANCA *novo, *aux;
	USER *novoUser, *auxUser;

	printf(" %c----------------------------------------------------------------%c\n",201,187);
	printf(" |                        Registar Crianca                        |\n");
	printf(" %c----------------------------------------------------------------%c\n",200,188);

	novo = (CRIANCA *)malloc(sizeof(CRIANCA));

	if (novo == NULL) {
		printf("\n\n  Erro na Alocacao da Memoria!  \n\n");
		exit(1);
	} 

	novo = preencherC(novo);

	if (listaCriancaVazia()) {

		criancas = novo;

	} else {
		
		aux = criancas;
	
		while ( aux->prox != NULL ) 
			aux = aux->prox;

		aux -> prox = novo;

	}

	for (int i = 0; i < 2; i++)	{

		system("clear");
		(i == 0) ? printf("\n\n  DADOS DO PAI:  \n") : printf("\n\n  DADOS DA MAE:  \n");

		novoUser = (USER *)malloc(sizeof(USER));

		if (novoUser == NULL) {
			printf("\n\n  Erro na Alocacao da Memoria!  \n\n");
			exit(1);
		} 

		printf("  Numero do bi: "); scanf("%d", &novoUser->bi);

		auxUser = getUserById(novoUser->bi);

		if ( auxUser == NULL ) {

			printf("  Nome: "); scanf(" %s", novoUser->nome); 
			printf("  Senha: "); scanf(" %s", novoUser->senha); 
			printf("  Dt Nasc. (dd/mm/aaaa): "); scanf(" %s", novoUser->dtnasc); 
			printf("  Morada: "); scanf(" %s", novoUser->morada); 
			printf("  Telefone: "); scanf("%d", &novoUser->phone);
			
			( i == 0 ) ? strcpy(novoUser->tipo, "pai") : strcpy(novoUser->tipo, "mae");

			novoUser->filhos[0] = novo->bi;

			if (listaUtilizVazia()) {

				users = novoUser;

			} else {
				
				auxUser = users;
				
				while ( auxUser->prox != NULL ) 
					auxUser = auxUser->prox;

				auxUser -> prox = novoUser;

			}
					
		} else {

			for (int j = 0; j < 5; j++)
				if (auxUser->filhos[j] == 0)			
					auxUser->filhos[j] = novo->bi;


			printf("\n\n  UTILIZADOR COM ESTE BI ENCONTRADO!\n  BEBE ADICIONADO AOS SEUS FILHOS!\n"); 

		}

		novo->parentes[i] = novoUser->bi;
	}

	guardarListaCriancas();
	guardarListaUtiliz();

	system("clear"); printf("\n  CRIANCA REGISTADA COM SUCESSO!  \n"); pause();
}


// funcao que lista todas as criancas /////////////////////////////////////////////////////////////////////////////////////////
void mostrarCriancas(){

	CRIANCA *aux = criancas;

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                          LISTA DE CRIANCAS                           |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if (listaCriancaVazia()) {

		system("clear"); printf("\n  NENHUMA CRIANCA REGISTADA!  \n");

	} else {

		printf("\n  %-6s %-6s %-12s %-6s %-8s %-6s %-6s %-6s %-6s \n", "BI", "Nome", "D.Nasc", 
				"Sexo", "Parto", "T.G.", "P.N.", "A.N.", "PC.N.");

		while ( aux != NULL ){
			// mostrarDadosCrianca(aux);


			printf(" ------------------------------------------------------------------------- \n");
			printf("\n  %-6d %-6s %-12s %-6s %-8s %-6.1f %-6.1f %-6.1f %-6.1f \n", 
				aux->bi , aux->nome, aux->dtnasc, aux->sexo, aux->tipopart, aux->tempgest, aux->pesonasc, 
				aux->altnasc, aux->pcefnasc);
			

			aux = aux -> prox;
		}


		printf("\n\n\n\n  ------------------------------------------------------------------------ \n");
		printf("  Descricao: \n\t*D.Nasc - data de nascimento\n\t*Parto - tipo de parto\n\t*T.G - tempo de gestacao (semanas, dias)\n\t*P.N - peso a nascenca (kg)\n\t*A.N - altura a nascenca (m, cm)\n\t*PC.N - perimetro cefalico a nascenca (cm, mm)");
		printf("\n  ------------------------------------------------------------------------ \n\n\n");
	}

	pause();
}


// funcao que pesquisa uma crianca especifica apartir do seu bi /////////////////////////////////////////////////////////////////////////////////////////
void pesquisarEditarCrianca(int opcao){

	CRIANCA *aux = criancas;
	int bi;

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);

	if ( opcao == 3 ) {
		printf(" |                          PESQUISAR CRIANCA                            |\n");
	} else if ( opcao == 4) {
		printf(" |                           EDITAR CRIANCA                              |\n");
	}

	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if (listaCriancaVazia()) {

		system("clear"); printf("\n  NENHUMA CRIANCA REGISTADA!  \n");

	} else {

		printf("\n\n  BI >> "); scanf("%d", &bi);

		while ( aux != NULL && aux->bi != bi )
			aux = aux -> prox;
		
		if ( aux != NULL ) {

			if ( opcao == 3 ) {
			
				mostrarDadosCrianca(aux);

			} else if (opcao == 4 ) {
				
				printf("\n\n  INTRODUZA OS NOVOS DADOS \n\n");
				aux = preencherC(aux);
				printf("\n\n  DADOS DE %s ATUALIZADO COM SUCESSO!  \n", aux->nome);
				guardarListaCriancas();
			
			}			
		}

		else {
			printf("\n\n  CRIANCA NAO ENCONTRADA! :-( \n");
		}

	}

	pause();
}


// funcao que remove uma crianca apartir do seu bi /////////////////////////////////////////////////////////////////////////////////////////
void removerCrianca(){

	CRIANCA *atual, *anterior;
	int bi, find = 0;


	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                          REMOVER CRIANCA                              |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if (listaCriancaVazia()) {

		system("clear"); printf("\n  NENHUMA CRIANCA REGISTADA!  \n");

	} else {

		printf("\n\n  BI >> "); scanf("%d", &bi);

		// eliminar o primeiro no
		if (criancas -> bi == bi){

			atual = criancas;
			criancas = criancas -> prox;

			for (int i = 0; i < 2; i++)
				deleteUser(atual->parentes[i]);
			
			free(atual);
			find = 1;
		
		} else { // eliminar no meio ou no final da lista

			atual = criancas -> prox;
			anterior = criancas;

			while ( atual != NULL && atual->bi != bi ){
				anterior = atual;
				atual = atual -> prox;
			}

			if (atual != NULL){

				anterior -> prox = atual -> prox;
				

				for (int i = 0; i < 2; i++)
					deleteUser(atual->parentes[i]);

				free(atual);
				find = 1;

			}
		}

		if (find){

			printf("\n\n  CRIANCA REMOVIDO COM SUCESSO!  \n\n");
			guardarListaCriancas();
		
		} else {

			printf("\n\n  CRIANCA NAO ENCONTRADA!  \n\n");

		}
		
	}

	pause();
}


// funcao que retorna uma crianca apartir do bi //////////////////////////////////////////////////////////
CRIANCA* getCriancaById (int bi) {

	CRIANCA *aux;

	for ( aux = criancas; aux != NULL; aux = aux -> prox) 
		if (aux->bi == bi) 
			return aux;


	return NULL;
}


// funcao principal /////////////////////////////////////////////////////////////////////////////////////////
int mainCriancas() {

	int opcao;			// variavel que guarda a opcao escolhida pelo utilizador

	criancas = carregarListaCriancas();	// carregar a lista de criancas armazenadas no ficheiro

	system("clear");

	do {

		opcao = menu("Criancas");		// mostrar menu das criancas e obter a opcao escolhida
		system("clear");

		switch(opcao) {

			case 1:
				registarCrianca();
				break;

			case 2:
				mostrarCriancas();
				break;

			case 3:
				pesquisarEditarCrianca(opcao);
				break;

			case 4:
				pesquisarEditarCrianca(opcao);
				break;

			case 5:
				removerCrianca();
				break;

			case 0:
				// printf("\n  ADEUS E OBRIGADO! A SAIR DO PROGRAMA...\n"); pause();
				break;

			default:
				printf("\n  OPCAO INVALIDA! INTRODUZA UMA OPCAO VALIDA. \n"); pause();
		}

	} while (opcao!=0);

	return 0;
}