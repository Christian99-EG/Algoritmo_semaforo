#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define n 6
#define m 3

struct Nodo_Jt
{
  int No,Edo,Localidad,Sec[3];
  Nodo_Jt *sig_jt;
};

Nodo_Jt *PtrJt, *QrryJt, *NuevoPtrJt, *AuxJt, *AuxJt2;

struct Lista
{
  int Jt,Pagina,Tiempo,Ciclos,Edo,Seccion_critica,Inicio_Sc,Duracion,Interrupcion;
  Lista *sig;
};

Lista *PtrLista, *QrryLista, *NuevoPtrLista, *Aux, *Aux2, *Aux3;

struct Semaforo
{
  int Binario,Jt,Pagina,Tiempo,Ciclos,Edo,Seccion_critica,Inicio_Sc,Duracion,Interrupcion;
  Semaforo *sig_semaforo;
};

Semaforo *PtrSm, *QrrySm, *NuevoPtrSm, *AuxSm, *Aux2Sm;


void crear_jt(void);
void ver_jt(void);

void crear_lista(void);
void ver_lista(void);

void Algoritmo_RoundRobin();
void vector(int);

void semaforo();
void eliminar();

main()
{
  printf("\n creacion de tablas \n ");

  crear_jt();
  ver_jt();

  crear_lista();
  ver_lista();

  Algoritmo_RoundRobin();

  getch();
}

void crear_jt(void)
{
  int jt[6] = {435,325,515,725,328,400};
  int No=1;
  int i,j;

  PtrJt = (Nodo_Jt *)malloc(sizeof(Nodo_Jt));
  PtrJt->No=No;
  PtrJt->Edo=0;
  No++;
  PtrJt->Localidad=0+rand()%1024;
  PtrJt->sig_jt = NULL;
  QrryJt = PtrJt;

  for(i=1;i<=5;i++)
  {
    NuevoPtrJt = (Nodo_Jt *)malloc(sizeof(Nodo_Jt));

    NuevoPtrJt->Edo=0;
    NuevoPtrJt->No=No;
    No++;
    NuevoPtrJt-> Localidad = 0+rand()%1024;
    NuevoPtrJt-> sig_jt = NULL;
    QrryJt = NuevoPtrJt;
  }

  AuxJt = PtrJt;
  printf("\n");
  while(AuxJt!=NULL)
  {
    for(i=0;i<3;i++) //creacion de secuencias para cada tarea
    {
      do
      {
        AuxJt-> Sec[i] =1+rand()%5;
      }while(AuxJt->Sec[i] == AuxJt->Sec[i-1]);
    }
    AuxJt= AuxJt->sig_jt;
  }
}//end function crear_jt

void ver_jt(void)
{
  AuxJt = PtrJt;
  printf("\n \n TABLA DE TAREAS JT ");
  printf("\n  [Numero Tarea] \t [Localizacion PTM] \t [Paginas] "); // \n
   while(AuxJt!=NULL)
   {
     printf("\n %d \t P%d, P%d, P%d", AuxJt->No, AuxJt->Localidad, AuxJt->Sec[0], AuxJt->Sec[1], AuxJt->Sec[2]);

     AuxJt=AuxJt-> sig_jt;
   }
}//end function ver_jt

void crear_lista(void)
{
  int nuevo_elemento, flag=1, i=0, j=0;

  while(flag<QrryJt->No*3)
  {
    if(PtrLista==NULL)
    {
      PtrLista = (Lista *)malloc(sizeof(Lista));
      PtrLista-> Jt=1;
      PtrLista-> Pagina= PtrJt ->Sec[0];

      PtrLista->Tiempo= 0;
      PtrLista->Ciclos= 5+rand()%(15-5);
      PtrLista->Edo= 1;
      do
      {
        PtrLista->Interrupcion=-5+rand()%(40);
      }while(PtrLista->Interrupcion>4&&PtrLista->Interrupcion<32);

      PtrLista->Seccion_critica = 0;
      PtrLista->Duracion = 0+rand()%(PtrLista->Ciclos-1);
      PtrLista->Inicio_Sc = 0+rand()%(PtrLista->Ciclos-PtrLista->Duracion);
      PtrLista->sig = NULL;
      QrryLista = PtrLista;
      AuxJt=PtrJt;
    }
    else
    {
      NuevoPtrLista = (Lista *)malloc(sizeof(Lista));
      if(i%2==0&&i!=0)
      {
        j++;
        i=-1;
        AuxJt=AuxJt->sig_jt;
      }
      NuevoPtrLista->Jt= j+1;
      NuevoPtrLista->Pagina= AuxJt-> Sec[i+1];
      NuevoPtrLista->Tiempo= flag;
      flag++;
      NuevoPtrLista->Ciclos= 5+rand()%(15-5);
      NuevoPtrLista->Edo = 1;
      do
      {
        NuevoPtrLista->Interrupcion=-5+rand()%(40);
      }while(NuevoPtrLista->Interrupcion>4&&NuevoPtrLista->Interrupcion<32);

      NuevoPtrLista->Seccion_critica= 0;
      NuevoPtrLista->Duracion = 0+rand()%(NuevoPtrLista->Ciclos-1);
      NuevoPtrLista->Inicio_Sc= 0+rand()%(NuevoPtrLista->Ciclos-NuevoPtrLista->Duracion);
      NuevoPtrLista-> sig = NULL;
      QrryLista->sig = NuevoPtrLista;
      QrryLista = NuevoPtrLista;
      i++;
    }
  }
}

