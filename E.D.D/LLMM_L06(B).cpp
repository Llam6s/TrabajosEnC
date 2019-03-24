// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en Listas Circulares que agrege, elimine, busque e imprima una Listas de nodos, tambien que un inciso "Salir"
// en el cual se eliminen todos los registros o nodos existentes con datos de alumno, se eliminaron los comentarios para no saturar "tanto" el codigo de texto.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
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
	int op, X;
	Tnodo nuevo=NULL;
	Tnodo listaC=NULL;
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
				nuevo=Agregar(&listaC,&nuevo,&ultimo);
				if(nuevo){							
					printf("NO SE PUDO AGREGAR EL REGISTRO : \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n---------REGISTRO REPETIDO---------\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
				}
			break;
			case 2:
				if(listaC){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Eliminar(&listaC,&ultimo,X); 				
					if(temp){								
						printf("REGISTRO ELIMINADO: \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
				if(listaC){
					printf("REGISTRO A BUSCAR: ");
					scanf("%d",&X);
					temp=Buscar(listaC,ultimo, X); 			
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
				if(listaC){
				Imprimir(listaC,ultimo); 						
				}else{											
					NADA;
				}
			break;
			case 5:
				while(temp!=ultimo){
					printf("ELIMINANDO REGISTROS...\n");
					temp=Salir(&listaC,&ultimo);					
						printf("REGISTRO ELIMINADO: \nMATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
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
	temp->matricula=(rand()%10000+30000);
	temp->E=(rand()%20+18);
	genom(&temp);
	printf("\tRegistro Agregado\n\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d\n",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
	return temp;	
}
Tnodo Agregar(Tnodo *listaC, Tnodo *nuevo,Tnodo *ultimo){
	Tnodo temp=NULL;
	Tnodo nodo=NULL;
	if(!*listaC){
			*listaC=*nuevo;
			*ultimo=*nuevo;
			(*ultimo)->sig=(*listaC);
			*nuevo=NULL;
			return nodo;
	}else{
			if((*nuevo)-> matricula< (*listaC)->matricula){
				(*nuevo)->sig=(*listaC);
				(*listaC)=(*nuevo);
				(*ultimo)->sig=(*listaC);
				*nuevo=NULL;
				return nodo;
				}else{
					if((*nuevo)->matricula>(*ultimo)->matricula){
						(*nuevo)->sig=(*listaC);
						(*ultimo)->sig=(*nuevo);
						*ultimo=*nuevo;
						return nodo;
					}else{
						temp=*listaC;
						while((temp->sig)->matricula<(*nuevo)->matricula){
							temp=temp->sig;
						}
						if((temp->sig)->matricula!=(*nuevo)->matricula){
							(*nuevo)->sig=temp->sig;
							temp->sig=*nuevo;
							*nuevo= NULL;
							return nodo;
						}
						return *nuevo;
					}
				}
		}
}
void Imprimir(Tnodo listaC,Tnodo ultimo){
	Tnodo temp=NULL;
	temp=listaC;					
	if(listaC->matricula==ultimo->matricula){	
		Servicio(temp);					
	}else{
		while(temp->matricula!=ultimo->matricula){ 	
				Servicio(temp);			
				temp=temp->sig;				
		}
		Servicio(temp);
	 }
}
void Servicio(Tnodo temp){
	printf("-------------------------------------------------\n");
	printf("MATRICULA: %d\nNOMBRE: %s\nAPELLIDO PATERNO: %s\nAPELLIDO MATERNO: %s\nEDAD: %d",temp->matricula,temp->N,temp->AP,temp->AM,temp->E);
	printf("\n------------------------------------------------\n");
}
Tnodo Buscar(Tnodo listaC,Tnodo ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	temp=listaC;
	if(ultimo->matricula==X){
		return ultimo;		
	}
		while(temp->matricula <=X && temp!=ultimo){	
			if(temp->matricula==X){	
				return temp;
			}
			temp=temp->sig;
		}
		return nodo;
}
Tnodo Eliminar(Tnodo *listaC,Tnodo *ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	if((*listaC)->matricula==X){	
		if((*listaC)->matricula==X && (*listaC)==(*ultimo)){		
			temp=(*listaC);									
			(*listaC)=NULL;									
			(*ultimo)=NULL;
			return temp;									
		}
		temp=*listaC;									
		*listaC=(*listaC)->sig;  						
		temp->sig=NULL;									
		(*ultimo)->sig=*listaC;							
		return temp;
	}else{
		temp=*listaC;
		while(temp->sig!=*ultimo && (temp->sig)->matricula<=X){
			if((temp->sig)->matricula==X){					
				nodo=temp->sig;							
				temp->sig=(nodo->sig);
				nodo->sig=NULL;
				return nodo;							
			}
			temp=temp->sig;
		}
		if((*ultimo)->matricula==X){							
			(*ultimo)=temp;								
			temp=temp->sig;								
			(*ultimo)->sig=*listaC;
			temp->sig=NULL;
			return temp;
		}
		return nodo;
	}
}
Tnodo Salir(Tnodo *listaC,Tnodo *ultimo){
	Tnodo temp;			
	temp=(*listaC);
	(*listaC)=(*listaC)->sig;
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
