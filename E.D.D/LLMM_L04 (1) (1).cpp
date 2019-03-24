// Llamas Medina Manuel Alonso - 1238187 - 441 

#include <stdio.h>
#include <stdlib.h>
#include <string>


#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdato{
	int id;
	char pal[30];
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void menu(void);
Tnodo GenDatos();
void Push(Tnodo *,Tnodo *,Tnodo *);
Tnodo POP(Tnodo *,Tnodo *);
void Servicio(Tnodo temp);
void genom(Tnodo *);

int main(){
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
	printf("1.- LEER TEXTO\n");
	printf("2.- IMPRIMIR CADENA\n");
	printf("3.- FINALIZAR PROGRAMA \n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				CLS;
				FILE *CMP;
				CMP=fopen("importante.txt","r");
				while(!feof(CMP)){
					nuevo=GenDatos();
					fscanf(CMP,"%s",&nuevo->pal);
					Push(&cabeza,&ultimo,&nuevo);
				}
			break;
			case 2:
				CLS;
				temp=POP(&cabeza,&ultimo);
				if(temp){
					Servicio(temp);
					}else{
						NADA;
						}
			break;
			case 3:
				if(cabeza){
				do{
						CLS;
						temp=cabeza;
						cabeza=(temp)->sig;
						printf("\tELIMINANDO REGISTROS..\n");
						temp->sig=NULL;
						PAUSA;
						CLS;
					}while(cabeza);
				}else{
						CLS;
						printf("NO HAY REGISTROS...\n");
							}
					
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
	int i;
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->id=i;
	i++;
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

}
