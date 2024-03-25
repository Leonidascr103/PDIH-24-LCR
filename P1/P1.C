#include <stdio.h>
#include <dos.h>

#define INVISIBLE 0
#define NORMAL 1
#define GRUESO 2

unsigned char cfondo=4;
unsigned char ctexto=1;

// Función para colocar el cursor en una posición determinada
void gotoxy(int x, int y){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.bh = 0x00; // Página 0
    inregs.h.dh = y;
    inregs.h.dl = x;
    int86(0x10, &inregs, &outregs);
    return;
}

// Función para fijar el aspecto del cursor
void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor) {
        case INVISIBLE:
            inregs.h.ch = 010;
            inregs.h.cl = 000;
            break;
        case NORMAL:
            inregs.h.ch = 010;
            inregs.h.cl = 010;
            break;
        case GRUESO:
            inregs.h.ch = 000;
            inregs.h.cl = 010;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

// Función para fijar el modo de video deseado
void setvideomode(int mode){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = mode;
    int86(0x10, &inregs, &outregs);
    return;
}

// Función para obtener el modo de video actual
int getvideomode(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}

// Función para modificar el color de primer plano
void textcolor(int ctexto, int cfondo,char caracter){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;    //una funcion más general debe recibir el caracter a imprimir
    inregs.h.bl = cfondo << 4 | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10,&inregs,&outregs);
    return;
}

// Función para borrar toda la pantalla
void mi_clrscr(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Función para escribir un carácter en pantalla con el color actual
void cputchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl = cfondo << 4 | ctexto; // Color de fondo negro (predeterminado)
    inregs.h.bh = 0x00; // Página 0
    inregs.x.cx = 0x01; // Número de repeticiones
    int86(0x10, &inregs, &outregs);
    return;
}

// Función para obtener un carácter de teclado y mostrarlo en pantalla
char getche() {
     union REGS inregs, outregs;
     int caracter;
     inregs.h.ah = 1;
     int86(0x21, &inregs, &outregs);
     caracter = outregs.h.al;
     return caracter;
}

void mi_putchar(char c){
     union REGS inregs, outregs;
     inregs.h.ah = 2;
     inregs.h.dl = c;
     int86(0x21, &inregs, &outregs);
     return;
}

// hace una pausa
void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}


// Función para dibujar un recuadro en modo texto
void draw() {
    gotoxy(10, 1); printf("(\\(\\       /\\");
    gotoxy(10, 2); printf("(^=U=^) o/  |");
    gotoxy(10, 3); printf("o_('')('')  |");
    gotoxy(10, 4); printf("---------------");
    gotoxy(10, 5); printf("xXxXXxXXXXXxxXXxx"); 
}


void write_color_message(int x, int y, char text_color, char bg_color, char *message) {
    int offset;
    char far *scrn = (char far *)0xB8000000;

    char attr = (bg_color << 4) | (text_color & 0x0F); // Combine los colores del texto y del fondo en un solo byte de atributo

    offset = ((y * 80 + x) * 2) + (0 * 0x1000);
    while (*message) {
        scrn[offset] = *message;
        ++offset;
        scrn[offset] = attr;
        ++offset;
        ++message;
    }
}

void draw_box(int x1, int y1, int x2, int y2, int fg_color, int bg_color) {
    int x, y;
    for (y = y1; y <= y2; y++) {
        for (x = x1; x <= x2; x++) {
            if (y == y1 || y == y2 || x == x1 || x == x2) {
                gotoxy(x, y);
                textcolor(fg_color,bg_color,'*');
            }
        }
    }
}

/*
// pone un pixel en la coordenada X,Y de color C
void pixel(int x, int y, BYTE C){
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}
*/


