#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PAUSA system("pause")
#define NADA printf("Ausencia de Datos\n")
#define CLS system("cls")
typedef struct _tdato{
	int matricula;
	char N[20];
	char AP[20];
	char AM[20];
	char sexo[2];
	int E;
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
	srand(time(NULL));
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
	printf("1.- AGREGA REGISTRO\n");
	printf("2.- SERVICIO (BORRAR REGISTRO)\n");
	printf("3.- FINALIZAR PROGRAMA \n");
	printf("Selecciona una opcion: ");
	scanf("%d",&op);
		switch(op){
			case 1:
				CLS;
				nuevo=GenDatos();
				Push(&cabeza,&ultimo,&nuevo);
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
						printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
	Tnodo temp=NULL;
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->matricula=(rand()%10000+30000);
	temp->E=(rand()%20+18);
	genom(&temp);
	printf("\tRegistro Agregado\n\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
	printf("\tREGISTRO ELIMINADO...\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
