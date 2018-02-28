
#include "definiciones.cpp"
#include <pthread.h>

int main(){
    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;                                           //  entrada del teclado en version de prueba
    pthread_t my_thread[N+1];                           
    struct piArguments argArray[N];
    char* tecla;
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

    int print = pthread_create(&my_thread[N+1], NULL, &printArray, (void*) &argArray);
    if (print != 0){
        printf("Error: pthread_create() failed\n");
        exit(EXIT_FAILURE);                         
    }

    pthread_exit(NULL);
    
}