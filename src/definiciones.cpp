
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>  //  libreria de manipulacion de decimales
#include <unistd.h>
#include <term.h>
#include <sstream>

using namespace std;



/*-----------------------------------------------------------------------------
                    piArguments es una estructura para                           
                    los argumentos de los threads que                            
                    calculan pi                                                  
-------------------------------------------------------------------------------

        Contiene los atributos:

        int iteraciones corresponde a los terminos de taylor
        que la función utilizará para calcular pi.

        bool pausa corresponde a una señal para detener el 
        calculo mientras se realiza la ejecucion del programa

        double progreso guardara que tanto ha avanzado el thread

        double resultado guardara el valor que se ha calculado
        hasta el momento
        
-----------------------------------------------------------------------------*/

struct piArguments {                            
    int iteraciones;
    bool* pausa;
    double progreso;    //  progreso para la barra. Convertirlo a entero por si acaso.
    double resultado;
};

/*-----------------------------------------------------------------------------
                    piThread es una funcion que ejecuta
                    el algoritmo de taylor que calcula pi                                                
-------------------------------------------------------------------------------

        La funcion se debe llamar con un argumento tipo 
        struct piArguments, ingresado por referencia
        
-----------------------------------------------------------------------------*/

void *piThread(void* arg){
    struct piArguments *data = (struct piArguments *) arg;
    //printf("Thread #%i \n", data->iteraciones/50);
    double suma = 0.0;
    double completado;
    int sign = 1;
    int n = data->iteraciones;
    int i = 0;
    while (i < n){
        usleep(10000);
        if (!*data->pausa){
            suma += 4*sign/(2.0*i+1.0);
            sign *= -1;
            data->resultado = suma;
            completado = (double)(i+1)/n;
            data->progreso = completado*100;
            i++;
//            printf("%f %c\n",data->progreso, '%');
        }
    }
    pthread_exit(NULL); 
}

const char* doubleToStr(double value){
    std::stringstream ss ;
    ss << value;
    const char* str = ss.str().c_str();
    return str;
}


/*--------------------------- Funciones de prueba -------------------------

*/
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

void *printArray(void* array){
    struct piArguments *data = (struct piArguments *) array;
    while (true){
        int i;
        for(i=1; i<30; i++){
            cout << setprecision(20) << data[i].resultado;
            cout << "   ";
            cout << data[i].progreso << endl;
        }
        usleep(1000);
        ClearScreen();
    }
}