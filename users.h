#ifndef USERS_H
#define USERS_H

// especificacao dos tipos strings
typedef char String[45];


// declaração da lista (struct com campo de dados e ponteiro)
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
USER *users;	// inicialmente a lista esta vazia

// prototipos das funcoes
void pause();
void guardarListaUtiliz();
USER* carregarListaUtiliz();
int menu(char* nome);
int listaUtilizVazia();
USER* preencherU(USER* novo, int update);
void showUserData (USER *user);
void registarUser();
void mostrarUtiliz();
void pesquisarEditarUtiliz(int opcao);
void removerUser();
int mainUser();
int login();
void perfil();
const char* getUserType(int bi);
USER* getUserById (int bi);
int deleteUser (int bi);
void mudarSenha();
void editarPerfil();


#endif