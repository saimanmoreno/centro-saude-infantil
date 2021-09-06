#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "criancas.h"

// especificacao dos tipos strings /////////////////////////////////////////////////////////////////////////////////////////
typedef char String[45];


// declaração da lista (struct com campo de dados e ponteiro) /////////////////////////////////////////////////////////////////////////////////////////
typedef struct user {
	int bi;
	String nome;
	String senha;
	String dtnasc;
	String sexo;
	String morada;
	String tipo;
	String espec;
	int phone;
	int filhos[5];
	struct user *prox;  
} USER;


// variaveis globais
USER *users = NULL;	// inicialmente a lista esta vazia /////////////////////////////////////////////////////////////////////////////////////////



// funcao que espera por enter para continuar /////////////////////////////////////////////////////////////////////////////////////////
void pause() {
	printf("  PRESSIONE ENTER PARA CONTINUAR! "); getchar(); getchar();
	system("clear");
}


// funcao que guarda a lista de users num ficheiro txt /////////////////////////////////////////////////////////////////////////////////////////
void guardarListaUtiliz() {

	FILE *file;
	USER *aux;

	file = fopen("base-dados/users.txt", "wb");

	if (file == NULL){
		printf("\n\n  ERRO NO ACESSO AO FICHEIRO! \n\n"); getchar(); getchar();
		exit(1);
	}

	aux = users;

	while (aux!=NULL){

		fwrite(aux, sizeof(USER), 1, file);
		aux = aux -> prox;
	}

	fclose(file);
}


// funcao que le os dados guardaddos no ficheiro e os carregue na lista de criancas /////////////////////////////////////////////////////////////////////////////////////////
USER* carregarListaUtiliz() {

	FILE *file;
	USER *lista=NULL, *atual=NULL, temp, *novo_no;
	int i;

	file = fopen("base-dados/users.txt", "rb");

	if (file == NULL){
		system("clear"); printf("  ERRO NO ACESSO AO FICHEIRO! "); pause();
		exit(1);
	}

	while (fread(&temp, sizeof(USER), 1, file) != 0){

		novo_no = (USER *)malloc(sizeof(USER));

		novo_no->bi = temp.bi;
		strcpy(novo_no->nome, temp.nome);
		strcpy(novo_no->senha, temp.senha);
		strcpy(novo_no->dtnasc, temp.dtnasc);
		strcpy(novo_no->morada, temp.morada);
		strcpy(novo_no->tipo, temp.tipo);
		strcpy(novo_no->espec, temp.espec);
		strcpy(novo_no->sexo, temp.sexo);
		novo_no->phone = temp.phone;

		if (lista == NULL) {
			
			lista = novo_no;
			atual = novo_no;
		
		} else {

			atual->prox = novo_no;
			atual = novo_no;
		}
	}

	novo_no->prox = NULL;

	fclose(file);

	return lista;
}


// funcao que retorna um utilizador apartir do seu bi /////////////////////////////////////////////////////////////////////////////////////////
USER* getUserById (int bi) {

	USER *aux;

	for ( aux = users; aux != NULL; aux = aux -> prox) 
		if (aux->bi == bi) 
			return aux;


	return NULL;
}


// funcao que exibe o menu e retorna a opcao escolhida /////////////////////////////////////////////////////////////////////////////////////////
int menu(char* nome){

	int opcao;
	printf(" %c----------------------------------------------------------------%c\n",201,187);
	printf("                          %s                            \n", nome);
	printf(" %c----------------------------------------------------------------%c\n",200,188);
	printf(" %c---------%c\n",201,187);
	printf(" |   MENU  |\n");
	printf(" %c---------%c\n",200,188);
	printf(" %c----------------------------------------------------------------%c\n",201,187);
	printf(" | <1>  Registar                                                  |\n");
	printf(" |----------------------------------------------------------------|\n");
	printf(" | <2>  Listar                                                    |\n");     
	printf(" |----------------------------------------------------------------|\n");
	printf(" | <3>  Pesquisar                                                 |\n");       
	printf(" |----------------------------------------------------------------|\n");
	printf(" | <4>  Editar                                                    |\n");
	printf(" |----------------------------------------------------------------|\n");
	printf(" | <5>  Remover                                                   |\n");      
	printf(" |----------------------------------------------------------------|\n");
	printf(" |----------------------------------------------------------------|\n");
	printf(" | <0>  Voltar                                                    |\n");
	printf(" %c----------------------------------------------------------------%c\n",200,188);
	printf(" >> "); scanf("%d", &opcao);

	return opcao;
}


