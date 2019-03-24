#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>

#define PAUSA system("pause")
#define NADA printf("ARBOL VACIO!!!\n")
#define CLS system("cls")

typedef struct _tarbol{
    int dato;
	struct _tarbol *izq;
	struct _tarbol *der;
	struct _tarbol *padre;
	int FE;
	int hD;
	int hI;
} TarbolAVL;

typedef TarbolAVL *AVLtree;

AVLtree Busqueda (AVLtree ,AVLtree);
void Insertar (AVLtree *,AVLtree *);
AVLtree GenDato (void);
AVLtree FE (AVLtree *);
void Balanceo(AVLtree *,AVLtree *);
void Flasheo(AVLtree *, AVLtree );
void menu(void);
void RSD(AVLtree *,AVLtree *);
void RSI(AVLtree *,AVLtree *);
void inOrden (AVLtree);
void postOrden (AVLtree);
void preOrden (AVLtree);
AVLtree Eliminar(AVLtree *,AVLtree *);
int main(){
	srand(time(NULL));
	menu();
}

void menu(void){
	AVLtree temp=NULL, Arb = NULL, dato = NULL, fact=NULL;
	int op, op2, x,altura=0;
	
	do{
	CLS;
	printf("\n\tM	E	N	U\n\n");
	printf("1.- Agregar\n");
	printf("2.- Eliminar\n");
	printf("3.- Buscar\n");
	printf("4.- Mostrar\n");
	printf("5.- Salir\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op)
		{
			case 1:
			CLS;
			dato = GenDato();
			temp = Busqueda(Arb, dato);
				if(!temp){
					printf("Dato agregado: %d\n",dato->dato);
					Insertar(&Arb, &dato);
					fact = FE(&dato);

					if(fact){
						Balanceo(&fact,&Arb);
					}
					}else{
						printf("El valor ingresado ya existe, favor de ingresar un nuevo digito\n");
					}
			PAUSA;
			break;
			CLS;
			case 2:
				CLS;
				dato = GenDato();
				temp = Busqueda(Arb, dato);
					if(!temp){
						printf("Dato agregado: %d\n",dato->dato);
						Insertar(&Arb, &dato);
						fact = FE(&dato);
	
						if(fact){
							Balanceo(&fact,&Arb);
						}
						}else{
							printf("El valor ingresado ya existe, favor de ingresar un nuevo digito\n");
						}
			PAUSA;
			break;
			case 3:
				if(Arb){
					printf("Ingrese dato a buscar: ");
					scanf("%d",&x);
					temp=(AVLtree)malloc(sizeof(TarbolAVL));
					temp->dato=x;
					temp = Busqueda(Arb,temp);
					if(temp){
						printf("Dato encontrado: %d\n", temp->dato);
					}else{
						printf("No se encontro el registro solicitado\n");
					}
				}else{
					NADA;
				}
			PAUSA;				
			break;
			case 4:
				do{
					printf("\n\tD E S P L E G A R\n\n");
					printf("1.- InOrden\n");
					printf("2.- PostOrden\n");
					printf("3.- PreOrden\n");
					printf("4.- Salir\n");
					scanf("%d",&op2);
					CLS;				
					switch(op2){
						case 1:
							inOrden (Arb);
						break;
						case 2:
							postOrden(Arb);
						break;
						case 3:
							preOrden(Arb);
						break;
					}
					PAUSA;
					CLS;
				}while(op2!=4);
			break;
		}
	}while(op!=5);
}

AVLtree GenDato(void){
	AVLtree temp=NULL;
	temp=(AVLtree)malloc(sizeof(TarbolAVL));
	scanf("%d",&temp->dato);
	//temp->dato=(1+rand()%100);
	Flasheo(&temp, temp->padre);
	return temp;
}

AVLtree Busqueda (AVLtree Arb, AVLtree dato){
	AVLtree temp=NULL, nodo = Arb;
	if(Arb){
		while(nodo){
			if(dato->dato==nodo->dato){
				temp=nodo;
				return temp;
			}else{
				if(dato->dato>nodo->dato){
					nodo=nodo->der;
				}else{
					if(dato->dato<nodo->dato){
						nodo=nodo->izq;
					}
				}
			}
		}
	}
		return temp;
}

void Insertar (AVLtree *Arb, AVLtree *dato){
	AVLtree padre = NULL, actual = *Arb;

	while(actual){
		if(actual->dato>(*dato)->dato){
			padre=actual;
			actual=actual->izq;
		}else{
			if(actual->dato<(*dato)->dato){
				padre=actual;
				actual=actual->der;
			}
		}
	}
	if(!padre){
		*Arb=*dato;
		(*Arb)->padre=NULL;
		return;
	}
	if((*dato)->dato>padre->dato){
		padre->der=*dato;
		(*dato)->padre=padre;
		return;
	}else{
		if((*dato)->dato<padre->dato){
			padre->izq=*dato;
			(*dato)->padre=padre;
			return;
		}
	}
}

void Flasheo(AVLtree *nodo, AVLtree padre){
	(*nodo)->padre=padre;
	(*nodo)->der=NULL;
	(*nodo)->izq=NULL;
	(*nodo)->hI=0;
	(*nodo)->hD=0;
	(*nodo)->FE=0;
}

AVLtree FE(AVLtree *nuevo){
	AVLtree  nodo = NULL;
	nodo=*nuevo;
	int temp;
	while(nodo){
		if(nodo->der){
			if((nodo->der)->hI>(nodo->der)->hD){
			nodo->hD=(nodo->der)->hI+1;
			}else{
				nodo->hD=(nodo->der)->hD+1;
			}
		}
		if(nodo->izq){
			if((nodo->izq)->hI>(nodo->izq)->hD){
				nodo->hI=(nodo->izq)->hI+1;
			}else{
				nodo->hI=(nodo->izq)->hD+1;
			}
		}
		nodo->FE=nodo->hD - nodo->hI;
		if(nodo->FE<2 && nodo->FE >-2){
			nodo=nodo->padre;
		}else{
			return nodo;
		}
	}
	if(nodo==NULL){
		return NULL;
	}
}

void Balanceo (AVLtree *fact,AVLtree *Arb){
	
	if((*fact)->FE>=2 && ((*fact)->der)->FE==1){
		printf("ROTACION SIMPLE A LA IZQUIERDA");
		RSI(fact,Arb);
		return;
	}
	if((*fact)->FE<=-2 && ((*fact)->izq)->FE==-1){
		printf("ROTACION SIMPLE A LA DERECHA");
		RSD(fact,Arb);
		return;
	}
	if((*fact)->FE>=2 && ((*fact)->der)->FE==-1){
		printf("ROTACION DOBLE A LA IZQUIERDA");
		RSD(&(*fact)->der, Arb);
		RSI(fact,Arb);
		return;
	}
	if((*fact)->FE<=-2 && ((*fact)->izq)->FE==1){
		printf("ROTACION DOBLE A LA DERECHA");
		RSI(&(*fact)->izq,Arb);
		RSD(fact,Arb);
		return;
	}
}

void RSD(AVLtree *nodo,AVLtree *Arb){
	AVLtree temp = NULL;
	
	temp=(*nodo)->izq;
	if(temp->der){
		(*nodo)->izq=temp->der;
		(temp->der)->padre=*nodo;
	}else{
		(*nodo)->izq=NULL;
	}
	temp->der=*nodo;
	if((*nodo)->padre){
		temp->padre=((*nodo)->padre);
		if(((*nodo)->padre)->der==*nodo){
			((*nodo)->padre)->der=temp;
		}else{
			((*nodo)->padre)->izq=temp;
		}
	}else{
		temp->padre=NULL;
		*Arb=temp;
	}
	(*nodo)->padre=temp;
}

void RSI(AVLtree *nodo,AVLtree *Arb){
	AVLtree temp = NULL;
	
	temp=(*nodo)->der;
	if(temp->izq){
		(*nodo)->der=temp->izq;
		(temp->izq)->padre=*nodo;
	}else{
		(*nodo)->der=NULL;
	}
	temp->izq=*nodo;
	if((*nodo)->padre){
		temp->padre=((*nodo)->padre);
		if(((*nodo)->padre)->izq==*nodo){
			((*nodo)->padre)->izq=temp;
		}else{
			((*nodo)->padre)->der=temp;
		}
	}else{
		temp->padre=NULL;
		*Arb=temp;
	}
	(*nodo)->padre=temp;
}

void inOrden (AVLtree Arb){
	if(Arb){
	inOrden(Arb->izq);
	printf("- %d -", Arb->dato);
	inOrden(Arb->der);
}	
}

void postOrden (AVLtree Arb){
	if(Arb){
		postOrden(Arb->izq);
		postOrden(Arb->der);
		printf("- %d -", Arb->dato);
	}
}

void preOrden (AVLtree Arb){
	if(Arb){
		printf("- %d -", Arb->dato);
		preOrden(Arb->izq);
		preOrden(Arb->der);
	}
}

AVLtree Eliminar(AVLtree *dato,AVLtree *Arb){
	
}