void ver_lista(void)
{
  Aux = PtrLista;
  printf("\n \n [Proceso] [Tiempo de llegada] [Ciclos] [Estado] [Seccion critica] [Inicio Sc] [Duracion] [Interrupcion] \n");
  while(Aux!=NULL)
  {
    if(Aux->Interrupcion>=0)
    {
      printf("\n J%dP%d          %d              %d       %d          %d              %d          %d           %d        ", Aux->Jt, Aux->Pagina, Aux->Tiempo, Aux->Ciclos, Aux->Edo, Aux->Seccion_critica, Aux->Inicio_Sc, Aux->Duracion,Aux->Interrupcion);
    }
    else
    {
      printf("\n J%dP%d          %d              %d       %d          %d              %d          %d         No int      ", Aux->Jt, Aux->Pagina, Aux->Tiempo, Aux->Ciclos, Aux->Edo, Aux->Seccion_critica, Aux->Inicio_Sc, Aux->Duracion);
    }
  Aux=Aux->sig;
 }
}//end function ver_lista

void Algoritmo_RoundRobin()
{
  int q=5, i, sum=0, drop=0, j=0, rat=1;

  while(rat==1)
  {
    Aux=PtrLista;
    	printf("\n\n                   BLOQUE DE CONTROL DE PROCESOS (PCB)");

      while(Aux!=NULL)
      {
        if(Aux->Edo!=5)
        {
          Aux->Edo=2;
          Aux2=Aux;
          getch();
          system("cls");
          printf("\n\n                   BLOQUE DE CONTROL DE PROCESOS (PCB)");
  				printf("\n\n -------------------------------------------RONDA %d------------------------------------------",j+1);
  				printf("\n    ******J%dP%d se carga en memoria*********",Aux->Jt,Aux->Pagina);
          ver_lista();
          Aux=Aux2;
          i=0;
          while(i<q&&Aux->Ciclos>0)
          {
            getch();
            system("cls");
            printf("\n\n                   BLOQUE DE CONTROL DE PROCESOS (PCB)");
            printf("\n\n -------------------------------------------RONDA %d------------------------------------------",j+1);
            printf("\n----------------------********J%dP%d se ejecuta en memoria*********---------------------------",Aux->Jt,Aux->Pagina);

            if(Aux->Interrupcion>=0&&Aux->Interrupcion<5&&Aux->Inicio_Sc==i)
            {
              Aux2=Aux->sig;
              vector(Aux->Interrupcion);
              Aux=Aux2;
              drop=1;
              break;
            }else if(Aux->Interrupcion>32)
            {
              Aux->Edo=4;
              Aux2=Aux->sig;

              semaforo();
              Aux=Aux2;
              drop=1;
            }
            else
            {
              Aux->Edo=3;
              Aux->Ciclos--;
              Aux->Seccion_critica++;
              i++;
              Aux2=Aux;
              ver_lista();
              drop=0;
            }
          }
          sum+=i;
          if(drop==0)
          {
            if(Aux->Ciclos>0)
            {
              Aux->Edo=4;

              Aux2=Aux;
              getch();
              system("cls");
              printf("\n TAREA EN ESPERA");
              ver_lista();
              Aux=Aux2;
            }
            else
            {
              Aux->Edo=5;

              getch();
              system("cls");
              printf("TAREA TERMINADA");
              Aux2=Aux;

              ver_lista();
              Aux=Aux2;
            }
            Aux=Aux->sig;
          }
        }
      }
      rat = 0;
      Aux = PtrLista;
      while(Aux!=NULL)
      {
        if(Aux->Edo!=5)
        {
          rat=1;
          break;
        }
        Aux=Aux->sig;
      }
      ver_lista();
  }
}//end function Algoritmo RoundRobin

