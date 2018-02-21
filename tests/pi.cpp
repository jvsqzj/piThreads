#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>  //  libreria de manipulacion de decimales

using namespace std;    //  por defecto


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
    double *results;
};

void *worker_thread(void *arg){                         //  funcion de los hilos
    struct threadArgs *data = (struct threadArgs *) arg;
    printf("This is thread will calculate pi with %i iterations\n", data->iteraciones);
    double result = pi(data->iteraciones);              //  toma el valor que tiene la funcion pi
    data->results = &result;
    pthread_exit(NULL);                                 //  termina la llamada del hilo
}


int main(){                                             //  programa principal
    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;                                           //  entrada del teclado
    pthread_t my_thread[N];                             //  tipo de tratado de hilo
    double *pies [N];
    struct threadArgs argArray[N];

    printf("In main: creating threads\n");   

    int id;
    for (id = 1; id <= N; id++){
        argArray[N].iteraciones = id*50;
        argArray[N].results = pies[N];
        int ret = pthread_create(&my_thread[id], NULL, &worker_thread, (void*) &argArray[id]);    //  Crea un hilo y pasa por parametro el valor de la variable "pies"
        if (ret != 0){
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);                         //  se sale del for
        }
    }
    pthread_exit(NULL);     //  termina la llamada del hilo
    int i;
    for (i = 0; i <= N; id++){
        cout << setprecision(10) << pies[i] << endl;         //  trunca el valor a 10 digitos
    }
}
