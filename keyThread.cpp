#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>  //  libreria de manipulacion de decimales
#include <unistd.h>
#include <term.h>
#include <ncurses.h>

using namespace std;

struct piArguments{
     int iteraciones;
     bool pausa;
     double progreso;
     double resultado;
};

void *keyThread(void* arg){

     struct piArguments data;
     char captura;
     bool ciclo=true;
     char *tecla;

    /* Inicializar la operacion de ncurses */
    initscr ();

    while(ciclo==true){
       captura=getch();
       cbreak();

       if(captura==80 || captura==112){
          printw ("Sistema pausado\n");
          data.pausa=true;
          tecla = &captura;
       }

       else if(captura==82 || captura==114){
          printw ("Sistema Reiniciado\n");
          data.pausa=false;
          tecla = &captura;
       }
       else if(captura==83 || captura==115){
         ciclo=false;
         tecla=&captura;
       }
    }

    /* Finalizar ncurses. Esto es necesario para volver al modo estandar de
     * la terminal */
    endwin ();
    pthread_exit(NULL);
}

int main(){

    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;                                           //  entrada del teclado en version de prueba
    pthread_t hilo;
    char* tecla;

    int key = pthread_create(&hilo, NULL, &keyThread, NULL);
    if (key != 0){
       printf("Error: pthread_create() failed\n");
       exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);

}
