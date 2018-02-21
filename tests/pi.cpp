#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>  //  libreria de manipulacion de decimales
#include <unistd.h>
#include <term.h>

using namespace std;    //  por defecto

void ClearScreen()
  {
  if (!cur_term)
    {
    int result;
    setupterm( NULL, STDOUT_FILENO, &result );
    if (result <= 0) return;
    }

  putp( tigetstr( "clear" ) );
  }

double pi(int n) {                      //  Variable tipo double que recibe a n
    double sum = 0.0;
    int sign = 1;
    for (int i = 0; i < n; ++i) {       //  ciclo for       
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}

struct threadArgs {
    int iteraciones;
    double results;
};

void *worker_thread(void *arg){                         //  funcion de los hilos
    struct threadArgs *data = (struct threadArgs *) arg;
    printf("This is thread will calculate pi with %i iterations\n", data->iteraciones);
    double result = pi(data->iteraciones);              //  toma el valor que tiene la funcion pi
    data->results = result;
    pthread_exit(NULL);                                 //  termina la llamada del hilo
}

void *printArray(void* array){
    struct threadArgs *data = (struct threadArgs *) array;
    while (true){
        int i;
        for(i=1; i<=20; i++){
            cout << setprecision(50) << data[i].results << endl;         //  trunca el valor a 10 digitos
        }
        ClearScreen();
    }
}


int main(){                                             //  programa principal
    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;                                           //  entrada del teclado
    pthread_t my_thread[N+1];                             //  tipo de tratado de hilo
    struct threadArgs argArray[N];
    printf("In main: creating threads\n");   

    int i;
    for (i = 1; i <= N; i++){
        argArray[i].iteraciones = i*50;
        int ret = pthread_create(&my_thread[i], NULL, &worker_thread, (void*) &argArray[i]);    //  Crea un hilo y pasa por parametro el valor de la variable "pies"
        if (ret != 0){
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);                         //  se sale del for
        }
    }

    int print = pthread_create(&my_thread[N+1], NULL, &printArray, (void*) &argArray);    //  Crea un hilo y pasa por parametro el valor de la variable "pies"
    if (print != 0){
        printf("Error: pthread_create() failed\n");
        exit(EXIT_FAILURE);                         //  se sale del for
    }

    pthread_exit(NULL);     //  termina la llamada del hilo
}
