#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double pi(int n) {
    double sum = 0.0;
    int sign = 1;
    for (int i = 0; i < n; ++i) {           
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}


void *worker_thread(void *arg){
    printf("This is thread will calculate pi\n");
    double result = pi((long)arg);
    cout << setprecision(10) << result << endl;
    pthread_exit(NULL);
}


int main(){
    int N;
    cout << "How many units do you want to use?\n";
    cin >> N;
    pthread_t my_thread[50*N];
    double *pies [50*N];

    printf("In main: creating threads\n");   

    long id;
    for (id = 1; id <= 50*N; id++){
        int ret = pthread_create(&my_thread[id], NULL, &worker_thread, (void*)pies[id]);
        if (ret != 0){
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}

