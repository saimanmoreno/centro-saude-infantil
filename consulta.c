#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //necessário para usar localtime() e struct tm

#include "users.h"
#include "criancas.h"
#include "main.h"

struct Data {
	int dia, mes, ano, hora, minuto;
};


// declaração da lista (struct com campo de dados e ponteiro) /////////////////////////////////////////////////////////////////////////////////////////
typedef struct consulta {
	int numero;
	String tipo;
	String desc;
	int med_bi;
	int crianc_bi;
	int enf_bi;
	int author;
	struct Data data; 
	struct consulta *prox;  
} CONSULTA;


// variaveis globais
CONSULTA *consultas = NULL;	// inicialmente a lista esta vazia /////////////////////////////////////////////////////////////////////////////////////////



// funcao que guarda a lista de consultas num ficheiro txt /////////////////////////////////////////////////////////////////////////////////////////
void guardarConsulta() {

	FILE *file;
	CONSULTA *aux;

	file = fopen("base-dados/consultas.txt", "wb");

	if (file == NULL){
		printf("\n\n  ERRO NO ACESSO AO FICHEIRO! \n\n"); pause();
		exit(1);
	}

	aux = consultas;

	while (aux!=NULL){

		fwrite(aux, sizeof(CONSULTA), 1, file);
		aux = aux -> prox;
	}

	fclose(file);
}


