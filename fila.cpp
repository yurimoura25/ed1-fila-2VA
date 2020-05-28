#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct node Node;

struct node {
	int pid;
	char nome[25];
	Node *prox;
};


Node *inicioFilaComum;
Node *fimFilaComum;
Node *inicioFilaPref;
Node *fimFilaPref;

Node *alocarNovoNode(int pid, char* nome);


bool filaComumVazia();
bool filaPrefVazia();

int quantidadeProcessosListaComum();
int quantidadeProcessosListaPref();

void criarFilaComum(); //fila comum vazia;
void criarFilaPref(); // fila preferencial vazia;

void inserirComum(int pid, char* nome);
void inserirPref(int pid, char* nome);	
void removerFilaComum();
void removerFilaPref();
void imprimirFilaComum();
void imprimirFilaPref();

//funcionamento
void cadastrarProcesso();
void executarProcesso();
void finalizarProcesso();
void listarProcessos();




int main() {
	setlocale(LC_ALL, "Portuguese");
	criarFilaComum();
	criarFilaPref();
	char nome[25];
	int pid, opcao;
	do {
		system("cls");
		printf("Quantidade de processos na fila comum: %i\n",quantidadeProcessosListaComum());
		printf("Quantidade de processos na fila preferencial: %i\n",quantidadeProcessosListaPref());
		printf("\n\t 1 - Inserir processo.");
		printf("\n\t 2 - para executar um processo");
		printf("\n\t 3 - para finalizar um processo");
		printf("\n\t 4 - Listagem de todos os processos em ambas as filas!");
		printf("\n\t 0 - Sair\n\t");
		scanf("%d", &opcao);
		switch(opcao) {
			case 0:
				break;
				
			case 1:
				cadastrarProcesso();
				break;
				
			case 2:
				executarProcesso();
				break;
				
			case 3:
				finalizarProcesso();
				break;
				
			case 4:
				system("cls");
				listarProcessos();
				system("pause");
				break;
			default: break;
		}
	}while(opcao != 0);

	
	
}

bool filaComumVazia() {
	if(inicioFilaComum==NULL) {
		return true;
	} else {
		return false;
	}
}

bool filaPrefVazia() {
	if(inicioFilaPref == NULL) {
		return true;
	} else {
		return false;
	}
}

int quantidadeProcessosListaComum() {
	Node *verificador= inicioFilaComum;
	int cont=0;
	while(verificador!=NULL) {
		cont++;
		verificador= verificador->prox;
	}
	return cont;
}

int quantidadeProcessosListaPref() {
	Node *verificador= inicioFilaPref;
	int cont=0;
	while(verificador!=NULL) {
		cont++;
		verificador= verificador->prox;
	}
	return cont;
}

void cadastrarProcesso() {
	int pid;
	char nome[25];
	int pref;
	printf("\n\tDigite o PID do processo: ");
	scanf("%i", &pid);
	printf("Informe o nome do processo: ");
	scanf("%s", &nome);
	printf("\n\tEsse processo esta na fila preferencial?");
	printf("\n\t1 . SIM");
	printf("\n\t0 . NÃO");
	scanf("%i", &pref);
	if(pref == 1) {
		inserirPref(pid, nome);
	} else if(pref == 0) {
		inserirComum(pid, nome);
	}
}

void executarProcesso() {
	Node *walker;
	if(!filaPrefVazia() && !filaComumVazia()) {
		walker = inicioFilaPref;
		inicioFilaPref = inicioFilaPref->prox;
		walker->prox = NULL;
		fimFilaComum->prox = walker;
		fimFilaComum = fimFilaComum->prox;
		
	} else if(filaPrefVazia() && !filaComumVazia()){
		walker = inicioFilaComum;
		inicioFilaComum = inicioFilaComum->prox;
		walker->prox = NULL;
		fimFilaComum->prox = walker;
		fimFilaComum = walker;
	} else if(filaComumVazia() && filaPrefVazia()) {
		printf("Não existem processos inseridos em nenhuma das filas!");
	} else if(!filaPrefVazia() && filaComumVazia()) {
		walker = inicioFilaPref;
		inicioFilaPref = inicioFilaPref->prox;
		walker->prox = NULL;
		inicioFilaComum = walker;
		fimFilaComum = walker;
	}
}

void finalizarProcesso() {
	Node *walker;
	if(inicioFilaPref!=NULL) {
		walker = inicioFilaPref;
		inicioFilaPref= inicioFilaPref->prox;
		free(walker);
	} else {
		walker = inicioFilaComum;
		inicioFilaComum = inicioFilaComum->prox;
		free(walker);
	}
	
}

void listras(int qntListras) {
	for(int i = 1; i<=qntListras; i ++) {
		printf("|");
	}
}
void listarProcessos() {
	listras(25);
	printf(" FILA COMUM ");
	listras(25);
	printf("\n");
	imprimirFilaComum();
	printf("\n\n\n");
	listras(25);
	printf(" FILA PREFERENCIAL ");
	listras(25);
	imprimirFilaPref();
}


void criarFilaComum() {
	inicioFilaComum = NULL;
	fimFilaComum = NULL;
}

void criarFilaPref() {
	inicioFilaPref = NULL;
	fimFilaPref = NULL;
}

void inserirComum(int pid, char* nome) {
	if(filaComumVazia()) {
		Node *novo = alocarNovoNode(pid, nome);
		novo->pid = pid;
		strcpy(novo->nome, nome);
		novo->prox = NULL;
		inicioFilaComum = novo;
		fimFilaComum = novo;
	} else {
		Node *novo = alocarNovoNode(pid,nome);
		Node *walker = inicioFilaComum;
		novo->pid = pid;
		strcpy(novo->nome, nome);
		while(walker->prox!=NULL) {
			walker = walker->prox;
		}
		fimFilaComum = novo;
		walker->prox = novo;
		novo->prox = NULL;
		
	}
}

void removerFilaComum() {
	Node *aux = inicioFilaComum;
	inicioFilaComum = inicioFilaComum->prox;
	free(aux);
}

void inserirPref(int pid, char* nome) {
	if(filaPrefVazia()) {
		Node *novo = alocarNovoNode(pid,nome);
		novo->pid = pid;
		strcpy(novo->nome, nome);
		novo->prox = NULL;
		inicioFilaPref = novo;
		fimFilaPref = novo;
	} else {
		Node *novo = alocarNovoNode(pid, nome);
		Node *walker = inicioFilaPref;
		novo->pid = pid;
		strcpy(novo->nome, nome);
		while(walker->prox != NULL) {
			walker = walker->prox;
		}
		fimFilaPref = novo;
		walker->prox = novo;
		novo->prox = NULL;
	}
}

void removerFilaPref() {
	Node *aux = inicioFilaPref;
	inicioFilaPref = inicioFilaPref->prox;
	free(aux);
}

void imprimirFilaComum() {
	Node *walker = inicioFilaComum;
	while(walker!=NULL) {
		printf("\nPID: %i\tNome %s\n", walker->pid, walker->nome);
		walker = walker->prox;
	}
}
void imprimirFilaPref() {
	Node *walker = inicioFilaPref;
	while(walker!=NULL) {
		printf("\nPID: %i\tNome %s\n", walker->pid, walker->nome);
		walker = walker->prox;
	}
}

Node *alocarNovoNode(int pid, char* nome) {
	Node *novo = new Node;
	novo->pid = pid;
	strcpy(novo->nome, nome);
	novo->prox = NULL;
	return novo;
}
