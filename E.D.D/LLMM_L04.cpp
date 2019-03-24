// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en listas que agrege, elimine, busque e imprima una fila de nodos.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdato{
	int dato;
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void menu(void);
Tnodo GenDatos();
Tnodo Agregar(Tnodo *,Tnodo *);
void Imprimir(Tnodo );
void Servicio(Tnodo *);
Tnodo Buscar(Tnodo *,int );
Tnodo Eliminar(Tnodo *,int);
Tnodo Salir(Tnodo *);
int main(){
	srand(time(NULL));
	menu();
}
void menu(){
	int op, X;
	Tnodo nuevo=NULL;
	Tnodo lista=NULL;
	Tnodo temp=NULL;
	do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- AGREGAR\n");
	printf("2.- ELIMINAR\n");
	printf("3.- BUSCAR\n");
	printf("4.- IMPRIMIR\n");
	printf("5.- SALIR\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
	CLS;
		switch(op){
			case 1:
				for(int i=0;i<53;i++){
				nuevo=GenDatos();
				Agregar(&lista,&nuevo);
			}
			break;
			case 2:
				if(lista){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Eliminar(&lista,X);
					if(temp){
						printf("REGISTRO %d ELIMINADO\n", temp->dato);
						temp=NULL;
						free(temp);
					}else{
						printf("NO EXISTE REGISTRO A ELMINAR\n");
					 }
				}else{
					NADA;
				 }
			break;
			case 3:
				if(lista){
					printf("REGISTRO A BUSCAR: ");
					scanf("%d",&X);
					temp=Buscar(&lista, X);
					if(temp){
						Servicio(&temp);
					}else{
						printf("REGISTRO NO ENCONTRADO\n");
					 }
				}else{
					NADA;
				 }
			break;
			case 4:
				Imprimir(lista);
			break;
			case 5:
				while(lista){
					printf("ELIMINANDO REGISTROS...\n");
					temp=Salir(&lista);
					printf("REGISTRO ELIMINADO: %d\n", temp->dato);
					free(temp);
					PAUSA;
					CLS;
				}
				NADA;
			break;
			default:
			printf("OPCION INVALIDA\n");
			break;
		}
		PAUSA;
		CLS;
	}while(op!=5);
}

Tnodo GenDatos(){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->dato=(1+rand()%53);
	printf("REGISTRO AGREGADO: %d\n",temp->dato);
	return temp;
}

Tnodo Agregar(Tnodo *lista, Tnodo *nuevo){
	Tnodo temp=NULL;
	if(!*lista || (*nuevo)->dato < (*lista)->dato){
			(*nuevo)->sig=(*lista);
			*lista=*nuevo;
	}
		else{
		  	temp=*lista;
		  	while((temp->sig) && (temp->sig)->dato <= (*nuevo)->dato){
		  		temp=temp->sig;
			}
				if(temp->dato != (*nuevo)->dato){
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
		  Servicio(&temp);
		  temp=temp->sig;
		}
	}else{
		NADA;
	 }
}

void Servicio(Tnodo *temp){
	printf("R: %d \n",(*temp)->dato);
}

Tnodo Buscar(Tnodo *lista, int X){
	Tnodo temp=NULL, nodo=NULL;
	temp=*lista;
	while(temp->dato <=X){
		if(temp->dato==X){
			return temp;
		}
		temp=temp->sig;
	}
	return nodo;
}

Tnodo Eliminar(Tnodo *lista,int X){
	Tnodo temp=NULL, nodo=NULL;
	temp=*lista; //Se declaran 2 variables igualadas a lista
	nodo=*lista; //una que se mueva detras de otra
	if((*lista)->dato==X){
		*lista=(*lista)->sig;	//En dado caso de que la variable a eliminar sea el primer nodo
		temp->sig=NULL;			//la lista se recorre al siguiente nodo
		return temp;
	}
		while(temp && temp->dato<= X){	//Mientras haya algo que evaluar o comparar con la variable a eliminar el while funcionara
			if(temp->dato==X){			
				nodo->sig=(temp->sig);	//Si se encuentra el valor a eliminar, nodo toma el "nodo" que esta ubicado frente a temporal
				temp->sig=NULL;
				return temp;
			}
		nodo=temp;				//Si el numero no se ha encontrado, nodo se iguala a la variable temporal
		temp=temp->sig;			//y temporal recorre la fila
		}
	return NULL;
}

Tnodo Salir(Tnodo *lista){
	Tnodo temp;					//Se recorre el nodo lista de 1 en 1 eliminando registos hasta finalizar la fila
	temp=*lista;
	*lista=(*lista)->sig;
	temp->sig=NULL;
	return temp;
}
