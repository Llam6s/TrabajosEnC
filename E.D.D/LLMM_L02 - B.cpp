#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _tdato{
	int F;
	struct _tdato *sig;	
} Tdato;

typedef Tdato *Tnodo;

void menu(void);
Tnodo AgDat(int);
void Push(Tnodo *pila, Tnodo *nuevo);
Tnodo POP(Tnodo *pila);
void Servicio(Tnodo temp,int *);

int main(){
	menu();
}
void menu(){
	int op,f,i,t;
	Tnodo pila=NULL;
	Tnodo nuevo=NULL;
	Tnodo temp=NULL;
	do{
	printf("\n\tM	E	N	U\n\n");
	printf("1.- AGREGA DATO\n");
	printf("2.- IMPRIME DATO\n");
	printf("3.- FINALIZAR PROGRAMA\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				i=1,f=0;
				printf("Ingresa un numero: ");
				scanf("%d",&f);
				do{
				nuevo=AgDat(i);
				Push(&pila,&nuevo);
				pila->F=i++;
				printf("%d\n",pila->F);
				}while(pila->F<f);
				printf("COLA AGREGADA\n");
				
			break;
			case 2:
				i=1;
				do{
				temp=POP(&pila);
				if(pila){
					Servicio(temp,&i);
					free(temp);
					}else{
						printf("AUSENCIA DE DATOS\n");
						system("pause");
						system("cls");
						return menu();
					}
				printf("EL FACTORIAL DE %d ES: %d \n",f,i);
				}while(temp->sig);
			f=0; 
			break;
			case 3:
				printf("SALIENDO...\n");
			break;
			default:
			printf("OPCION INVALIDA\n");
			break;
		}
		system("pause");
		system("cls");
	}while(op!=3);
}
Tnodo AgDat(int i){
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->F=i;
	return temp; 
}
void Push(Tnodo *pila, Tnodo *nuevo){
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
void Servicio(Tnodo temp,int *i){
	*i=*i*temp->F;
}

