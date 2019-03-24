// Llamas Medina Manuel Alonso - 1238187 - 441 
// Programa basado en Listas Circulares que agrege, elimine, busque e imprima una Lista circular de nodos, tambien que un inciso "Salir"
// en el cual se eliminen todos los registros o nodos existentes con datos simples (numeros)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PAUSA system("pause")
#define NADA printf("FILA VACIA!!!\n")
#define CLS system("cls")

typedef struct _tdato{
	int dato;
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
				if(nuevo){								//if que verifica si algun registro se repite
					printf("NO SE PUDO AGREGAR EL REGISTRO : %d\n---------REGISTRO REPETIDO---------\n", nuevo->dato);
				}
			break;
			case 2:
				if(listaC){
					printf("REGISTRO A ELIMINAR: ");
					scanf("%d",&X);
					temp=Eliminar(&listaC,&ultimo,X); 					//Se envian los parametros lista y ultimo como referencia y el numero a buscar.
					if(temp){											//"X" por valor, en este caso Eliminar regresara el nodo encontrado para realizarle servicio (libera la memoria)
						printf("REGISTRO %d ELIMINADO\n", temp->dato);
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
					temp=Buscar(listaC,ultimo, X); 				//Se envian los mismos parametros ultimo para agilizar la busqueda y no recorrer todos los nodos, lista que contiene todos los nodos, y el dato a buscar
					if(temp){									//se retorna simplemente la direccion del nodo donde se encuentra el dato buscado.
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
				Imprimir(listaC,ultimo); 							//Se envia la lista circular y el puntero ubicado en el ultimo nodo de la lista, esto con el fin
				}else{												// de detener la funcion de imprimir
					NADA;
				}
			break;
			case 5:
				while(temp!=ultimo){
					printf("ELIMINANDO REGISTROS...\n");
					temp=Salir(&listaC,&ultimo);					//el parametro ultimo se encarga de detener el proceso de eliminar registros
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
	temp=(Tnodo)malloc(sizeof(Tdato));
	temp->sig=NULL;
	temp->dato=(1+rand()%100);
	printf("REGISTRO AGREGADO: %d\n",temp->dato);
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
			if((*nuevo)->dato < (*listaC)->dato){
				(*nuevo)->sig=(*listaC);
				(*listaC)=(*nuevo);
				(*ultimo)->sig=(*listaC);
				*nuevo=NULL;
				return nodo;
				}else{
					if((*nuevo)->dato>(*ultimo)->dato){
						(*nuevo)->sig=(*listaC);
						(*ultimo)->sig=(*nuevo);
						*ultimo=*nuevo;
						return nodo;
					}else{
						temp=*listaC;
						while((temp->sig)->dato<(*nuevo)->dato){
							temp=temp->sig;
						}
						if((temp->sig)->dato!=(*nuevo)->dato){
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
	temp=listaC;						//Para imprimir se le asigna la direccion de lista a temporal para que recorra la misma
	if(listaC->dato==ultimo->dato){		//Condicion que verifica solo haya un dato en la lista circular
		Servicio(temp);					
	}else{
		while(temp->dato!=ultimo->dato){ 	//En dado caso de que la lista no tenga un solo dato, se comprueba que temporal, el cual recorre la lista
				Servicio(temp);				//no se encuentre con ultimo, esto para que se detenga un nodo antes y al salir la funcion, con el dato de salida
				temp=temp->sig;				// se imprima el ultimo valor, en este caso "ultimo"	
		}
		Servicio(temp);
	 }
}
void Servicio(Tnodo temp){
	printf("R: %d \n",(temp)->dato);
}
Tnodo Buscar(Tnodo listaC,Tnodo ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	temp=listaC;
	if(ultimo->dato==X){
		return ultimo;		//Retorna el valor ubicado en el puntero ultimo en dado caso de que el valor buscado se encuentre en ese nodo. Esto para evitar recorrer el ultimo nodo.
	}
		while(temp->dato <=X && temp!=ultimo){	//mientras temporal sea diferente de ultimo la funicon buscara en el resto de el arreglo el valor solicitado
			if(temp->dato==X){		//Busca en todo el arreglo dinamico el valor solicitado
				return temp;
			}
			temp=temp->sig;
		}
		return nodo;
}
Tnodo Eliminar(Tnodo *listaC,Tnodo *ultimo, int X){
	Tnodo temp=NULL, nodo=NULL;
	if((*listaC)->dato==X){							//si el dato a eliminar se encuentra en el primer nodo
		if((*listaC)->dato==X && (*listaC)==(*ultimo)){			//Condicion que verifica que solo exista 1 nodo en la lista
			temp=(*listaC);										//si se cumple la condicion, temporal que es el valor a retornar, toma el valor del nodo
			(*listaC)=NULL;										//Las variables listaC y ultimo se convierten en NULL debido a que ya no existen mas nodos en la lista
			(*ultimo)=NULL;
			return temp;										//retorna el unico nodo de la lista quedando esta misma vacia
		}
		temp=*listaC;										// temporal que es el valor a retornar por la funcion toma el valor del nodo a eliminar
		*listaC=(*listaC)->sig;  							//listaC avanza de posicion al siguiente nodo debido a que este puntero debe hacer referencia al inicio de la listaC		
		temp->sig=NULL;										//se descuelga el nodo temporal de la lista
		(*ultimo)->sig=*listaC;								//se actualiza el puntero ultimo
		return temp;
	}else{
		temp=*listaC;
		while(temp->sig!=*ultimo && (temp->sig)->dato<=X){
			if((temp->sig)->dato==X){						//si el dato no se encuentra en la primera posicion de la lista, se asigna un puntero temporal
				nodo=temp->sig;								//que recorra la lista hasta encontrar el valor solicitado
				temp->sig=(nodo->sig);
				nodo->sig=NULL;
				return nodo;								//en dado caso de que tenga exito, descuelga el nodo de la lista y lo retorna.
			}
			temp=temp->sig;
		}
		if((*ultimo)->dato==X){								//Si el dato a buscar se encuentra en el ultimo nodo, dado a que la funcion while recorrió
			(*ultimo)=temp;									//ya la lista y se detuvo un nodo antes de ultimo, es aqui donde el nodo ubicado antes del nodo ultimo
			temp=temp->sig;									//se convierte en el nuevo puntero ultimo, descolgando el nodo solicitado y retornandolo.
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