// funcao que verifica se a lista esta vazia /////////////////////////////////////////////////////////////////////////////////////////
int listaUtilizVazia() {

	if (users == NULL) {

		system("clear"); printf("\n  NENHUM UTILIZADOR REGISTADO!  \n");
		return 1;
	}
	else 
		return 0;
}


// funcao que recebe memoria alocada e preenche os dados do utilizador /////////////////////////////////////////////////////////////////////////////////////////
USER* preencherU(USER* novo, int update){

	USER *aux;

	printf("  Numero do bi: "); scanf("%d", &novo->bi);

	aux = getUserById(novo->bi);

	if ( aux == NULL || update) {

		printf("  Nome: "); scanf(" %s", novo->nome); 

		if (update) 
			printf("  Senha: "); scanf(" %s", novo->senha); 
		
		printf("  Dt Nasc. (dd/mm/aaaa): "); scanf(" %s", novo->dtnasc); 
		printf("  Sexo: "); scanf(" %s", novo->sexo); 
		printf("  Morada: "); scanf(" %s", novo->morada); 
		printf("  Tipo de Utilizador: "); scanf(" %s", novo->tipo); 
		printf("  Especialidade: "); scanf(" %s", novo->espec); 
		printf("  Telefone: "); scanf("%d", &novo->phone);
		
		return novo;
	
	} else {

		printf("\n\n  UTILIZADOR COM ESTE BI JA EXISTE!\n\n"); pause();

		return NULL;
	}
}


// mostrar dados de um utilizador /////////////////////////////////////////////////////////////////////////////////////////
void showUserData (USER *user){

	CRIANCA *aux;

	printf("\n\n  ------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t\t\t  BI: %d\n", user->bi);
	printf("  Nome: %s\n", user->nome);
	printf("  Data de Nascimento: %s\n", user->dtnasc);
	printf("  Morada: %s\n", user->morada);
	printf("  Genero: %s\n", user->sexo);

	if (strcmp(user->tipo, "pai") == 0 || strcmp(user->tipo, "mae") == 0) {
		
		printf("  Filhos: \n");

		for (int i = 0; i < 5; i++) {

			aux = getCriancaById (user->filhos[i]);

			if (aux!=NULL)
				printf("  %s\n", aux->nome);

		}
	
	} else if (strcmp(user->tipo, "medico") == 0 || strcmp(user->tipo, "enfermeiro") == 0) {

		printf("  Tipo utilizador: %s\n", user->tipo);
		printf("  Especialidade: %s\n", user->espec);
	
	}

	printf("  Telefone: %d\n", user->phone);
	printf("\n  ------------------------------------------------------------------------\n\n");

	// pause();
}


// funcao que adiciona um novo utilizador no final da lista /////////////////////////////////////////////////////////////////////////////////////////
void registarUser(){

	USER *novo, *aux;

	novo = (USER *)malloc(sizeof(USER));

	printf(" %c----------------------------------------------------------------%c\n",201,187);
	printf(" |                       Registar Utilizador                      |\n");
	printf(" %c----------------------------------------------------------------%c\n",200,188);

	if (novo == NULL) {
		printf("\n\n  Erro na Alocacao da Memoria!  \n\n");
		exit(1);
	} 

	novo = preencherU(novo, 0);
		
	if ( novo != NULL ) {

		if (listaUtilizVazia()) {

			users = novo;

		} else {
			
			aux = users;
			while ( aux->prox != NULL ) aux = aux->prox;
			aux -> prox = novo;

		}

		system("clear"); printf("\n  UTILIZADOR REGISTADO COM SUCESSO!  \n"); pause();

		guardarListaUtiliz();
	}
}


