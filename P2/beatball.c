#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 50000
int P_MAXIMA=0;

void colorearBloque(int color, int y, int x) {
    attron(COLOR_PAIR(color));
    mvprintw(y, x, "########");
    attroff(COLOR_PAIR(color));
}

void mostrarControles() {
    int rows, cols;
    initscr();
    clear();

    refresh();
    getmaxyx(stdscr, rows, cols); 

    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(3));
    box(window, '|', '-');     

    attron(COLOR_PAIR(1)); // Color azul
    mvwprintw(window,1, 10, "Controles del juego Ball");
    attroff(COLOR_PAIR(2)); 
    mvwprintw(window,5, 10, ">Movimiento de la barra: Flecha_Izquierda / Flecha_Derecha => A / D");
    mvwprintw(window,3, 10, ">Iniciar Juego: '1' en el menú");
    mvwprintw(window,4, 10, ">Salir del juego en la partida: 'Q' o 'q'");
    mvwprintw(window,5, 10, ">Movimiento de la barra: Flecha_Izquierda / Flecha_Derecha => A / D");
    mvwprintw(window,6, 10, ">Sistema de puntuación:");
        mvwprintw(window,7, 10, "--Bloques Verdes = 1 punto");
        mvwprintw(window,8, 10, "--Bloques Amarillos = 2 puntos");
        mvwprintw(window,9, 10, "--Bloques Azules = 3 puntos");
        mvwprintw(window,10, 10,"--Bloques Rojos = 4 puntos");
    mvwprintw(window,12, 10, ">Objetivo: Destruye todos los bloques para ganar!");


    mvwprintw(window,15, 10, "Presiona cualquier tecla para volver al menu");
    mvwprintw(window,20, 10, "CREADO POR: Leon Corbacho Rodriguez");
    wrefresh(window);
    int opcion;
    while ((opcion = getch()) == ERR) {}
    usleep(DELAY);
    endwin();
}

void mostrarMenu(int contador) {
    int rows, cols;
    clear();
    getmaxyx(stdscr, rows, cols);
    //Título "BeatBall" en ASCII art
    attron(COLOR_PAIR(2)); // Color amarillo
    mvprintw(1, 25, " _____      _      _     ");
    mvprintw(2, 25, "|  __ \\    | |    | |    ");
    mvprintw(3, 25, "| |__)| _ _| |    | |    ");
    mvprintw(4, 25, "|  ___/ _` | |    | |    ");
    mvprintw(5, 25, "| |__)\\(_| | |___ | |___ ");
    mvprintw(6, 25, "|_|___/___ |_____||_____|");
    attroff(COLOR_PAIR(2));


    attron(COLOR_PAIR(1)); // Color verde
    mvprintw(9, 30, "1. Jugar");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3)); // Color azul
    mvprintw(11, 30, "2. Controles");
    attroff(COLOR_PAIR(3)); 

    attron(COLOR_PAIR(4)); // Color rojo
    mvprintw(13, 30, "3. Salir");
    attroff(COLOR_PAIR(4));


    if(contador > P_MAXIMA){
        P_MAXIMA = contador;
    }
    attron(COLOR_PAIR(2)); // Color rojo
    mvprintw(17, 27, "MAXIMA PUNTUACION: %d", P_MAXIMA);
    attroff(COLOR_PAIR(3));  

    //attron(COLOR_PAIR(0)); // Color rojo
    mvprintw(22, 20, "CREADO POR: Leon Corbacho Rodriguez");
    //attroff(COLOR_PAIR(0));  

    refresh();

    int opcion;
    while ((opcion = getch()) != '1' && opcion != '2' && opcion != '3') {}

    switch (opcion) {
        case '1':
            break; // Continuar al juego
        case '2':
            mostrarControles(); //Abrir la ventana de controles
            mostrarMenu(P_MAXIMA); // Volver al menú después de mostrar los controles
            break;
        case '3':
            endwin(); //Salir del programa
            exit(0);
    }
}

