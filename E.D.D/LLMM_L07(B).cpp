// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en Lista Dobles que agrege, elimine, busque e imprima una Lista circular de nodos, tambien que un inciso "Salir"
// en el cual se eliminen todos los registros o nodos existentes con datos de alumnos.

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
Tnodo Agregar(Tnodo *,Tnodo *,Tnodo *);
void Imprimir(Tnodo ,Tnodo);
void Servicio(Tnodo );
Tnodo Buscar(Tnodo ,Tnodo ,int );
Tnodo Eliminar(Tnodo *,Tnodo *,int);
Tnodo Salir(Tnodo *,Tnodo *);
void genom(Tnodo *);

int main(){
	srand(time(NULL));
	menu();
}

void menu(){
	int op, X, sn;
	Tnodo nuevo=NULL;
	Tnodo listaD=NULL;
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
				temp=Agregar(&listaD,&nuevo,&ultimo);
				if(temp){
					printf("NO SE PUDO AGREGAR EL REGISTRO : \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n---------REGISTRO REPETIDO---------\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
					free(temp);
				}
			break;
			case 2:
				if(listaD){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Buscar(listaD,ultimo,X);
					if(temp){
						printf("SEGURO QUE DESEAS ELIMINAR EL REGISTRO: \n MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
						printf("Si - [1]\nNo - [2]\nSELECCIONA UNA OPCION: ");
						scanf("%d",&sn);
						switch(sn){
							case 1:
								printf("REGISTRO ELIMINADO: \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
								temp=Eliminar(&listaD,&ultimo,X);
								temp=NULL;
								free(temp);
							break;
							case 2:
							printf("REGRESANDO REGISTRO A LA LISTA......\n");
							Agregar(&listaD,&temp,&ultimo);
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
				if(listaD){
					printf("REGISTRO A BUSCAR: ");
					scanf("%d",&X);
					temp=Buscar(listaD,ultimo, X); 			
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
				if(listaD){
				Imprimir(listaD,ultimo); 						
				}else{											
					NADA;
				}
			break;
			case 5:
				while(temp!=ultimo){
					printf("ELIMINANDO REGISTROS...\n");
					temp=Salir(&listaD,&ultimo);				
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

Tnodo Agregar(Tnodo *listaD, Tnodo *nuevo,Tnodo *ultimo){
	Tnodo temp=NULL;
	Tnodo nodo=NULL;
	if(!*listaD){
			*listaD=*nuevo;
			*ultimo=*nuevo;
			*nuevo=NULL;
			return nodo;
		}else{
			if((*nuevo)->matricula < (*listaD)->matricula){
				(*nuevo)->sig=*listaD;
				(*listaD)->ant=*nuevo;
				*listaD=*nuevo;
				*nuevo=NULL;
				return nodo;
				}else{
					temp=*listaD;
					while((temp->sig)&&(temp->sig)->matricula<=(*nuevo)->matricula){
						temp=temp->sig;
						}
					if(temp->matricula==(*nuevo)->matricula){
						return *nuevo;
						}else{
							if(temp->sig==NULL){
								temp->sig=*nuevo;
								(*nuevo)->ant=temp;
								(*nuevo)->sig=NULL;
								*ultimo=*nuevo;
								*nuevo=NULL;
								return nodo;
							}
						}
						(*nuevo)->ant=temp;
						(*nuevo)->sig=temp->sig;
						(temp->sig)->ant=(*nuevo);
						temp->sig=(*nuevo);
						return nodo;
					}
				}
}
void Imprimir(Tnodo listaD,Tnodo ultimo){
	Tnodo temp=listaD;
		while(temp->matricula!=ultimo->matricula){ 	
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
Tnodo Buscar(Tnodo listaD,Tnodo ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	int i=1, Comienzo;
		if(ultimo->matricula==X){
			temp=ultimo;
			return temp;
		}
		Comienzo=ceil((ultimo->matricula-listaD->matricula)/2);
		if(X>=Comienzo){
			temp=ultimo;
			while(temp!=listaD && temp->matricula >= X){
					if(temp->matricula==X){
						return temp;
					}
				temp=temp->ant;
				}
			}else{
				temp=listaD;
				while(temp!=ultimo && temp->matricula <= X){
					if(temp->matricula==X){
						return temp;
					}
				temp=temp->sig;
				}
			}
		return nodo;
}
Tnodo Eliminar(Tnodo *listaD,Tnodo *ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	if((*listaD)->matricula==X){
		if((*listaD)==(*ultimo)){
			temp=(*listaD);
			(*listaD)=NULL;
			(*ultimo)=NULL;
			return temp;
		}
		temp=*listaD;
		*listaD=(*listaD)->sig;
		(*listaD)->ant=NULL;
		temp->sig=NULL;
		return temp;
	}else{
		if((*ultimo)->matricula==X){
			temp=*ultimo;
			*ultimo=(*ultimo)->ant;
			temp->ant=NULL;
			return temp;
		}
		temp=*listaD;
		while(temp->sig!=*ultimo && (temp->sig)->matricula<=X){
			if((temp->sig)->matricula==X){
				temp=temp->sig;
				(temp->ant)->sig=temp->sig;
				(temp->sig)->ant=temp->ant;
				temp->sig=NULL;
				temp->ant=NULL;
				return temp;
			}
			temp=temp->sig;
		}
		return nodo;
	}
}
Tnodo Salir(Tnodo *listaD,Tnodo *ultimo){
	Tnodo temp;			
	temp=(*listaD);
	(*listaD)=(*listaD)->sig;
	temp->sig=NULL;
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