// funcao que lista todas os utilizadores /////////////////////////////////////////////////////////////////////////////////////////
void mostrarUtiliz(){

	USER *aux = users;

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                         LISTA DE UTILIZADORES                         |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if ( !listaUtilizVazia() ) {

		printf("\n  %-6s %-6s %-12s %-12s %-6s %-12s %-6s \n", "BI", "Nome", "D.Nasc", 
				"Morada", "Tipo", "Especialidade", "Telefone");

		while ( aux != NULL ){
			// mostrarDadosCrianca(aux);

			if (aux->bi != session) {
				printf(" ------------------------------------------------------------------------- \n");
				printf("\n  %-6d %-6s %-12s %-12s %-6s %-12s %6d \n", 
					aux->bi , aux->nome, aux->dtnasc, aux->morada, aux->tipo, aux->espec, 
					aux->phone);
			}
			

			aux = aux -> prox;
		}

		printf("\n\n\n\n  ------------------------------------------------------------------------ \n");
	
	}

	pause();
}


// funcao que pesquisa um utilizador especifico apartir do seu bi /////////////////////////////////////////////////////////////////////////////////////////
void pesquisarEditarUtiliz(int opcao){

	USER *aux;
	int bi;

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);

	if ( opcao == 3 ) {
		printf(" |                       PESQUISAR UTILIZADOR                        |\n");
	} else if ( opcao == 4) {
		printf(" |                        EDITAR UTILIZADOR                          |\n");
	}

	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if ( !listaUtilizVazia() ) {

		printf("\n\n  BI >> "); scanf("%d", &bi);

		aux = getUserById(bi);
		
		if ( aux != NULL ) {

			if ( opcao == 3 ) {
			
				showUserData(aux);

			} else if (opcao == 4 ) {
				
				printf("\n\n  INTRODUZA OS NOVOS DADOS \n\n");
				aux = preencherU(aux, 1);
				printf("\n\n  DADOS DE '%s' ATUALIZADO COM SUCESSO!  \n", aux->nome);
				guardarListaUtiliz();
			
			}			
		}

		else {
			printf("\n\n  UTILIZADOR NAO ENCONTRADO! :-( \n");
		}

	}

	pause();
}


// funcao que remove um user apartir do seu bi
int deleteUser (int bi) {

	USER *atual, *anterior;
	int find = 0;

	// eliminar o primeiro no
	if (users -> bi == bi){

		atual = users;
		users = users -> prox;
		free(atual);
		find = 1;
	
	} else { // eliminar no meio ou no final da lista

		atual = users -> prox;
		anterior = users;

		while ( atual != NULL && atual->bi != bi ){
			anterior = atual;
			atual = atual -> prox;
		}

		if (atual != NULL){

			anterior -> prox = atual -> prox;
			free(atual);
			find = 1;

		}
	}

	return find;
}


// funcao que solicita um bi e remove o user /////////////////////////////////////////////////////////////////////////////////////////
void removerUser(){

	int bi, find = 0;


	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                          REMOVER UTILIZADOR                            |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if ( !listaUtilizVazia() ) {

		printf("\n\n  BI >> "); scanf("%d", &bi);

		find = deleteUser(bi);

		if (find){

			printf("\n\n  UTILIZADOR REMOVIDO COM SUCESSO!  \n\n");
			guardarListaUtiliz();
		
		} else {

			printf("\n\n  UTILIZADOR NAO ENCONTRADA!  \n\n");

		}
		
	}

	pause();
}


// funcao de login /////////////////////////////////////////////////////////////////////////////////////////
int login(){

	USER *aux;
	int tentativas = 3, bi;
	String senha;
	
	users = carregarListaUtiliz();	// carregar a lista de utilizadores armazenadas no ficheiro

	if (listaUtilizVazia()) 
		registarUser();

	while ( tentativas > 0 ) {

		tentativas--;	
		bi = 0;
		strcpy(senha, "");

		system("clear");
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c-----------%c\n",201,187);
		printf(" |   LOGIN   |\n");
		printf(" %c-----------%c\n",200,188);
		printf("  BI: "); scanf("%d", &bi);
		printf("  Senha: "); scanf("%s", senha);

		aux = getUserById(bi);

		if ( aux != NULL ) {

			if ( strcmp(aux->senha, senha) == 0) {

				session = users->bi;
				printf("\n\n  Bem-vindo '%s'!  \n\n", users->nome); pause();
				return 1;

			} else {

				printf("\n\n  Senha invalida! Tentativas: %d \n\n", tentativas); 
				
			}

		} else {
			
			printf("\n\n  Utilizador nao Encontrado! Tentativas: %d \n\n", tentativas); 

		}

		pause();
	}

	exit(1);		
}


