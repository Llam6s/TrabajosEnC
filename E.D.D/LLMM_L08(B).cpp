// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en Lista Dobles Circulares que agrege, elimine, busque e imprima una Lista circular de nodos, tambien que un inciso "Salir"
// en el cual se eliminen todos los registros o nodos existentes con datos de alumno.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdatoD{
	int matricula;
	char N[20];
	char AP[20];
	char AM[20];
	char sexo[2];
	int E;
	struct _tdatoD *sig;	//Se agregan el puntero recursivo ant, debido a que es una de las caracteristicas
	struct _tdatoD *ant;	//de las listas dobles
} TdatoD;

typedef TdatoD *Tnodo;

void menu(void);
Tnodo GenDatos();
void genom(Tnodo *);
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
					printf("NO SE PUDO AGREGAR EL REGISTRO : \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n---------REGISTRO REPETIDO---------\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
					free(temp);
				}
			break;
			case 2:
				if(listaDC){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Buscar(listaDC,X);
					if(temp){
						printf("SEGURO QUE DESEAS ELIMINAR EL REGISTRO: \n MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
						printf("Si - [1]\nNo - [2]\nSELECCIONA UNA OPCION: ");
						scanf("%d",&sn);
						switch(sn){
							case 1:
								printf("REGISTRO ELIMINADO: \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
					printf("\nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
	temp->matricula=(rand()%10000+30000);
	temp->E=(rand()%20+18);
	genom(&temp);
	printf("\tRegistro Agregado\n\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
			if((*nuevo)->matricula < (*listaDC)->matricula){		//
				(*nuevo)->sig=*listaDC;					//
				(*nuevo)->ant=(*listaDC)->ant;			//
				((*listaDC)->ant)->sig=*nuevo;			//	Si el nodo a agregar contiene un dato menor al nodo inicial...
				(*listaDC)->ant=*nuevo;					//
				*listaDC=*nuevo;						//
				return nodo;							//
				}else{
					temp=*listaDC;															//
					while(temp->sig!=*listaDC && (temp->sig)->matricula<=(*nuevo)->matricula){		//		Se recorre la lista con "temp" hasta encontrar la posicion del nodo a agregar...
						temp=temp->sig;														//
						}																	//----------------------------------------------------------------------------
					if(temp->matricula==(*nuevo)->matricula){											//
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
	printf("-------------------------------------------------\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
	printf("\n------------------------------------------------\n");
}
Tnodo Buscar(Tnodo listaDC,int X){
	Tnodo temp=NULL, nodo=NULL;
	int Comienzo;
		if(listaDC->matricula==X){
			temp=listaDC;
			return temp;
		}
		Comienzo=ceil(((listaDC->ant)->matricula-listaDC->matricula)/2);
		if(X>=Comienzo){
			temp=(listaDC->ant);
			while(temp!=listaDC && temp->matricula >= X){
					if(temp->matricula==X){
						return temp;
					}
				temp=temp->ant;
				}
			}else{
				temp=listaDC;
				while(temp->sig!=listaDC && temp->matricula <= X){
					if(temp->matricula==X){
						return temp;
					}
				temp=temp->sig;
				}
			}
		return nodo;
}
Tnodo Eliminar(Tnodo *listaDC, int X){
	Tnodo temp=NULL, nodo=NULL;
	if((*listaDC)->matricula==X){
		temp=(*listaDC);
		if((*listaDC)->sig==(*listaDC)){	//
			(*listaDC)->ant=NULL;			// unico nodo en la lista
			(*listaDC)->sig=NULL;			//
			(*listaDC)=NULL;				//
			return temp;					//
		}else{
			if((temp->sig)->sig==*listaDC){
					(*listaDC)->sig->sig=temp->sig;			//
					((*listaDC)->ant)->ant=temp->ant;		// 	 primer nodo a eliminar - lista con 2 datos
					*listaDC=temp->sig;						// 	???????????????????????????????
					temp->sig=NULL;							//
					temp->ant=NULL;							//
					return temp;					
			}
		*listaDC=(temp->sig);							//
		(*listaDC)->ant=temp->ant;						//
		(temp->ant)->sig=*listaDC;						//
		temp->sig=NULL;									//	primer nodo de la lista a eliminar - lista con datos
		temp->ant=NULL;									//
		return temp;									//
	
		}
	}else{
		if(((*listaDC)->ant)->matricula==X){								// 		Si el ultimo nodo de la lista es el que se eliminará se hacen las siguientes preguntas:
			temp=((*listaDC)->ant);									//
				if(((*listaDC)->sig)->matricula==X){						//		- Si el nodo a eliminar es el ultimo nodo de la lista, pero esta solo contiene 2 nodos.
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
		while(temp->sig!=(*listaDC)->ant && (temp->sig)->matricula<=X){	//	Hasta encontrar el dato a eliminar...
			if((temp->sig)->matricula==X){								//	
				temp=temp->sig;										//	
				(temp->ant)->sig=temp->sig;							//	Si se encuentra que "(temp->sig)->matricula" es el nodo que contiene el valor a eliminar, la lista se detiene en "temp" 
				(temp->sig)->ant=temp->ant;							//	
				temp->sig=NULL;										//	
				temp->ant=NULL;										//	
				return temp;										//	
			}														//	----------------------------------------------------------------------------------------------------------------------	
			temp=temp->sig;											//	La lista avanza en dado caso de que "(temp->sig)->matricula" no sea el nodo a eliminar.
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

void genom(Tnodo *temp){
            int ap,am,nam,nah,s;
            char app[20][10]={"Rivera","Ayala","Garcia","Lopez","Perez","Gonzalez","Sanchez","Martinez","Rodriguez","Fernandez","Gomez","Ruiz","Diaz","Alvarez","Jimenez","Lopez","Moreno","Perez","Munoz","Morales"};
            char nomH[20][10]={"Aaron","Abraham","Adan","Agustin","Alan","Aldo","Cain","Carlos","Dagomar","Daniel","Dante","Dario","David","Diego","Edgar","Eduardo","Elias","Hector","Jacinto","Pablo"};
			char nomM[20][10]={"Abby","Abigail","Abril","Ada","Adabella","Adalia","Adela","Camila","Valentina","Valeria","Vanesa","Vanina","Ventura","Vera","Veronica","Gabriela","Karen","Karina","Nadia","Nancy"};
            ap=rand()%20;
			am=rand()%20;
            nam=rand()%20;
            nah=rand()%20;
            s=rand()%2;
        	strcpy((*temp)->AP,app[ap]);
        	strcpy((*temp)->AM,app[am]);
        	if(s==1){
        		strcpy((*temp)->N,nomH[nah]);
        		strcpy((*temp)->sexo,"M");
			}else{
				strcpy((*temp)->N,nomM[nam]);
				strcpy((*temp)->sexo,"F");
			}
        	
}
