// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en Lista Dobles Circulares que agrege, elimine, busque e imprima una Lista circular de nodos, tambien que un inciso "Salir"
// en el cual se eliminen todos los registros o nodos existentes con datos simples (numeros)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdatoD{
	int dato;
	struct _tdatoD *sig;	//Se agregan el puntero recursivo ant, debido a que es una de las caracteristicas
	struct _tdatoD *ant;	//de las listas dobles
} TdatoD;

typedef TdatoD *Tnodo;

void menu(void);
Tnodo GenDatos();
Tnodo Agregar(Tnodo *,Tnodo *);
void Imprimir(Tnodo);
void Servicio(Tnodo );
Tnodo Buscar(Tnodo ,int );
Tnodo Eliminar(Tnodo *,int);
Tnodo Salir(Tnodo *);

int main(){
	srand(time(NULL));
	menu();
}

void menu(){
	int op, X, sn;
	Tnodo nuevo=NULL;
	Tnodo listaDC=NULL;
	Tnodo temp=NULL;
	Tnodo ultimo=NULL;
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
				nuevo=GenDatos();
				temp=Agregar(&listaDC,&nuevo);
				if(temp){
					printf("NO SE PUDO AGREGAR EL REGISTRO : %d\n---------REGISTRO REPETIDO---------\n", nuevo->dato);
					free(temp);
				}
			break;
			case 2:
				if(listaDC){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Buscar(listaDC,X);
					if(temp){
						printf("SEGURO QUE DESEAS ELIMINAR EL REGISTRO: %d\n", temp->dato);
						printf("Si - [1]\nNo - [2]\nSELECCIONA UNA OPCION: ");
						scanf("%d",&sn);
						switch(sn){
							case 1:
								printf("REGISTRO ELIMINADO: %d\n",temp->dato);
								temp=Eliminar(&listaDC,X);
								temp=NULL;
								free(temp);
							break;
							case 2:
							printf("REGRESANDO REGISTRO A LA LISTA......\n");
							Agregar(&listaDC,&temp);
							break;
						}
					}else{
						printf("NO EXISTE REGISTRO A ELMINAR\n");
					 }
				}else{
					NADA;
				 }
			break;
			case 3:
				if(listaDC){
					printf("REGISTRO A BUSCAR: ");
					scanf("%d",&X);
					temp=Buscar(listaDC,X); 			
					if(temp){
						Servicio(temp);			
					}else{
						printf("REGISTRO NO ENCONTRADO\n");
					 }
				}else{
					NADA;
				 }
			break;
			case 4:
				if(listaDC){
				Imprimir(listaDC); 						
				}else{											
					NADA;
				}
			break;
			case 5:
				temp=listaDC;
				while(listaDC){
					printf("ELIMINANDO REGISTROS...\n");
					temp=Salir(&listaDC);				
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
	temp=(Tnodo)malloc(sizeof(TdatoD));
	temp->sig=NULL;
	temp->ant=NULL;
	temp->dato=(1+rand()%100);
	printf("REGISTRO AGREGADO: %d\n",temp->dato);
	return temp;
}
Tnodo Agregar(Tnodo *listaDC, Tnodo *nuevo){
	Tnodo temp=NULL;
	Tnodo nodo=NULL;
	if(!*listaDC){
			*listaDC=*nuevo;					//
			(*listaDC)->sig=*listaDC;			//	Agrega un nodo a la lista vacia
			(*listaDC)->ant=*listaDC;			//
			return nodo;						//
		}else{
			if((*nuevo)->dato < (*listaDC)->dato){		//
				(*nuevo)->sig=*listaDC;					//
				(*nuevo)->ant=(*listaDC)->ant;			//
				((*listaDC)->ant)->sig=*nuevo;			//	Si el nodo a agregar contiene un dato menor al nodo inicial...
				(*listaDC)->ant=*nuevo;					//
				*listaDC=*nuevo;						//
				return nodo;							//
				}else{
					temp=*listaDC;															//
					while(temp->sig!=*listaDC && (temp->sig)->dato<=(*nuevo)->dato){		//		Se recorre la lista con "temp" hasta encontrar la posicion del nodo a agregar...
						temp=temp->sig;														//
						}																	//----------------------------------------------------------------------------
					if(temp->dato==(*nuevo)->dato){											//
						return *nuevo;														//		Si el dato del nodo a agregar esta repetido, se retorna nodo.
						}else{																//-----------------------------------------------------------------------------		
							if(temp->sig==*listaDC){										//
								(*nuevo)->sig=*listaDC;										//		
								(*nuevo)->ant=((*listaDC)->ant);							//
								((*listaDC)->ant)->sig=*nuevo;								//		Si "temp" se detuvo al final de la lista....
								(*listaDC)->ant=*nuevo;										//
								return nodo;												//
							}																//
						}																	//------------------------------------------------------------------------------
						(*nuevo)->sig=temp->sig;											//
						(*nuevo)->ant=temp;													//
						(temp->sig)->ant=*nuevo;											//		Si el dato del nodo a agregar se encuentra entre dos nodos...
						temp->sig=*nuevo;													//
						return nodo;														//
					}																		//
				}																			//
}																							//
void Imprimir(Tnodo listaDC){
	Tnodo temp=listaDC;
		while(temp->sig!=listaDC){
				Servicio(temp);
				temp=temp->sig;
		}
		Servicio(temp);
}
void Servicio(Tnodo temp){
	printf("R: %d \n",(temp)->dato);
}
Tnodo Buscar(Tnodo listaDC,int X){
	Tnodo temp=NULL, nodo=NULL;
	int Comienzo;
		if(listaDC->dato==X){
			temp=listaDC;
			return temp;
		}
		Comienzo=ceil(((listaDC->ant)->dato-listaDC->dato)/2);
		if(X>=Comienzo){
			temp=(listaDC->ant);
			while(temp!=listaDC && temp->dato >= X){
					if(temp->dato==X){
						return temp;
					}
				temp=temp->ant;
				}
			}else{
				temp=listaDC;
				while(temp->sig!=listaDC && temp->dato <= X){
					if(temp->dato==X){
						return temp;
					}
				temp=temp->sig;
				}
			}
		return nodo;
}
Tnodo Eliminar(Tnodo *listaDC, int X){
	Tnodo temp=NULL, nodo=NULL;
	if((*listaDC)->dato==X){
		temp=(*listaDC);
		if((*listaDC)->sig==(*listaDC)){	//
			(*listaDC)->ant=NULL;			// unico nodo en la lista
			(*listaDC)->sig=NULL;			//
			(*listaDC)=NULL;				//
			return temp;					//
		}else{
			if((temp->sig)->sig==*listaDC){		 			//
					(*listaDC)->sig->sig=temp->sig;			//
					((*listaDC)->ant)->ant=temp->ant;		// 	 primer nodo a eliminar - lista con 2 datos
					*listaDC=temp->sig;						// 	???????????????????????????????
					temp->sig=NULL;							//
					temp->ant=NULL;							//
					return temp;							//
			}
		*listaDC=(temp->sig);							//
		(*listaDC)->ant=temp->ant;						//
		(temp->ant)->sig=*listaDC;						//
		temp->sig=NULL;									//	primer nodo de la lista a eliminar - lista con datos
		temp->ant=NULL;									//
		return temp;									//
	
		}
	}else{
		if(((*listaDC)->ant)->dato==X){								// 		Si el ultimo nodo de la lista es el que se eliminará se hacen las siguientes preguntas:
			temp=((*listaDC)->ant);									//
				if(((*listaDC)->sig)->dato==X){						//		- Si el nodo a eliminar es el ultimo nodo de la lista, pero esta solo contiene 2 nodos.
					(*listaDC)->sig=temp->sig;						//
					(*listaDC)->ant=temp->ant;						//		
					temp->ant=NULL;									//
					temp->sig=NULL;									//									???????????????????????????
					return temp;									//
				}													//	-------------------------------------------------------------------------------------------------------------------
			(temp->ant)->sig=*listaDC;								//		
			(*listaDC)->ant=temp->ant;								//		- Si la lista contiene mas de 2 nodos y el ultimo nodo es el que se eliminara...
			temp->sig=NULL;											//
			temp->sig=NULL;											//
			return temp;											//
		}															//	--------------------------------------------------------------------------------------------------------------------
		temp=*listaDC;												//	En dado caso de que el ultimo nodo de la lista no sea el que se va a eliminar, la lista se recorre de manera normal
		while(temp->sig!=(*listaDC)->ant && (temp->sig)->dato<=X){	//	Hasta encontrar el dato a eliminar...
			if((temp->sig)->dato==X){								//	
				temp=temp->sig;										//	
				(temp->ant)->sig=temp->sig;							//	Si se encuentra que "(temp->sig)->dato" es el nodo que contiene el valor a eliminar, la lista se detiene en "temp" 
				(temp->sig)->ant=temp->ant;							//	
				temp->sig=NULL;										//	
				temp->ant=NULL;										//	
				return temp;										//	
			}														//	----------------------------------------------------------------------------------------------------------------------	
			temp=temp->sig;											//	La lista avanza en dado caso de que "(temp->sig)->dato" no sea el nodo a eliminar.
		}															//	----------------------------------------------------------------------------------------------------------------------
		return nodo;												//	?????????????????????????????????????????????????
	}																//	--------------------------------------------------------------------------------------------------------------------
}																	//	
Tnodo Salir(Tnodo *listaDC){
	Tnodo temp=*listaDC;
	if(temp->sig==*listaDC){
		(*listaDC)->sig=NULL;
		(*listaDC)->ant=NULL;
		(*listaDC)=NULL;
		return temp;
	}
		(*listaDC)=(*listaDC)->sig;
		(*listaDC)->ant=temp->ant;
		(temp->ant)->sig=*listaDC;
		temp->sig=NULL;
		temp->ant=NULL;
		return temp;
}