// funcao que le os dados guardados no ficheiro e os carregue na lista de consultas /////////////////////////////////////////////////////////////////////////////////////////
CONSULTA* carregarConsultas() {

	FILE *file;
	CONSULTA *lista=NULL, *atual=NULL, temp, *novo_no;

	file = fopen("base-dados/consultas.txt", "rb");

	if (file == NULL){
		printf("  ERRO NO ACESSO AO FICHEIRO! "); pause();
		exit(1);
	}

	while (fread(&temp, sizeof(CONSULTA), 1, file) != 0){

		novo_no = (CONSULTA *)malloc(sizeof(CONSULTA));

		novo_no->numero = temp.numero;
		strcpy(novo_no->tipo, temp.tipo);
		strcpy(novo_no->desc, temp.desc);
		novo_no->med_bi = temp.med_bi;
		novo_no->enf_bi = temp.enf_bi;
		novo_no->crianc_bi = temp.crianc_bi;
		novo_no->author = temp.author;
		novo_no->data = temp.data;

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
int nenhumaConsultaMarcada() {

	if (consultas == NULL)
		return 1;
	else
		return 0;
}


// funcao que retorna um novo id para uma nova consulta
int autoGenerateConsultaID() {

	CONSULTA *aux = consultas;

	if (nenhumaConsultaMarcada) return 1;

	else {

		while(aux!=NULL) aux=aux->prox;

		return aux->numero + 1;
	}
}


// funcao que recebe memoria alocada e preenche os dados da nova crianca /////////////////////////////////////////////////////////////////////////////////////////
CONSULTA* preencherConsulta(CONSULTA* novo){

	novo->author = session;
	novo->numero = autoGenerateConsultaID();

	printf("  Tipo de Consulta: "); scanf("%s", novo->tipo); 
	printf("  Descricao da Consulta: "); scanf("%s", novo->desc); 
	printf("  BI da Crianca: "); scanf("%d", &novo->crianc_bi); 
	printf("  BI do Medico(a): "); scanf("%d", &novo->med_bi); 
	printf("  BI do Enfermeiro(a): "); scanf("%d", &novo->enf_bi); 
	printf("  Dia >> "); scanf("%d", &novo->data.dia);
	printf("  Mes >> "); scanf("%d", &novo->data.mes);
	printf("  Hora >> "); scanf("%d", &novo->data.hora);

	novo->data.ano = 2020;

	return novo;
}


// funcao que recebe uma crianca e mostra os seus dados /////////////////////////////////////////////////////////////////////////////////////////
void mostrarConsulta (CONSULTA *consulta){

	CRIANCA *crianca;
	USER *medico, *enfer;

	crianca = getCriancaById(consulta->crianc_bi);
	medico = getUserById(consulta->med_bi);
	enfer = getUserById(consulta->enf_bi);

	printf("\n\n  ------------------------------------------------------------------------\n");
	printf("  \n\t\t\t\t  Numero: %d | Data: %d/%d/%d %d:%d\n", consulta->numero, consulta->data.dia, consulta->data.mes, consulta->data.ano, consulta->data.hora, consulta->data.minuto);
	printf("  Tipo: %s\n", consulta->tipo);
	printf("  Descricao: %s\n", consulta->desc);
	
	if (crianca!=NULL) {
		printf("  Crianca/BI: %s/%d\n", crianca->nome, crianca->bi);
	} 

	if (medico!=NULL) {
		printf("  Medico/BI: %s/%d\n", medico->nome, medico->bi);
	} 

	if (enfer!=NULL) {
		printf("  Enfermeiro/BI: %s/%d\n", enfer->nome, enfer->bi);
	}

	printf("  BI da crianca: %d\n", consulta->crianc_bi);
	printf("  BI da medico: %d\n", consulta->med_bi);
	printf("  BI da Enfermeiro: %d\n", consulta->enf_bi);
	printf("\n  ------------------------------------------------------------------------\n\n");
}


// funcao que marca uma consulta /////////////////////////////////////////////////////////////////////////////////////////
void marcarConsulta(){

	CONSULTA *aux, *novo;

	printf(" %c----------------------------------------------------------------%c\n",201,187);
	printf(" |                        Marcar Consulta                         |\n");
	printf(" %c----------------------------------------------------------------%c\n",200,188);

	novo = (CONSULTA *)malloc(sizeof(CONSULTA));

	if (novo == NULL) {
		printf("\n\n  Erro na Alocacao da Memoria!  \n\n");
		exit(1);
	} 

	novo = preencherConsulta(novo);

	if (nenhumaConsultaMarcada()) {

		consultas = novo;

	} else {
		
		aux = consultas;
	
		while ( aux->prox != NULL ) 
			aux = aux->prox;

		aux -> prox = novo;

	}

	guardarConsulta();


	system("clear"); printf("\n  CRIANCA REGISTADA COM SUCESSO!  \n"); pause();
}


// funcao que lista todas as consultas /////////////////////////////////////////////////////////////////////////////////////////
void listarConsultas(){

	CONSULTA *aux = consultas;

	printf(" %c-----------------------------------------------------------------------%c\n",201,187);
	printf(" |                          LISTA DE CONSULTAS                           |\n");
	printf(" %c-----------------------------------------------------------------------%c\n",200,188);

	if (nenhumaConsultaMarcada()) {

		system("clear"); printf("\n  NENHUMA CONSULTA REGISTADA!  \n");

	} else {

		printf("\n  %-6s %-10s %-14s %-12s \n", "Numero", "Tipo", "Descricao", "Data");

		while ( aux != NULL ) {

			printf(" ------------------------------------------------------------------------- \n");
			printf("\n  %-6d %-10s %-14s %-4d/%-4d/%-4d \n", 
				aux->numero, aux->tipo, aux->desc, aux->data.dia, aux->data.mes, aux->data.ano);
			printf(" ------------------------------------------------------------------------- \n");
			
			aux = aux -> prox;
		}
	}

	pause();
}


int mainConsultas(){	
	
	int opcao, op;

	// consultas = carregarConsultas();

	do {

		printf("  CONSULTAS  \n");
		printf("  1. Marcar consultas\n");
		printf("  2. Listar consultas\n");
		printf("  2. Ver consultas\n");

		printf("  >> "); scanf("%d", &opcao);

		switch(opcao) {

			case 1: 
				marcarConsulta();
				break;

			case 2:
				listarConsultas();
				break;

			case 3:
				printf(" Numero da Consulta >> ");scanf("%d", &op);
				while(consultas!=NULL && consultas->numero!=op) consultas=consultas->prox;

				mostrarConsulta(consultas);

			case 0:
				break;

			default:
				system("clear"); printf("  OPCAO INVALIDA!\n"); pause();

		}
	
	} while(opcao!=0);

	return 0;
}