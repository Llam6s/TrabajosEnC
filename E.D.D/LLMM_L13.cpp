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

typedef Tarbol *TarbolP;

TarbolP Busqueda (TarbolP ,TarbolP);
void Insertar (TarbolP *,TarbolP);
TarbolP GenDato (void);
void Cnodos(TarbolP,int *);
void Chojas (TarbolP,int *);
void Caltura(TarbolP,int *,int);
void inOrden (TarbolP);
void postOrden (TarbolP);
void preOrden (TarbolP);
void menu(void);

int main(){
	srand(time(NULL));
	menu();
}
void menu(void){
	TarbolP temp=NULL, Arb = NULL, dato = NULL;
	int op, op2, x,nodos=0,hojas=0,altura=0;
	
	do{
	CLS;
	printf("\n\tM	E	N	U\n\n");
	printf("1.- Agregar\n");
	printf("2.- Buscar\n");
	printf("3.- Desplegar\n");
	printf("4.- Contar Hojas\n");
	printf("5.- Contar Nodos\n");
	printf("6.- Altura\n");
	printf("7.- Salir\n");
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
				if(Arb){
					printf("Ingrese dato a buscar: ");
					scanf("%d",&x);
					temp=(TarbolP)malloc(sizeof(Tarbol));
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
			case 3:
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
			case 4:
				hojas=0;
				Chojas(Arb, &hojas);
				printf("Hojas: %d\n", hojas);
				PAUSA;
				CLS;
			break;
			case 5:
				nodos=0;
				Cnodos(Arb, &nodos);
				printf("Nodos: %d\n", nodos);
				PAUSA;
				CLS;
			break;
			case 6:
				altura=0;
				Caltura(Arb, &altura, 0);
				printf("Altura del Arbol: %d\n", altura);
				PAUSA;
				CLS;
			break;
		}
	}while(op!=7);
}
TarbolP GenDato (void){
	TarbolP temp=NULL;
	temp=(TarbolP)malloc(sizeof(Tarbol));
	temp->dato=(1+rand()%100);
	temp->izq=NULL;
	temp->der=NULL;
	return temp;
}
TarbolP Busqueda (TarbolP Arb, TarbolP dato){
	TarbolP temp=NULL, nodo = Arb;
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
void Insertar (TarbolP *Arb, TarbolP dato){
	TarbolP padre = NULL, actual = *Arb;

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
void inOrden (TarbolP Arb){
	if(Arb){
	inOrden(Arb->izq);
	printf("- %d -", Arb->dato);
	inOrden(Arb->der);
}
}
void postOrden (TarbolP Arb){
	if(Arb){
		postOrden(Arb->izq);
		postOrden(Arb->der);
		printf("- %d -", Arb->dato);
	}
}
void preOrden (TarbolP Arb){
	if(Arb){
		printf("- %d -", Arb->dato);
		preOrden(Arb->izq);
		preOrden(Arb->der);
	}
}
void Cnodos (TarbolP Arb, int *nodos){
	if(Arb){
		Cnodos(Arb->izq, nodos);
		Cnodos(Arb->der, nodos);
		(*nodos)++;
	}
}
void Chojas(TarbolP Arb,int *hojas){
	if(Arb){
		Chojas(Arb->izq, hojas);
		Chojas(Arb->der, hojas);
		if(!Arb->izq && !Arb->der){
			(*hojas)++;
		}
	}
}
void Caltura(TarbolP Arb,int *altura,int temp){
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


