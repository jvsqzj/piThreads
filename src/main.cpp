
#include "definiciones.cpp"
#include <pthread.h>
#include <ncurses.h>

int main(){
    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;                                           //  entrada del teclado en version de prueba
    pthread_t my_thread[N+1];           //                             
    struct piArguments argArray[N];     //  Aqui estan los valores que se deben imprimir y el progreso tambien
    
    bool pausa;
    pausa = true;
    

    int i;
    for (i = 1; i <= N; i++){
        argArray[i].pausa = &pausa;
        argArray[i].iteraciones = i*50;
        int ret = pthread_create(&my_thread[i], NULL, &piThread, (void*) &argArray[i]);    //  Crea un hilo y pasa por parametro el valor de la variable "pies"
        if (ret != 0){
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);                         
        }
    }

    char captura;
    bool ciclo=true;
    char *tecla;

    // //  Esto se va a ir
    // int print = pthread_create(&my_thread[N+1], NULL, &printArray, (void*) &argArray);
    // if (print != 0){
    //     printf("Error: pthread_create() failed\n");
    //     exit(EXIT_FAILURE);                         
    // }

    //  Aqui va lo grafico
    WINDOW *w;
    initscr ();
    int max_x, max_y;

    getmaxyx(w, max_y, max_x);
    move(1, 0);
    printw("Hilo");
    move(1, 20);
    printw("Estado");

    move(1, 40);
    printw("Valor");
    //int espacio = max_y/N;
    //printw("%i", espacio);
    for (i = 1; i <= N; i++){
        move(2*i, 1);
        printw("%i", i);

        while (progreso < 10 && progreso > 0)
        {
            move(2*i, 20);
        }

        while (progreso < 20 && progreso > 10)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND);
        }

        while (progreso < 30 && progreso > 20)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
        }

        while (progreso < 40 && progreso > 30)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); 
        }

        while (progreso < 50 && progreso > 40)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
        }

        while (progreso < 60 && progreso > 50)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); 
        }

        while (progreso < 70 && progreso > 60)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
        }

        while (progreso < 80 && progreso > 70)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND);
        }

        while (progreso < 90 && progreso > 80)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
        }

        while (progreso < 100 && progreso > 90)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND);
        }

        while (progreso == 100)
        {
            move(2*i, 20);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
            addch(ACS_DIAMOND); addch(ACS_DIAMOND);
        }
    }




    while(ciclo==true){
       captura=getch();
       cbreak();

       if(captura==80 || captura==112){
          //printw ("Sistema pausado\n");
          pausa=true;
          tecla = &captura;
       }

       else if(captura==82 || captura==114){
          //printw ("Sistema Reiniciado\n");
          pausa=false;
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