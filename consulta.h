#ifndef CONSULTAS
#define CONSULTAS

struct Data {
	int dia, mes, ano, hora, minuto;
};


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
CONSULTA *consultas;

void guardarConsulta();

CONSULTA* carregarConsultas();

int nenhumaConsultaMarcada();

int autoGenerateConsultaID();

CONSULTA* preencherConsulta(CONSULTA* novo);

void mostrarConsulta (CONSULTA *consulta);

void marcarConsulta();

void listarConsultas();

int mainConsultas();

#endif