void vector(int v)
{
  system("cls");
  printf("Interrupcion %d \n descripcion: ", v);
  switch(v)
  {
   case 0:
    printf("\n #DE Divide error \n Tipo: Fault\n  Error code: \n fuente: DIV and IDIV instructions \n");
    break;

    case 1:
    printf("\n #BD RESERVED \n Tipo: Fault/Trap \n Error code: No \n fuente: For INTEL use only \n");
    break;

    case 2:
    printf("\n - NMI Interrupcion \n Tipo: interrupt \n Error code: No \n Fuente: Nonmaskable external interrupt \n");
    break;

    case 3:
    printf("\n #BP Breakpoint \n Tipo: Trap \n Error code: No \n Fuente: INT 3 instruction");
    break;

    case 4:
    printf("#OF Overflow\n Tipo: Trap \n Error code: No \n Fuente: INTO INSTRUCTION");
    break;
  }
  //delete node

  eliminar();
  getch();
  system("cls");
}//end function

void eliminar()
{
  if(Aux == PtrLista)
  {
    PtrLista = Aux->sig;
    delete Aux;
    //si la lista queda vacia acutliza el puntero al final
    if(PtrLista == NULL)
    {
      QrryLista = NULL;
    }
  }else
   {
     //buscar el nodo anterior al nodo a eliminar
     Lista* anterior = PtrLista;
     while(anterior->sig != Aux)
     {
       anterior = anterior->sig;
     }
     //conectar el nodo anterior con el siguiente, saltandose el nodo a eliminar
     anterior->sig = Aux->sig;
     // si el nodo actual es el ultimo a eliminar actualizamos el puntero a eliminar
     if(Aux==QrryLista)
     {
       QrryLista = anterior;
     }
     //drop node
     delete Aux;
   }
}//end function eliminar


void semaforo()
{
  //copiamos el nodo
  if(PtrSm == NULL)
  {
    PtrSm = (Semaforo *)malloc(sizeof(Semaforo));
    PtrSm->Jt= Aux->Jt;
    PtrSm->Pagina = Aux->Pagina;
    PtrSm->Tiempo = Aux->Tiempo;
    PtrSm->Ciclos = Aux->Ciclos;
    PtrSm->Edo = Aux->Edo;
    PtrSm->Interrupcion = Aux->Interrupcion;
    PtrSm->Seccion_critica = Aux->Seccion_critica;
    PtrSm->Duracion = Aux->Duracion;
    PtrSm->Inicio_Sc = Aux->Inicio_Sc;
    PtrSm->sig_semaforo=NULL;
    QrrySm = PtrSm;
  }
  else
  {
    NuevoPtrSm = (Semaforo *)malloc(sizeof(Semaforo));
    NuevoPtrSm->Jt= Aux->Jt;
    NuevoPtrSm->Pagina = Aux->Pagina;
    NuevoPtrSm->Tiempo = Aux->Tiempo;
    NuevoPtrSm->Ciclos = Aux->Ciclos;
    NuevoPtrSm->Edo = Aux->Edo;
    NuevoPtrSm->Interrupcion = Aux->Interrupcion;
    NuevoPtrSm->Seccion_critica = Aux->Seccion_critica;
    NuevoPtrSm->Duracion = Aux->Duracion;
    NuevoPtrSm->Inicio_Sc = Aux->Inicio_Sc;
    NuevoPtrSm->sig_semaforo = NULL;
    QrrySm->sig_semaforo = NuevoPtrSm;
    QrrySm = NuevoPtrSm;
  }

  //eliminamos de la tabla original
  eliminar();
  Aux3 = Aux;
  ver_lista();
  Aux=Aux3;

  AuxSm = PtrSm;

  printf("\n \n  SEMAFORO");

  while(AuxSm != NULL)
  {
    printf("\n J%dP%d     %d       %d          %d         %d         %d         %d         %d ", AuxSm->Jt, AuxSm-> Pagina, AuxSm->Tiempo, AuxSm->Ciclos, AuxSm->Edo, AuxSm->Inicio_Sc, AuxSm->Duracion, AuxSm->Interrupcion);
    AuxSm = AuxSm->sig_semaforo;
  }
  printf("\n Entro \n");
}//end function semaforo
