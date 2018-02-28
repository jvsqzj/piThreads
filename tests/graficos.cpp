#include <ncurses.h>

//using namespace std;

void dibuja_barra(int pos_y) 
  {
    int a;
    for (a=0; a<10; a++)
      {
        move (pos_y,a); printw(" ");
      }
  }

int main()
{
  WINDOW *w;  //  ventana es un puntero llamado w
  int tecla;  //  entero tecla
  int max_x, max_y, pos_x, pos_y; //  enteros de la pantalla
  bool fin = false;   //  booleano fin igual a falso

  w = initscr();    //  inicia la pantalla
  keypad(w, TRUE);  /*  habilita el teclado del usuario
                    TRUE indica que el usuario puede
                    presionar una tecla y wgetch()retorna
                    un simple valor representando la tecla
                    de funcion*/

  noecho();     //  cancela el echo
  nonl();       /*  curses es capaz de hacer mejor uso de la
                    linea de alimentacion, resultando en un
                    movimiento de cursor mas rapido*/

  curs_set(0);  /*  fija la apariencia del cursor basado en
                    el valor de visibilidad*/
  erase();      //  borra los elementos de una espec. posicion

  getmaxyx(w, max_y, max_x);  /*  Almacena el inicio de las
                              coordenadas y delimita el size 
                              de la pantalla */

  pos_x = max_x / 2;  //  Tanto 'x' como 'y' son la mitad del
  pos_y = max_y / 2;  //  valor maximo

  bkgd(COLOR_PAIR(1)); 
  attron(COLOR_PAIR(2)); 

  dibuja_barra(max_y);
  
  do  //  haga
  {
        move(pos_y, pos_x); //  mueve el cursor a esa posicion
        addch('@');         //  coloca el arroba
        refresh();          //  obtenemos la salida actual de
                            //  la terminal

    tecla = getch();  //  tecla es igual a la funcion getch

        move(pos_y, pos_x);
        addch(' ');
        refresh();

        switch(tecla)   //  tecla es evaluada
        {
          case 27: // tecla ESC
             fin = true;  //  el booleano cambia
             break;       //  se termina el programa
        }
  }  while (!fin);
  endwin(); //  Restaura la terminal despues de la actividad
            //  de curses
  return 0;
}

