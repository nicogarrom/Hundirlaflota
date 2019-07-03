#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pasoaux()//Esta es una funcion auxiliar para registrar mejor las entradas de teclado, para que no diese error//
{
    char lol;
    do{
        lol=getchar();
    }while(lol!='\n');
}

typedef struct 
{
    int y;
    int x;

}coords;

int randmap(int **colocb,int n)//genera aleatoriamente el numero de barcos en funcion de n y los reparte//
{
    int i,j,cuenta=0;
    srand((unsigned)time(NULL));
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            colocb[i][j]=rand()%2;
            if(colocb[i][j]==1)
            {
                cuenta++;
            }
        }
    }
    return cuenta;
}
void tablero(char **campobat,int n)//imprime el tablero en pantalla con cada jugada//
{
    int i,j;

    campobat[0][0]=' ';
    for(i=1;i<(n+1);i++)
    {
        campobat[0][i]=i+48;
        campobat[i][0]=i+48;
    }

    for(i=1;i<(n+1);i++)
    {
        for(j=1;j<(n+1);j++)
        {
            campobat[i][j]='+';
        }
    }
}
void batalla(int **colocb, char **campobat,int n, coords x,int *cuenta,int *fallo)//esta es la funcion que usamos para atacar, introducimos la matriz-puntero del campo, la matriz de la colocacion de los barcos, las coordenadas de cada ataque y la cuenta de barcos restantes y fallos//
{

    int i,j;

     for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(x.x-1 == i && x.y-1 == j)
                {
                    if(colocb[i][j]==1)
                    {
                        if(campobat[i+1][j+1]=='O')
                        {
                            printf("\nYa le has dado a esta casilla\n");
                            break;
                        }
                        printf("\nBlanco!\n");
                        campobat[i+1][j+1]='O';
                        (*cuenta)--;
                    }
                    else
                    {
                        if(campobat[i+1][j+1]=='X')
                        {
                            printf("\nYa le has dado a esta casilla\n\n");
                            break;
                        }
                        printf("\nHas fallado!\n");
                        campobat[i+1][j+1]='X';
                        (*fallo)++;
                    }

                }
            }
        }


}
void resultado(char **campobat,int n)//Esta funcion valora los datos que hay en el campo para mostrarte cada casilla //
{
    int i,j;

    for(i=0;i<(n+1);i++)
    {
        for(j=0;j<(n+1);j++)
        {
            printf("%6c",campobat[i][j]);
        }
        printf("\n\n");
    }
}
int main(){
	
	FILE *f;
	coords coord;//son las variables que introducen para hacer un ataque//
   int **barcos;//este puntero matricial lo usaremos para hacer una matriz de memoria dinámica donde almacenaremos la posición de los barcos(1)//
   char **campobatx;
   int i,j;
   int n;
   char size,nivel;//size es el tamaño del tablero, que influye sobre n, y el nivel es una varibale auxiliar para la dificultad//
   int dificultad=0;//la dificultad determina el número de fallos que puedes cometer antes de ser eliminado//
   int cuentab=0;//cuenta los barcos que hay en tablero, cuya cantidad se genera más o menos aleatoriamente en función de la dificultad//
   int fallos=0;//cuenta los fallos
   int recuentof;


   printf("\t\t\tBienvenido a hundir la flota!");

   printf("\nElige el tamaño(P,M,G):");
   scanf("%c",&size);
   pasoaux();

      switch(size)//Aquiì escogemos el tamaño del tablero, que afectará a la n//
   {
       case 'p':
       case 'P':n=3;break;
       case 'm':
       case 'M':n=5;break;
       case 'g':
       case 'G':n=8;break;
       default:printf("\nOpcion no disponible.\n");
               getch();
               exit(EXIT_FAILURE);
   }

   printf("\nElige dificultad(F,D):");
   scanf("%c",&nivel);
   pasoaux();

   switch(nivel)//ELegimos la dificultad, que determina el numero de fallos límite//
   {
       case 'f':
       case 'F':dificultad=(n*3)-6;break;
       case 'd':
       case 'D':dificultad=(n/2)+1;break;
       default:printf("\nOpcion no disponible.\n");
               getch();
               exit(EXIT_FAILURE);
   }

   barcos=(int**)malloc(n*sizeof(int*));

   for(i=0;i<n;i++)
   {
       barcos[i]=(int*)malloc(n*sizeof(int));
   }

   campobatx=(char**)malloc((n+1)*sizeof(char*));

   for(i=0;i<(n+1);i++)
   {
       campobatx[i]=(char*)malloc((n+1)*sizeof(char));
   }

   cuentab=randmap(barcos,n);
	recuentof=cuentab;
   printf("\n\nBarcos restantes:%d",cuentab);
   printf("\nNumero de fallos permitidos: %d\n\n",dificultad);

   tablero(campobatx,n);
   resultado(campobatx,n);

   while(cuentab!=0 && fallos!=dificultad)
   {

   printf("\nIntroduce coordenadas (x,y):");
   scanf("%d,%d",&coord.x,&coord.y);
   pasoaux();

   batalla(barcos,campobatx,n,coord,&cuentab,&fallos);
   resultado(campobatx,n);

   printf("Barcos restantes:%d",cuentab);
   printf("\nNumero de fallos(sobre %d): %d\n\n",dificultad,fallos);

   }
   if(cuentab==0)
   {
       printf("\nVictoria!\n\n");
       f=fopen("Resumen_de_partida.txt","w");
       fprintf(f,"\t\tResultado\nVictoria\nTamaño de tablero: %c\nNivel: %c\nNumero de aciertos: %i\nNumero de fallos: %i\n",size,nivel,recuentof,fallos);
       fclose(f);
       getch();
   }
   else if(fallos==dificultad)
   {
       printf("\nDerrota!\n\n");
       f=fopen("Resumen_de_partida.txt","w");
       fprintf(f,"\t\tResultado\nDerrota\nTamaño de tablero: %c\nNivel: %c\nNumero de aciertos: %i\nNumero de fallos: %i\n",size,nivel,recuentof,fallos);
       fclose(f);
       getch();
   }


  return 0;
}