void draw_fish_skewers() {

    // Cabeza del pez
    gotoxy(10, 5);
    printf("<*");


    // Cuerpo del pez
    gotoxy(13, 5);
    printf("))/))/");

    gotoxy(19, 5);
    printf("><");

    // Cabeza del pez
    gotoxy(10, 7);
    printf("<*");

    // Cuerpo del pez
    gotoxy(13, 7);
    printf("))/))/");

    gotoxy(19, 7);
    printf("><");

    // Cabeza del pez
    gotoxy(10, 9);
    printf("<*");

    // Cuerpo del pez
    gotoxy(13, 9);
    printf("))/))/");

    gotoxy(19, 9);
    printf("><");

    // Cabeza del pez
    gotoxy(15, 4);
    printf("I");

    // Cuerpo del pez
    gotoxy(15, 6);
    printf("|");

    gotoxy(15, 8);
    printf("|");

    gotoxy(15, 10);
    printf("|");

/*
    for(int i=10; i<21; i++){
      pixel(i,12, 4);
    }
*/
}

void draw_homer() {
    // Linea 1
    gotoxy(10, 10);
    printf("  ___");

    // Linea 2
    gotoxy(8, 11);
    printf(" //_\\\\_");

    // Linea 3
    gotoxy(6, 12);
    printf(".\"\\  \".");

    // Linea 4
    gotoxy(5, 13);
    printf("/        \\");

    // Linea 5
    gotoxy(4, 14);
    printf("|         \\_");

    // Linea 6
    gotoxy(4, 15);
    printf("|     ,--.-.)");

    // Linea 7
    gotoxy(5, 16);
    printf("\\   /  o \\o\\");

    // Linea 8
    gotoxy(3, 17);
    printf("/\\/\\  \\    /_/");

    // Linea 9
    gotoxy(2, 18);
    printf(" (_.   `--'__)");

    // Linea 10
    gotoxy(3, 19);
    printf("  |     .-'  \\");

    // Linea 11
    gotoxy(3, 20);
    printf("  |  .-'.     )");

    // Linea 12
    gotoxy(3, 21);
    printf("  | (  _/--.-'");

    // Linea 13
    gotoxy(3, 22);
    printf("  |  `.___.'");

    // Linea 14
    gotoxy(15, 23);
    printf("(");
}

int main() {
    int tmp; //variable temporal para guardar el caracter pulsado.
    int current_mode; //variable para guardar el modo de video actual.
    char *message = "Hola Mundo!"; //Mensaje para colorear.
    //Colores del texto a colorear
    char text_color = 0x0A; // Verde
    char bg_color = 0x01; // Azul oscuro

    //Colores del recuadro
    int fg_color_box = 14; // Amarillo
    int bg_color_box = 1;  // Azul 

    //Función para limpiar ventana
    mi_clrscr();

    //Funcion para establecer el modo de video
    setvideomode(1);

    // Funcion para obtener el modo de video actual.
    current_mode = getvideomode();

    //Funcion para posicionar el cursor en la pantalla.
    gotoxy(10, 8);

    printf("Modo de video actual: %d\n", current_mode);

    //Función para escribir el mensaje en una posición específica con un atributo de color específico
    write_color_message(10, 1, text_color, bg_color, message);

    gotoxy(10, 12);
    printf("Pulsa una tecla: ");

    //Función para establecer el tipo del cursor
    setcursortype(2);

    //Funcion para obtener el codigo de tecla pulsado
    tmp = getche();

    gotoxy(12, 14);
    printf("\nHas pulsado: ");

    //Función para mostrar la letra pulsada
    cputchar((char)tmp);
    mi_putchar((char)tmp);

    //Función para pausar la ejecución, usado para ver los resultados sin que el programa termine
    pausa();

    mi_clrscr();

    //Función para dibujar un art spray en ascii
    draw(); // Dibujar 
    gotoxy(60, 12);
    setcursortype(1);
    printf("Buena Pesca!");
    pausa();

    mi_clrscr(); 
    setvideomode(3);
    current_mode = getvideomode();
    printf("Modo de video actual: %d\n", current_mode);

    //Funcion que dibujar un rectángulo dando solo las posiciones de 2 esquinas opuestas y colores para los bordes
    draw_box(20, 5, 50, 20, fg_color_box, bg_color_box);
    pausa();

    mi_clrscr(); 
    gotoxy(10, 1);
    setvideomode(4);
    current_mode = getvideomode();
    printf("Modo de video actual: %d\n", current_mode);

    //Función para dibujar en modo gráfico 
    draw_fish_skewers();
    pausa();

    mi_clrscr();
    draw_homer();
    pausa();

    setvideomode(3);
    return 0;
}

