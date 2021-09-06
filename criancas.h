#ifndef CRIANCAS_H
#define CRIANCAS_H


// especificacao dos tipos strings
typedef char String[45];


// declaração da lista (struct com campo de dados e ponteiro)
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
CRIANCA *criancas;	// inicialmente a lista esta vazia


// prototipos das funcoes
void guardarListaCriancas();
CRIANCA* carregarListaCriancas();
int listaCriancaVazia();
CRIANCA* preencherC(CRIANCA* novo);
void mostrarDadosCrianca (CRIANCA *crianca);
void registarCrianca();
void mostrarCriancas();
void pesquisarEditarCrianca(int opcao);
void removerCrianca();
int mainCriancas();
CRIANCA* getCriancaById (int bi);

#endif