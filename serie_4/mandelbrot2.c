#include <stdio.h>
#include <stdlib.h>

#define SCALE 555
#define XOFFSET 20
#define YOFFSET (842-555)/2


int color_table[96];

int iterate(double x, double y);

/**
 * Schreibt eine Datei mit einen Abbild der Mandelbrotmenge in eine Postscript Datei.
 * Bedeutung der Eingangsparameter:
 *   f        Zeiger auf Datei, diese muss fürs Schreiben geöffnet sein
 *   rows     Anzahl der Zeilen des plots
 *   columns  Anzahl der Spalten des plots
 *   a        Anfang des  real teils  von z = x + i*y;
 *   b        Ende des real teils von z = x + i*y;
 *   c        Anfang des Imaginärteils von z = x + i*y;
 *   d        Ende des Imaginärteils  von z = x + i*y.
 */
void write_postscript_plot(FILE *f, int rows, int columns, double a, double b, double c, double d);


int main(int argc, char *argv[]) {
    int interactive = 0; /* set to 1 for interactive version */
    int rows, columns;
    double a, b, c, d;
    char filename[80];
    FILE *outputfile;

    if (interactive == 1) {
        printf("Give the number of rows : ");
        scanf("%d", &rows);
        printf("Give the number of columns : ");
        scanf("%d", &columns);
        printf("Give the lower bound for x : ");
        scanf("%lf", &a);
        printf("Give the upper bound for x : ");
        scanf("%lf", &b);
        printf("Give the lower bound for y : ");
        scanf("%lf", &c);
        printf("Give the upper bound for y : ");
        scanf("%lf", &d);
        printf("Give the name of the output file : ");
        scanf("%s", filename);
        outputfile = fopen(filename, "w");
        printf("See the file %s for results...\n", filename);
    } else {
        rows = 1000;
        columns = 2000;
        a = -1.5;
        b = 0.5;
        c = -1.00;
        d = 1.00;
        outputfile = fopen("mandelbrot.ps", "w");
    }
    write_postscript_plot(outputfile, rows, columns, a, b, c, d);
    fclose(outputfile);

    return 0;
}

void init_color_table() {
    int cases[6 * 3] = {0, 1, 2,
                        0, 2, 1,
                        1, 2, 0,
                        1, 0, 2,
                        2, 1, 0,
                        2, 0, 1
    };
    int f[3];
    int counter = 0;
    int i, j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 16; j++) {
            f[cases[3 * i]] = 0;
            f[cases[3 * i + 1]] = 255;
            f[cases[3 * i + 2]] = 255 - (256 / 16) * j;
            color_table[counter++] = (f[0] << 16) | (f[1] << 8) | f[2];
        }
    }
}

void write_postscript_plot(
        FILE *f,
        int rows,
        int columns,
        double a,
        double b,
        double c,
        double d
) {
    int color, it;
    int i, j;
    double x, y;
    double dx = (b - a) / (columns - 1);
    double dy = (d - c) / (rows - 1);

    init_color_table();

    fprintf(f, "%%!PS\n");
    fprintf(f, "%%%%BoundingBox: 20 20 555 802\n");
    fprintf(f, "/picstr %d string def\n", rows * 3);
    fprintf(f, "%d %d translate\n", XOFFSET, YOFFSET);
    fprintf(f, "%d %d scale\n", SCALE, SCALE);
    fprintf(f, "%d %d %d\n", columns, rows, 8);
    fprintf(f, "[%d 0 0 -%d 0 %d]\n", columns, rows, rows);
    fprintf(f, "{currentfile picstr readhexstring pop}\n");
    fprintf(f, "false 3 colorimage\n");

    for (i = 0, y = d; i < rows; i++, y -= dy, fprintf(f, "\n")) {

        for (j = 0, x = a; j < columns; j++, x += dx) {
            it = iterate(x, y);
            color = (it == 0xfff) ? 0 : color_table[it % 96];
            fprintf(f, "%.6x", color);
        }

    }

    fprintf(f, "showpage\n");
}

int iterate(double x, double y) {
    double wx, wy, v, xx;
    int k = 0;

    wx = 0.0;
    wy = 0.0;
    v = 0.0;
    while ((v < 4.0) && (k++ < 0xffe)) {
        xx = wx * wx - wy * wy;
        wy = 2.0 * wx * wy;
        wx = xx + x;
        wy = wy + y;
        v = wx * wx + wy * wy;
    }

    return k;
}
