#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PAUSA system("pause")
#define NADA printf("Ausencia de Datos\n")
#define CLS system("cls")
typedef struct _tdato{
	int dato;
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void menu(void);
Tnodo GenDatos();
void Push(Tnodo *,Tnodo *,Tnodo *);
Tnodo POP(Tnodo *,Tnodo *);
void Servicio(Tnodo temp);


int main(){
	srand(time(NULL));
	menu();
}
void menu(){
	int op;
	Tnodo nuevo=NULL;
	Tnodo cabeza=NULL;
	Tnodo ultimo=NULL;
	Tnodo temp=NULL;
	do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- AGREGA DATO\n");
	printf("2.- IMPRIME DATO\n");
	printf("3.- FINALIZAR PROGRAMA \n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				nuevo=GenDatos();
				Push(&cabeza,&ultimo,&nuevo);
			break;
			case 2:
				temp=POP(&cabeza,&ultimo);
				if(temp){
					Servicio(temp);
					free(temp);
					}else{
						NADA;
						}
			break;
			case 3:
				printf("Finalizando Programa...\n");
			break;
			default:
			printf("OPCION INVALIDA\n");
			break;
		}
		PAUSA;
		CLS;
	}while(op!=3);
}
Tnodo GenDatos(){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->dato=(1+rand()%100);
	printf("%d\n",temp->dato);
	return temp;
}
void Push(Tnodo *cabeza,Tnodo *ultimo,Tnodo *nuevo){
	if(*cabeza){
		(*ultimo)->sig=(*nuevo);
		*ultimo=*nuevo;
		}else{
			*cabeza=*nuevo;
			*ultimo=*nuevo;
		}
	*nuevo=NULL;
}
Tnodo POP(Tnodo *cabeza,Tnodo *ultimo){
	Tnodo temp=NULL;
	if(*cabeza){
		if(*cabeza==*ultimo){
			temp=*ultimo;
			*cabeza=NULL;
			*ultimo=NULL;
		}else{
			temp=*cabeza;
			*cabeza=(temp)->sig;
			temp->sig=NULL;
		}
	}
	return temp;
}

void Servicio(Tnodo temp){
	printf("\t %d \n", temp->dato);
}