int main(int argc, char *argv[]) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    start_color();
    srand(time(NULL));

    // Inicializar colores
    init_pair(0, COLOR_WHITE,COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLUE, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_RED);

    int contador = 0;

    //Juego
    while (true) {

        int x = 5, y = 11; //Posicion inicial de la pelotita
        int max_y = 25, max_x = 80; //Maximo de los lados de rebote y delimiadores del juego
        int next_x = 0; //Sigiente posición de la pelotita en el eje x
        int directionx = 1; //direccion de la siguiente posición x de la pelotita
        int next_y = 0; //Sigiente posición de la pelotita en el eje y
        int directiony = 1; //direccion de la siguiente posición y de la pelotita
        int xc = 20, yc = 20; //Poscion inicial de la barra 
        int ch; //Variable para leer la tecla de movimiento de la barra

        bool perdedor = false; // variable para indicar que se ha perdido en el juego
        bool ganador = false; //variable para indicar que se ha ganado.

        bool bloques[80][10]; // Matriz para almacenar el estado de los bloques
        int bloques_colores[80][10]; // Matriz para almacenar el color de los bloques
        
        int contador_bloques=0;
        bool color_estatico = false;
        
        mostrarMenu(contador);
        
        contador = 0;

        // Inicializar matriz de bloques
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 10; ++j) {
                bloques[i][j] = true;
            }
        }

        do {
            clear();

            // Dibujar bloques
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 10; ++j) {
                    if (bloques[i][j] && color_estatico == false) {
                        int color = rand() % 4 + 1; // Escoge un color aleatorio
                        colorearBloque(color, i, j * 8);
                        bloques_colores[i][j] = color;
                    }
                    if (bloques[i][j] && color_estatico) {
                        colorearBloque(bloques_colores[i][j], i, j * 8);
                    }
                }
            }
            
            ch = getch();

            mvprintw(y, x, "o");
            mvprintw(yc, xc, "==========");
            mvprintw(22, 60, "Contador: %d", contador); // Imprimir el valor del contador en la posición (22, 30)

            refresh();

            //Pantalla de preparación para el jugador
            if(!color_estatico){
                    attron(COLOR_PAIR(1)); // Color verde
                    mvprintw(14, 35, "READY?");
                    mvprintw(15, 22, "Presiona 'A' o 'D' para empezar");
                    attroff(COLOR_PAIR(1));
                    char opcion;
                    while ((opcion = getch()) != 'a' && opcion != 'A' && opcion != 'd' && opcion != 'D') {}
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    attron(COLOR_PAIR(4)); // Color rojo
                    mvprintw(14, 30, "     GO     ");
                    attroff(COLOR_PAIR(4));
                    mvprintw(15, 22, "\n");
                    refresh();
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);
                    usleep(DELAY);

            }

            color_estatico = true; //Color de los bloques ya han sido elegidos

            switch (ch) {
                case KEY_LEFT:
                case 'a':
                case 'A':
                    xc -= 5;
                    break;

                case KEY_RIGHT:
                case 'd':
                case 'D':
                    xc += 5;
                    break;
            }

            next_x = x + directionx;
            next_y = y + directiony;

            if (next_x >= max_x || next_x < 0) {
                directionx *= -1;
            } else {
                x += directionx;
            }

            if (next_y >= max_y || next_y < 0) {
                directiony *= -1;
                if (next_y >= max_y) {
                    perdedor = true; //La pelota ha llegado al fondo => Ha perdido
                }
            } else {
                y += directiony;
            }

            if (xc < 0) {
                xc = 0;
            }
            if (xc > 70) {
                xc = 70;
            }

            // Colisión con la barra
            if (next_x >= (xc - 2) && next_x <= (xc + 10) && next_y == yc - 1) {
                directiony *= -1;
                if (next_x < (xc + 3)) {
                    directionx *= -1;
                } else if(next_x > (xc + 10)){
                    directionx *= +1;
                }
            }

            // Colisión con los bloques
            int block_x = next_x / 8;
            int block_y = next_y;
            if (block_y >= 0 && block_y < 6 && block_x >= 0 && block_x < 10) {
                if (bloques[block_y][block_x]) {
                    bloques[block_y][block_x] = false;
                    directiony *= -1;
                if (next_x < (block_x * 8) + 4) {
                    // Si el centro de la pelota está a la izquierda del centro del bloque
                directionx = -1;
                } else {
                    // Si el centro de la pelota está a la derecha del centro del bloque
                    directionx = 1;
                    }
                    switch(bloques_colores[block_y][block_x]){
                    case 1: //Si el bloque es Verde
                        contador+=1;
                        break;
                    case 2: //Si el bloque es Amarillo
                        contador+=2;
                        break;
                    case 3: //Si el bloque es Azul
                        contador+=3;
                        break;
                    case 4: //Si el bloque es Rojo
                        contador+=4;
                        break;
                    }
                    contador_bloques++;              
                }
            }

            if(contador_bloques == 60){ //Si destruyes todos los bloques => Ganaste!
                ganador= true;
            }

            usleep(DELAY);

        } while ((ch != 'q' && ch != 'Q') && !perdedor && !ganador);

        endwin();

        // Mostrar ventana de resultado
        WINDOW *result_win;
        result_win = newwin(6, 30, (max_y - 5) / 2, (max_x - 30) / 2);
        box(result_win, 0, 0);
        if (perdedor) {
            mvwprintw(result_win, 2, 10, "¡Perdiste!");
        } else if(ganador) {
            mvwprintw(result_win, 2, 10, "¡Ganaste!");
        }
        else{
            mvwprintw(result_win, 2, 10, "!X____X!");
        }
        mvwprintw(result_win, 3, 8, "Puntuacion: %d", contador);

        if(contador > P_MAXIMA && contador > 0){
            mvwprintw(result_win, 4, 10, "NEW RECORD!");
        }
        wrefresh(result_win);

        sleep(3); // Espera 3 segundos antes de salir

        delwin(result_win);
    }

    return 0;
}
