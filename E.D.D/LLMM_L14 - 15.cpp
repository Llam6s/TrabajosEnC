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
} Tarbol;

typedef Tarbol *TarbolN;

typedef struct _tdato{
	Tarbol *nodo;
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void Push(Tnodo *pila, TarbolN nuevo);
TarbolN POP(Tnodo *pila);
Tnodo GenEspacioP(TarbolN nuevo);
TarbolN Busqueda (TarbolN ,TarbolN);
void Insertar (TarbolN *,TarbolN);
TarbolN GenDato (void);
void Caltura(TarbolN,int *,int);
void inOrden (TarbolN);
void postOrden (TarbolN);
void preOrden (TarbolN);
void menu(void);

int main(){
	srand(time(NULL));
	menu();
}

void menu(void){
	TarbolN temp=NULL, Arb = NULL, dato = NULL;
	int op, op2, x,altura=0;
	
	do{
	CLS;
	printf("\n\tM	E	N	U\n\n");
	printf("1.- Agregar\n");
	printf("2.- Eliminar\n");
	printf("3.- Buscar\n");
	printf("4.- Mostrar\n");
	printf("5.- Altura del arbol\n");
	printf("6.- Salir\n");
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
					Insertar(&Arb, dato);
					}else{
						printf("El valor ingresado ya existe, favor de ingresar un nuevo digito\n");
					}
			PAUSA;
			break;
			CLS;
			case 2:
				
			break;
			case 3:
				if(Arb){
					printf("Ingrese dato a buscar: ");
					scanf("%d",&x);
					temp=(TarbolN)malloc(sizeof(Tarbol));
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
			CLS;
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
			case 5:
				altura=0;
				Caltura(Arb, &altura, 0);
				printf("Altura del Arbol: %d\n", altura);
				PAUSA;
				CLS;
			break;
		}
	}while(op!=6);
}

TarbolN GenDato(void){
	TarbolN temp=NULL;
	temp=(TarbolN)malloc(sizeof(Tarbol));
	temp->dato=(1+rand()%100);
	temp->izq=NULL;
	temp->der=NULL;
	return temp;
}

Tnodo GenEspacioP(TarbolN nuevo){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->nodo=nuevo;
	temp->sig=NULL;
}

TarbolN Busqueda (TarbolN Arb, TarbolN dato){
	TarbolN temp=NULL, nodo = Arb;
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

void Insertar (TarbolN *Arb, TarbolN dato){
	TarbolN padre = NULL, actual = *Arb;

	while(actual){
		if(actual->dato>dato->dato){
			padre=actual;
			actual=actual->izq;
		}else{
			if(actual->dato<dato->dato){
				padre=actual;
				actual=actual->der;
			}
		}
	}
	if(!padre){
		*Arb=dato;
		return;
	}
	if(dato->dato>padre->dato){
		padre->der=dato;
		return;
	}else{
		if(dato->dato<padre->dato){
			padre->izq=dato;
			return;
		}
	}
}

void inOrden (TarbolN Arb){
	Tnodo pila = NULL;
	TarbolN temp = Arb;

	while(pila || temp!=NULL){
		if(temp){
			Push(&pila,temp);
			temp=temp->izq;
		}else{
			if(temp==NULL){
				temp = POP(&pila);
				printf(" %d -", temp->dato);
				temp=temp->der;
			}
		}
	}
	
}

void postOrden (TarbolN Arb){
	Tnodo pila = NULL;
	TarbolN temp = Arb;
	while(pila || temp){
		if(temp){
			Push(&pila,temp);
			temp=temp->izq;
		}else{
			if(temp==NULL){
				temp = POP(&pila);
				temp=temp->der;
			}else{
				temp = POP(&pila);
				printf("%d", temp->dato);
			}
		}
	}
}

void preOrden (TarbolN Arb){
	Tnodo pila = NULL;
	TarbolN temp = Arb;
	
	while(pila || temp!=NULL){
		if(temp){
			Push(&pila,temp);
			temp=temp->izq;
		}else{
			if(temp==NULL){
				temp = POP(&pila);
				temp=temp->der;
				printf(" %d -", temp->dato);
			}
		}
	}
}

void Caltura(TarbolN Arb,int *altura,int temp){
	if(Arb){
		if(Arb->izq){
			Caltura(Arb->izq, altura, temp+1);
		}
		if(Arb->der){
			Caltura(Arb->der, altura, temp+1);
		}
		if(!Arb->izq && !Arb->der){
			if(temp>*altura){
				*altura=temp;
			}
		}
	}
}

void Push(Tnodo *pila, TarbolN nuevo){
	Tnodo nodo=NULL;
	nodo=GenEspacioP(nuevo);
	(nodo)->sig=(*pila);
	*pila=nodo;
	nuevo=NULL;
}

TarbolN POP(Tnodo *pila){
	Tnodo temp=NULL;
	if(*pila){
		temp=(*pila);
		*pila=(temp)->sig;
		temp->sig=NULL;
	}
	return temp->nodo;
}

