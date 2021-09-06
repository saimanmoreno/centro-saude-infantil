#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //necessário para usar localtime() e struct tm

#include "main.h"
#include "users.h"
#include "criancas.h"
#include "consulta.h"

int session;
struct tm* data_hora_atual;


struct tm* current_timestamp() {

  //ponteiro para struct que armazena data e hora  
  struct tm *data_hora_atual;     

  //variável do tipo time_t para armazenar o tempo em segundos  
  time_t segundos;

  //obtendo o tempo em segundos  
  time(&segundos);   

  //para converter de segundos para o tempo local  
  //utilizamos a função localtime  
  data_hora_atual = localtime(&segundos);  

  return data_hora_atual;
}


void adminMenu(){

	int op;

	do {

		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c---------%c\n",201,187);
		printf(" |   MENU  |\n");
		printf(" %c---------%c\n",200,188);
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" | <1>  Gerir Utilizadores                                        |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <2>  Gerir Criancas                                            |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <3>  Gerir Consultas                                           |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <4>  Meu Perfil                                                |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <9>  Logout                                                    |\n"); 
		printf(" |----------------------------------------------------------------|\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <0>  Sair                                                      |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &op);

		system("clear");

		switch(op){
			case 1:
				mainUser();
				break;

			case 2:
				mainCriancas();
				break;

			case 3:
				mainConsultas();
				break;

			case 4:
				perfil();
				break;

			case 9:
				printf("\n  SESSAO ENCERADA! \n\n"); pause();
				main();
				break;

			case 0: 
				printf("\n  ADEUS E OBRIGADO! \n\n"); pause();
				break;

			default:
				printf("\n  OPCAO INVALIDA!  \n\n"); pause();
		}

	}while(op!=0);
}


void medMenu(){


	int op;

	do {

		system("clear");
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c---------%c\n",201,187);
		printf(" |   MENU  |\n");
		printf(" %c---------%c\n",200,188);
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" | <1>  Consultar                                                 |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <2>  Marcar Consultas                                          |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <3>  Historico de Consultas                                    |\n");    
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <4>  Meus Pacientes                                            |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <5>  Meu Perfil                                                |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <9>  Logout                                                    |\n"); 
		printf(" |----------------------------------------------------------------|\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <0>  Sair                                                      |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &op);
		system("clear");

		switch(op){
			case 1:
				// usersMain();
				break;

			case 2:
				// childrenMain();
				break;

			case 3:
				// consultaMain();
				break;

			case 5:
				perfil();
				break;

			case 9:
				printf("\n  SESSAO ENCERADA! \n\n"); pause();
				main();
				break;

			case 0: 
				printf("\n  ADEUS E OBRIGADO! \n\n"); pause();
				break;

			default:
				printf("\n  OPCAO INVALIDA!  \n\n"); pause();
		}

	}while(op!=0);
}


void enfMenu(){


	int op;

	do {

		system("clear");
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c---------%c\n",201,187);
		printf(" |   MENU  |\n");
		printf(" %c---------%c\n",200,188);
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" | <1>  Consultar                                                 |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <2>  Marcar Consultas                                          |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <3>  Historico de Consultas                                    |\n");    
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <4>  Meus Pacientes                                            |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <5>  Meu Perfil                                                |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <9>  Logout                                                    |\n"); 
		printf(" |----------------------------------------------------------------|\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <0>  Sair                                                      |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &op);
		system("clear");

		switch(op){
			case 1:
				// usersMain();
				break;

			case 2:
				// childrenMain();
				break;

			case 3:
				// consultaMain();
				break;

			case 5:
				perfil();
				break;

			case 9:
				printf("\n  SESSAO ENCERADA! \n\n"); pause();
				main();
				break;

			case 0: 
				printf("\n  ADEUS E OBRIGADO! \n\n"); pause();
				system("clear");
				break;

			default:
				printf("\n  OPCAO INVALIDA!  \n\n"); pause();
		}

	}while(op!=0);
}


void recMenu(){


	int op;

	do {

		system("clear");
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c---------%c\n",201,187);
		printf(" |   MENU  |\n");
		printf(" %c---------%c\n",200,188);
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" | <2>  Marcar Consultas                                          |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <3>  Lista de Espera                                           |\n");    
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <4>  Pesquisar                                                 |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <5>  Meu Perfil                                                |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <9>  Logout                                                    |\n"); 
		printf(" |----------------------------------------------------------------|\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <0>  Sair                                                      |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &op);

		system("clear");

		switch(op){
			case 1:
				// usersMain();
				break;

			case 2:
				// childrenMain();
				break;

			case 3:
				// consultaMain();
				break;

			case 5:
				perfil();
				break;

			case 9:
				printf("\n  SESSAO ENCERADA! \n\n"); pause();
				main();
				break;

			case 0: 
				printf("\n  ADEUS E OBRIGADO! \n\n"); pause();
				system("clear");
				break;

			default:
				printf("\n  OPCAO INVALIDA!  \n\n"); pause();
		}

	}while(op!=0);
}


void parentsMenu(){


	int op;

	do {

		system("clear");
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" |      SISTEMA DE GESTAO DE CENTROS DE SAUDE MATERNO INFANTIL    |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" %c---------%c\n",201,187);
		printf(" |   MENU  |\n");
		printf(" %c---------%c\n",200,188);
		printf(" %c----------------------------------------------------------------%c\n",201,187);
		printf(" | <1>  Minhas Consultas                                          |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <2>  Marcar Consultas                                          |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <3>  Historico de Consultas                                    |\n");    
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <4>  Meu(s) Filho(s)                                           |\n");   
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <5>  Meu Perfil                                                |\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <9>  Logout                                                    |\n"); 
		printf(" |----------------------------------------------------------------|\n");
		printf(" |----------------------------------------------------------------|\n");
		printf(" | <0>  Sair                                                      |\n");
		printf(" %c----------------------------------------------------------------%c\n",200,188);
		printf(" >> "); scanf("%d", &op);

		system("clear");

		switch(op){
			case 1:
				// usersMain();
				break;

			case 2:
				// childrenMain();
				break;

			case 3:
				// consultaMain();
				break;

			case 5:
				perfil();
				break;

			case 9:
				session = 0;
				printf("\n  SESSAO ENCERADA! \n\n"); pause();
				main();
				break;

			case 0: 
				printf("\n  ADEUS E OBRIGADO! \n\n"); pause();
				system("clear");
				break;

			case 999:
				mainUser();
				system("clear");
				break;

			default:
				printf("\n  OPCAO INVALIDA!  \n\n"); pause();
		}

	}while(op!=0);
}


int main(){
	
	String tipo;
	session = 0;
	data_hora_atual = current_timestamp();

	system("clear");	// limpar o terminal antes de abrir o programa

	if (login()){
		
		strcpy(tipo, getUserType(session));

		if (strcmp(tipo, "medico") == 0)
			medMenu();
		
		else if (strcmp(tipo, "enfermeiro") == 0)
			enfMenu();
		
		else if (strcmp(tipo, "recepcionista") == 0)
			recMenu();
		
		else if (strcmp(tipo, "admin") == 0)
			adminMenu();
		
		else 
			parentsMenu();
		
	}

	return 0;
}
