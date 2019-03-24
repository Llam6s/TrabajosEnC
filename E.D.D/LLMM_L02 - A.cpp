#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct _tdato{
	int dato;
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void menu(void);
Tnodo GenDatos(void);
void Push(Tnodo *pila, Tnodo *nuevo);
Tnodo POP(Tnodo *pila);
void Servicio(Tnodo temp);

int main(){
	menu();
}
void menu(){
	int op;
	Tnodo pila=NULL;
	Tnodo nuevo=NULL;
	Tnodo temp=NULL;
	for(op=0;op<3;op++){
	}
	do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- AGREGA DATO\n");
	printf("2.- IMPRIME DATO\n");
	printf("3.- FINALIZAR PROGRAMA\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				nuevo=GenDatos();
				Push(&pila,&nuevo);
				printf("Dato agregado\n");
				system("pause");
				system("cls");
			break;
			case 2:
				temp=POP(&pila);
				if(temp){
					Servicio(temp);
					free(temp);
					system("cls");
				}else{
					printf("NO HAY VALORES DISPONIBLES!!!\n");
					system("pause");
					system("cls");
					}
				
			break;
		}
	}while(op!=3);
}
Tnodo GenDatos(){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->dato=(1+rand()%100);
}
void Push(Tnodo *pila, Tnodo *nuevo){
	//Tnodo temp=NULL;
	(*nuevo)->sig=(*pila);
	*pila=*nuevo;
	*nuevo=NULL;
}
Tnodo POP(Tnodo *pila){
	Tnodo temp=NULL;
	if(*pila){
		temp=(*pila);
		*pila=(temp)->sig;
		temp->sig=NULL;
	}
	return temp;
}
void Servicio(Tnodo temp){
	system("cls");
	printf("------------------\n");
	printf("DATO ->\t %d\n", temp->dato);
	printf("------------------\n");
	system("pause");
}



