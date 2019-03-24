// Llamas Medina Manuel Alonso - 1238187 - 441 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Tnodo GenEspacio();
void PushCola(Tnodo *,Tnodo *,Tnodo *);
Tnodo POPCola(Tnodo *,Tnodo *);
Tnodo POPPila(Tnodo *);
void Servicio(Tnodo);
void genom(Tnodo *);
void PushPila(Tnodo *, Tnodo *);
Tnodo AgregarLista(Tnodo *, Tnodo *);
void Imprimir(Tnodo);
Tnodo Eliminar(Tnodo *,int);

int main(){
	menu();
}

void menu(){
	int op,i=0;
	Tnodo nuevo=NULL;
	Tnodo cabeza=NULL;
	Tnodo ultimo=NULL;
	Tnodo temp=NULL;
	Tnodo pila=NULL;
	Tnodo lista=NULL;
	do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- LEER TEXTO\n");
	printf("2.- LEER CLAVE\n");
	printf("3.- DESCIFRAR TEXTO \n");
	printf("4.- IMPRIMIR MENSAJE \n");
	printf("5.- FINALIZAR PROGRAMA \n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				CLS;
				FILE *CMP;
				CMP=fopen("Importante (2).txt","r");
				while(!feof(CMP)){
					nuevo=GenEspacio();
					fscanf(CMP,"%s",&nuevo->pal);
					nuevo->id=i;
					AgregarLista(&lista,&nuevo);
					i++;
					printf("%s ",nuevo->pal);
				}
				fclose(CMP);
			break;
			case 2:
				CLS;
				CMP=fopen("clave (2).txt","r");
				while(!feof(CMP)){
					nuevo=GenEspacio();
					fscanf(CMP,"%d",&nuevo->id);
					PushCola(&cabeza,&ultimo,&nuevo);
					printf("%d ",ultimo->id);
				}
				fclose(CMP);
				break;
			case 3:
				i=0;
				while(cabeza){
				temp=Eliminar(&lista,cabeza->id);
				nuevo=GenEspacio();
				strcpy(nuevo->pal,temp->pal);
				nuevo->id=temp->id;
				//PushPila(&pila,&nuevo);
				temp=POPCola(&cabeza,&ultimo);
				temp=NULL;
				printf("%s",cabeza->pal);
				}
			break;
			case 4:
				Imprimir(lista);
			break;
			case 5:
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
	}while(op!=5);
}

Tnodo GenEspacio(){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	return temp;
}

void PushCola(Tnodo *cabeza,Tnodo *ultimo,Tnodo *nuevo){
	if(*cabeza){
		(*ultimo)->sig=(*nuevo);
		*ultimo=*nuevo;
		}else{
			*cabeza=*nuevo;
			*ultimo=*nuevo;
		}
	*nuevo=NULL;
}

void PushPila(Tnodo *pila, Tnodo *nuevo){
	(*nuevo)->sig=(*pila);
	*pila=*nuevo;
	*nuevo=NULL; 
}

Tnodo POPCola(Tnodo *cabeza,Tnodo *ultimo){
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
Tnodo POPPila(Tnodo *pila){
	Tnodo temp=NULL;
	if(*pila){
		temp=(*pila);
		*pila=(temp)->sig;
		temp->sig=NULL;
	}
	return temp;
}

Tnodo AgregarLista(Tnodo *lista, Tnodo *nuevo){
	Tnodo temp=NULL;
	if(!*lista || (*nuevo)->id < (*lista)->id){
			(*nuevo)->sig=(*lista);
			*lista=*nuevo;
	}else{
	  	temp=*lista;
	  	while((temp->sig) && (temp->sig)->id <= (*nuevo)->id){
	  		temp=temp->sig;
		}
			if(temp->id != (*nuevo)->id){
				(*nuevo)->sig=temp->sig;
				temp->sig=*nuevo;
				temp=NULL;
				return temp;
			}
			return *nuevo;
		}
}

void Imprimir(Tnodo lista){
	Tnodo temp=NULL;
	temp=lista;
	if(lista){
		while(temp){
		  Servicio(temp);
		  temp=temp->sig;
		}
	}else{
		NADA;
	 }
}
void Servicio(Tnodo temp){
	printf("R: %s \n",temp->pal);
}

Tnodo Eliminar(Tnodo *lista,int X){
	Tnodo temp=NULL, nodo=NULL;
	temp=*lista; 
	nodo=*lista;
	if((*lista)->id==X){
		*lista=(*lista)->sig;
		temp->sig=NULL;			
		return temp;
	}
		while(temp && temp->id<= X){
			if(temp->id==X){				
				nodo->sig=(temp->sig);
				temp->sig=NULL;
				return temp;
			}
		nodo=temp;
		temp=temp->sig;
		}
	return NULL;
}
