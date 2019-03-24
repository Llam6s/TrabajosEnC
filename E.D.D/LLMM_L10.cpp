#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdatoH{
	int dato;
	struct _tdatoH *sig;
} TdatoH;

typedef TdatoH *TnodoH;
int Posicion(int, int);
TnodoH Buscar(TnodoH , int);
TnodoH Borrar(TnodoH *, int);
void Push(TnodoH *, TnodoH *);
TnodoH POP(TnodoH *pila);
void Insertar(TnodoH *, int);
int GenDato();
TnodoH Vec[13];

int main(){
srand(time(NULL));
int op, t=13,dato ,Pos;
TnodoH temp=NULL;
do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- INSERTAR DATO\n");
	printf("2.- BORRAR\n");
	printf("3.- BUSCAR\n");
	printf("4.- SALIR\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				CLS;
				dato=GenDato();
				Pos=Posicion(dato,t);
				Insertar(&(Vec[Pos]),dato);
			break;
			case 2:
				printf("INGRESE EL NUMERO A ELIMINAR: \n");
				scanf("%d",& dato);
				Pos=Posicion(dato,t);
				temp=Borrar(&(Vec[Pos]),dato);
				if(temp){
					printf("REGISTRO ELIMINADO: %d",temp->dato);
					temp=NULL;
					free(temp);
				}else{
					printf("NO EXISTE EL DATO A ELIMINAR\n");
				}
			break;
			case 3:
				printf("REGISTRO A BUSCAR: \n");
				scanf("%d", &dato);
				Pos=Posicion(dato,t);
				temp=Buscar((Vec[Pos]),dato);
				if(temp){
					printf("%d",temp->dato);
				}else{
					printf("NO EXISTE EL DATO A BUSCAR\n");
				}
			break;
		}
		PAUSA;
		CLS;
}while(op!=4);
}

void Insertar(TnodoH *PosVec, int dato){
	TnodoH temp=NULL, tempP=NULL;
	temp=(TnodoH)malloc(sizeof(TdatoH));
	temp->dato=dato;
	temp->sig=NULL;
	tempP=*PosVec;
	if(tempP){
		Push(&(*PosVec), &temp);
	}else{
		*PosVec=temp;
	}
	printf("DATO AGREGADO: %d\n",(*PosVec)->dato);
}
int Posicion(int dato, int t){
	int x;
	x=dato%t;
	printf("MOD: %d\t",x);
	return x;
}
int GenDato(){
	int temp;
	printf("DATO A INGRESAR: ");
	scanf("%d",&temp);
	return temp;
}
void Push(TnodoH *pila, TnodoH *nuevo){
	(*nuevo)->sig=(*pila);
	*pila=*nuevo;
	*nuevo=NULL;
}

TnodoH Buscar(TnodoH Vec, int dato){
	TnodoH temp=NULL;
	temp=Vec;
	if(temp){
		while(temp->sig!=NULL && temp->dato!=dato){
			temp=temp->sig;
		}
		if(temp->dato==dato){
		temp=Vec;
		return temp;
		}
	}else{
		return temp;
	}
	return NULL;
}

TnodoH Borrar(TnodoH *Vec, int dato){
	TnodoH temp=NULL, nodo=NULL;
	temp=*Vec;
	nodo=*Vec;
	if(temp){
	if((*Vec)->dato==dato){
		*Vec=(*Vec)->sig;
		temp->sig=NULL;
		return temp;
	}
		while(temp && temp->dato!=dato){
			if(temp->dato==dato){
				nodo->sig=(temp->sig);
				temp->sig=NULL;
				return temp;
			}
		nodo=temp;
		temp=temp->sig;
		}
	return NULL;
	}else{
		return NULL;
	}	

}


