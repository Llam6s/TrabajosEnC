#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct {
        char appat[20];
        char appmat[20];
        char nom[20];
        char sexo[1];
        int num;
        int edad;
               }tdatos;
         
void menu (void);
void agrega (tdatos [], int*);
void buscar (tdatos [], int*);
void ordenar (tdatos [], int*);
void autom (tdatos [], int*);
void imprimirV (tdatos [], int*);
void genom (tdatos [], int);
void matried (tdatos [],int);
int secuencial (tdatos [], int, int *);
void burbuja (tdatos [], int*);
void ST (tdatos [], int*);
void imptex ();

int main (void){
   srand(time(NULL));
   menu();
   return 0;
}
void menu(void){
   int op,t=0;
   tdatos datos[300];
   do{
      system ("cls");
      printf("\n M  E   N   U\n");
	  printf("\n1.- LLENA VECTOR");
	  printf("\n2.- BUSCAR");
	  printf("\n3.- ORDENAR");
	  printf("\n4.- ARCHIVO DE TEXTO");
	  printf("\n5.- IMPRIMIR (ARREGLO)");
	  printf("\n6.- IMPRIMIR (ARCH. TEXT.)");
	  printf("\n7.- SALIR");
	  printf("\nELIGE UNA OPCION: ");
      scanf ("%d",&op);
	  switch(op)
	    {
		  case 1: agrega(datos,&t);  break;
		  case 2: buscar(datos,&t);  break;
		  case 3: ordenar(datos,&t);  break;
		  case 4: ST(datos,&t) ; break;
		  case 5: imprimirV(datos,&t); break;
		  case 6: imptex() ; break;
		  case 7: printf("Saliendo...") ; break;
          default:
		  system("cls");
		  printf("Opcion invalida\n");
		  system("pause"); break;
		}
   	  }while(op!=7);
}
void agrega(tdatos datos[],int *t){
	system ("cls"); 
	int op;
	do{
		printf("1.- Automatico (10)\n2.- Regresar al menu principal\nElige la opcion: ");
		scanf("%d",&op);
	switch(op){
		case 1 : autom(datos,t); break;
		case 2 : printf("Regresando al menu principal...\n"); break;
		default: 
		printf("Entrada invalida\n");
		system("pause"); 
		system("cls"); break;
				 }
	}while(op!=2);
	
    system("pause");
}
void imprimirV(tdatos datos[], int *t){ 
	 system ("cls");
	 if(*t<=0){
	 	printf("NO HAY DATOS PARA IMPRIMIR\n");
	 	system("pause");
	 	return;
	 }
	 int i;
	 printf(" -------------------------------------------------------------------\n");
	 printf("| # EMPLEADO  |  AP. PAT. |  AP. MAT. |   NOMBRE  |   EDAD  | SEXO |\n");
	 for(i=0;i<*t;i++){
	 	printf(" -------------------------------------------------------------------\n");
	 	printf("|%11d  |%10s |%10s |%10s |    %d   |%5s |\n",datos[i].num,datos[i].appat, datos[i].appmat,datos[i].nom,datos[i].edad,datos[i].sexo);
	 }	printf(" -------------------------------------------------------------------\n");
	 
     system("pause");
}
void buscar(tdatos datos[], int *t){
	 system ("cls");
	 int x,c=-1,op;
	 tdatos temp;
	 do{
	 	 system ("cls");
     	 printf("\n ELIGE UN METODO DE BUSQUEDA\n");
	  	 printf("\n1.- SECUENCIAL");
	  	 printf("\n2.- SALIR");
	  	 printf("\n SELECCIONA EL METODO DE BUSQUEDA: ");
	  	 scanf("%d",&op);
		 switch(op)
		 {
		 case 1:{
		 	 system ("cls");
			 printf("BUSQUEDA SECUENCIAL\n");
			 printf("Ingrese el numero de matricula que desea buscar: ");
			 scanf("%d", &x);
			 c=secuencial(datos,x,t); 
		 break;
		 }
		 case 2:{
		 	printf("SALIENDO...\n");
		 	system("pause");
		 	return;
			break;
		 }
		 default:printf("\nOPCION INVALIDA!\n"); break;
		}
		 if(c!=-1){
			 printf("Busqueda finalizada\nElemento encontrado!!\n");
			 printf(" -------------------------------------------------------------------\n");
	 		 printf("|  MATRICULA  |  AP. PAT. |  AP. MAT. |   NOMBRE  |   EDAD  | SEXO |\n");
	 		 printf(" -------------------------------------------------------------------\n");
	 		 printf("|%11d  |%10s |%10s |%10s |    %d   |%5s |\n",datos[c].num,datos[c].appat, datos[c].appmat,datos[c].nom,datos[c].edad,datos[c].sexo);
	 		 printf(" -------------------------------------------------------------------\n");
				    }else{
		 				printf("\nElemento no encontrado\n\n");
					 }
	     system("pause");
	    }while(op!=2);
}
void ordenar(tdatos datos[], int *t){
    int op;
	system ("cls");
	do{
	 	 system ("cls");
     	 printf("\n ELIGE UN METODO DE ORDENACION\n");
	  	 printf("\n1.- BURBUJA");
	  	 printf("\n2.- SALIR");
	  	 printf("\n ELIGE EL METODO DE ORDENACION: ");
	  	 scanf("%d",&op);
		 switch(op){
		 case 1:{
		 system ("cls");
		 printf("BURBUJA");
		 burbuja(datos,t);
		 break;
		 }
		 case 2:{
		 	printf("SALIENDO...\n");
			break;
		 }
		 default:printf("\nOPCION INVALIDA!\n"); break;
		}
	    }while(op!=2);
	system("pause");
}
void autom(tdatos datos[], int *t){
{
	  if(*t+10>500){
	  	printf("No se pueden capturar mas datos\n");
	  	system("pause");
	  	system ("cls");
	  	return ;
	  }else{
	  	system ("cls");
	 	int i,q=*t+10,c,j,r;
			 for(i=*t; i<q; i++){
	 			genom(datos,i);
	 			matried(datos,i);
				 }
	 *t+=10;
	 printf("REGISTROS ACTUALES: %d\n", *t);
     system("pause");
     system ("cls"); 
	  }
}
}
void genom(tdatos datos[],int t){
            int ap,am,nam,nah,s;
            char app[20][10]={"Rivera","Ayala","Garcia","Lopez","Perez","Gonzalez","Sanchez","Martinez","Rodriguez","Fernandez","Gomez","Ruiz","Diaz","Alvarez","Jimenez","Lopez","Moreno","Perez","Munoz","Morales"};
            char nomH[20][10]={"Aaron","Abraham","Adan","Agustin","Alan","Aldo","Cain","Carlos","Dagomar","Daniel","Dante","Dario","David","Diego","Edgar","Eduardo","Elias","Hector","Jacinto","Pablo"};
			char nomM[20][10]={"Abby","Abigail","Abril","Ada","Adabella","Adalia","Adela","Camila","Valentina","Valeria","Vanesa","Vanina","Ventura","Vera","Veronica","Gabriela","Karen","Karina","Nadia","Nancy"};
            ap=rand()%20;
			am=rand()%20;
            nam=rand()%20;
            nah=rand()%20;
            s=rand()%2;
        	strcpy(datos[t].appat,app[ap]);
        	strcpy(datos[t].appmat,app[am]);
        	if(s==1){
        		strcpy(datos[t].nom,nomH[nah]);
        		strcpy(datos[t].sexo,"M");
			}else{
				strcpy(datos[t].nom,nomM[nam]);
				strcpy(datos[t].sexo,"F");
			}
        	
}
void matried (tdatos datos[],int i){
	int j,c;
	do{
	c=0;
	datos[i].num=1+rand()%(800-1);
	for(j=0;j<=i;j++){
		if(datos[i].num==datos[j].num){
			c++;
		}
	}
}while(c>1);
	datos[i].edad=18+rand()%(26-18);
}
int secuencial (tdatos datos[], int x, int *t){
	int i;
	for(i=0; i<*t;i++){
	      	if(x==datos[i].num){
				return i;
			  }
		  }
		  return -1;	
}
void burbuja (tdatos datos[], int *t){
	int i=0,c;
	tdatos temp;
	system("cls");
		do{
			c=0;
			for(i=0;i<*t-1;i++){
		 		if(datos[i].num>datos[i+1].num){
		 			c++;
		 			temp=datos[i+1];
			 		datos[i+1]=datos[i];
			 		datos[i]=temp;
			 				}
		 				}
			}while(c!=0);
		printf("ORDENACION FINALIZADA...\n");
		system("pause");
}
void ST(tdatos datos[], int *t){
	system("cls");
	if(*t<=0){
		printf("NO HAY ARCHIVOS PARA CAPTURAR...\n");
		system("pause");
		return;
	}
	int i;
	FILE *CMP;
	CMP=fopen("Datos Empleado.txt","wa+");
	for(i=0;i<*t;i++){
	 	fprintf(CMP,"%d %s %s %s %d %s\n",datos[i].num,datos[i].appat, datos[i].appmat,datos[i].nom,datos[i].edad,datos[i].sexo);
}
	fclose(CMP);
	printf("Archivo creado!!!\n");
	system("pause");
}
void imptex(){
	system("cls");
	tdatos temp;
	FILE *CMP;
	CMP=fopen("Datos Empleado.txt","r");
	if(CMP){
		printf(" -------------------------------------------------------------------\n");
		printf("| # EMPLEADO  |  AP. PAT. |  AP. MAT. |   NOMBRE  |   EDAD  | SEXO |\n");
		printf(" -------------------------------------------------------------------\n");
		while((fscanf(CMP,"%s%s%s%s%s%s",&temp.num,&temp.appat,&temp.appmat,&temp.nom,&temp.edad,&temp.sexo))!=EOF){
	 	printf("| %11s |%10s |%10s |%10s |    %s   |%5s |\n",&temp.num,&temp.appat,&temp.appmat,&temp.nom,&temp.edad,&temp.sexo);
	 	printf(" -------------------------------------------------------------------\n");
		}
	fclose(CMP);
		}else{
			printf("No existe el archivo...\n");
			system("pause");
			return;
		}
	system("pause");
}