// funcao que altera a senha do utilizador logado
void mudarSenha() {

	USER *aux;
	String senhaAtual, novaSenha, confSenha;

	system("clear");

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                             MUDAR SENHA                               |\n");
	printf(" %c-----------------------------------------------------------------------%c\n\n",200,188);
	printf("\n  Senha Atual: "); scanf("%s", senhaAtual);
	printf("\n  Nova Senha: "); scanf("%s", novaSenha);
	printf("\n  Confirmar Senha: "); scanf("%s", confSenha);

	aux = getUserById(session);

	system("clear");

	if (aux!=NULL && strcmp(senhaAtual, aux->senha) == 0 && strcmp(novaSenha, confSenha) == 0) {

		strcpy(aux->senha, novaSenha);
		printf("  SENHA ALTERADO COM SUCESSO!  \n");
		guardarListaUtiliz();
	
	} else {

		printf("  SENHA ERRADA OU NAO CORRESPONDEM!  \n"); 
	}

	pause();
}


// funcao que atualiza dados do utilizador logado
void editarPerfil() {

	USER *aux;

	system("clear");
	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                           EDITAR PERFIL                               |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	aux = getUserById(session);

	aux = preencherU(aux, 1);

	system("clear");
	printf("  SEUS DADOS FORAM ATUALIZADOS COM SUCESSO!  \n"); pause();

	guardarListaUtiliz();
}


// funcao que apresenta o perfil do utilizador /////////////////////////////////////////////////////////////////////////////////////////
void perfil(){

	USER *aux;
	int opcao;

	do {

		system("clear");
		printf(" %c-----------------------------------------------------------------------%c\n",201,187);
		printf(" |                              MEU PERFIL                               |\n");
		printf(" %c-----------------------------------------------------------------------%c\n",200,188);

		aux = getUserById(session);

		if ( aux != NULL )
			showUserData(aux);


		printf("\n\n");
		printf(" %c-----------------------------------------------------------------------%c\n",201,187);
		printf(" | <1>  Mudar Senha                                                      |\n");
		printf(" |-----------------------------------------------------------------------|\n");
		printf(" | <2>  Editar Meus Dados                                                |\n");     
		printf(" |-----------------------------------------------------------------------|\n");
		printf(" |-----------------------------------------------------------------------|\n");
		printf(" | <0>  Voltar                                                           |\n");
		printf(" %c-----------------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &opcao);

		switch(opcao) {

			case 1:
				mudarSenha();
				break;

			case 2:
				editarPerfil();
				break;

			case 0:
				break;

			default:
				printf("\n  OPCAO INVALIDA! INTRODUZA UMA OPCAO VALIDA. \n"); pause();

		}


	} while(opcao!=0);

	system("clear");
}


// funcao que obtem o tipo de utilizador dado um bi /////////////////////////////////////////////////////////////////////////////////////////
const char* getUserType(int bi){

	while ( users != NULL && users->bi != session )			
		users = users -> prox;

	if ( users != NULL )
		return users->tipo;

	return "sem_cargo";
}


// funcao principal /////////////////////////////////////////////////////////////////////////////////////////
int mainUser() {

	int opcao;			// variavel que guarda a opcao escolhida pelo utilizador

	// users = carregarListaUtiliz();	// carregar a lista de utilizadores armazenadas no ficheiro

	system("clear");

	do {

		opcao = menu("UTILIZADORES");		// mostrar menu daos utilizadores e obter a opcao escolhida
		system("clear");

		switch(opcao) {

			case 1:
				registarUser();
				break;

			case 2:
				mostrarUtiliz();
				break;

			case 3:
				pesquisarEditarUtiliz(opcao);
				break;

			case 4:
				pesquisarEditarUtiliz(opcao);
				break;

			case 5:
				removerUser();
				break;

			case 0:
				//printf("\n  ADEUS E OBRIGADO! A SAIR DO PROGRAMA...\n"); pause();
				break;

			default:
				printf("\n  OPCAO INVALIDA! INTRODUZA UMA OPCAO VALIDA. \n"); pause();
		}

	} while (opcao!=0);

	return 0;
}