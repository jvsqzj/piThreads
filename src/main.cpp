
#include "definiciones.cpp"
#include <pthread.h>
#include <ncurses.h>

int main(){
    int N;
    cout << "Cuantos Threads desea ejecutar?\n";
    cin >> N;                                           //  entrada del teclado en version de prueba
    pthread_t my_thread[N+1];           //                             
    struct piArguments argArray[N];     //  Aqui estan los valores que se deben imprimir y el progreso tambien
    
    bool pausa;
    pausa = false;
    



    int i;
    for (i = 1; i <= N; i++){
        int wu;
        printf("Cuantas unidades de trabajo desea para el thread #%i?\n",i);
        cin >> wu; 
        argArray[i].iteraciones = wu*50;
        argArray[i].pausa = &pausa;
    }
    
    for (i = 1; i <= N; i++){
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
    noecho();
    //int max_x, max_y;

    //getmaxyx(w, max_y, max_x);
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
    }

  
    

    while(ciclo==true){
        
        captura=getch();
        nodelay(stdscr, true);
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
    

        for (i = 1; i <= N; i++){
            const char* prog = doubleToStr(argArray[i].progreso);
            move(2*i,6);
            printw("%.2f",argArray[i].progreso);
            move(2*i,20);

            if (argArray[i].progreso < 10)
            {
            

                printw("..........");
                //(ACS_DIAMOND);
                
                    
            }

            else if (argArray[i].progreso < 20 && argArray[i].progreso > 10)
            {
            

                printw("*.........");
                //(ACS_DIAMOND);
                
                    
            }

            else if (argArray[i].progreso < 30 && argArray[i].progreso > 20)
            {
            

                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                printw("**........");
                    
            }

            else if (argArray[i].progreso < 40 && argArray[i].progreso > 30)
            {
            
                printw("***.......");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND);
                    
            }

            else if (argArray[i].progreso < 50 && argArray[i].progreso > 40)
            {
            
                printw("****.......");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                    
            }

            else if (argArray[i].progreso < 60 && argArray[i].progreso > 50)
            {
            
                printw("*****.....");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); 
                    
            }

            else if (argArray[i].progreso < 70 && argArray[i].progreso > 60)
            {
            
                printw("*******...");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                    
            }

            else if (argArray[i].progreso < 80 && argArray[i].progreso > 70)
            {
            
                printw("********..");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND);
                    
            }

            else if (argArray[i].progreso < 90 && argArray[i].progreso > 80)
            {
            
                printw("*********.");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);


                    
            }


            else
            {
            
                printw("**********");
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); //addch(ACS_DIAMOND);
                //addch(ACS_DIAMOND); addch(ACS_DIAMOND);
                    
            }
        //const char* valor = doubleToStr(argArray[i].resultado);
        move(2*i, 50);
        printw("%.22f", argArray[i].resultado);
        refresh();
        }
    }
    

    
    /* Finalizar ncurses. Esto es necesario para volver al modo estandar de
     * la terminal */
    endwin ();


    pthread_exit(NULL);
    
}