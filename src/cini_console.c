#include "cini_console.h"

void CINI_print_bool(bool b) {
    if (b == false)
        printf("false");
    else
        printf("true");
}

void CINI_print_int(int n) {
    printf("%d", n);
    fflush(stdout);
}

void CINI_print_float(float f) {
    printf("%f", f);
    fflush(stdout);
}

void CINI_print_string(char *s) {
    printf("%s", s);
    fflush(stdout);
}

void CINI_print_char(char c) {
    printf("%c", c);
    fflush(stdout);
}

void CINI_newline() {
    CINI_print_string("\n");
}

int CINI_read_int() {
    int cpt = 0;
    int n = 0;
    int ok = 1;
    int signe = 1;
    int first = 1;
    char c;
    /* on lit caractère par caractère jusqu'à la fin de la ligne */
    while ((c = (char)getchar()) != '\n') {
        cpt++;
        if ((c >= '0') && (c <= '9'))
            n = n * 10 + (c - '0');
            /* cas du signe (seulementau début) */
        else {
            if (first && (c == '-')) {
                signe = -1;
            } else {
                /* sortie erreur */
                ok = 0;
                break;
            }
        }
        first = 0;
    }
    /* si on a tapé qqch qui ressemble à un entier */
    if (ok && (cpt > 0))
        return n * signe;
    else {
        fprintf(stderr, "CINI: Erreur dans la lecture du nombre\n");
        exit(1);
    }
}

/* CINI_read_float n'est pas capable de lire les exposants : il ne parse que les notations décimales */
float CINI_read_float() {
    char chaine[100];
    int i = 0;
    int ok = 1;
    int first = 1;
    int point = 0;
    while ((chaine[i] = (char)getchar()) != '\n') {
        /* on ne veut que des 0-9 ... */
        if ((chaine[i] < '0') || (chaine[i] > '9')) {
            /* ... sauf : au début le signe, ... */
            if ((chaine[i] != '-') || (!first)) {
                /* ... ou en cours : un seul point */
                if ((chaine[i] == '.') && (point == 0)) {
                    point = 1;
                } else {
                    ok = 0;
                    break;
                }
            }
        }
        first = 0;
        i++;
    }
    /* si on n'a pas tapé qqch qui ressemble à un flottant */
    if ((!ok) || first) {
        fprintf(stderr, "CINI: Erreur dans la lecture du nombre\n");
        exit(1);
    } else {
        float f;
        chaine[i] = 0;
        f = strtof(chaine, NULL);
        return f;
    }
}

char CINI_read_char() {
    char c = (char)getchar();
    if (getchar() == '\n')
        return c;
    else {
        fprintf(stderr, "CINI: Trop de caractères fournis\n");
        exit(1);
    }
}

/*
char *CINI_read_string()
{
  char *str = malloc(sizeof(char) * 30);
  scanf("%s", str);
  return str;
}
*/

int CINI_random(int min, int max) {
    static int premiere_fois = true;
    if (premiere_fois) {
        premiere_fois = false;
        srandom(time(NULL));
    }
    return min + ((int)random() % (max - min + 1));
}
