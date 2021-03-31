#include "cini_graphic.h"
#include "font.h"

#ifdef __APPLE__

#include <SDL.h>
#include <SDL_ttf.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif


// global var used to memorize cursor position when clic

static unsigned int clic_posx;
static unsigned int clic_posy;

// SDL2 migration
static SDL_Window *window = NULL;

void CINI_open_display(int width, int height, Uint32 flags) {
    // Initialize SDL 2D display component.

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr,
                "Erreur: ne peut pas initialiser le système graphique (\"%s\").\n",
                SDL_GetError());
        return;
    }


    // Make sure that SDL_Quit is executed upon exit (especially
    // important if running in fullscreen display).

    atexit(SDL_Quit);


    // Initialized windowed mode with given size and flags.

    window = SDL_CreateWindow("Default",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height, flags);

    // WIP: Enable key repeat
    //     (i.e.: when a key is kept down, the keyboard
    //            event is repeteadly triggered).

    // SDL1 : SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_INTERVAL / 4,
    //                     SDL_DEFAULT_REPEAT_DELAY / 12);

    // Start TTF engine.
    TTF_Init();
    atexit(TTF_Quit);
}

void CINI_open_fullscreen() {
    // Open fullscreen display in 640x480 resolution (anything else is
    // a bit of waste!).
    CINI_open_display(640, 480, SDL_SWSURFACE | SDL_RLEACCEL |
                                SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_FULLSCREEN);
}

void CINI_open_window(int width, int height, string title) {
    // Open window.
    CINI_open_display(width, height, SDL_SWSURFACE | SDL_RLEACCEL |
                                     SDL_RENDERER_PRESENTVSYNC);

    // Set caption.
    SDL_SetWindowTitle(window, title);
    // SDL1: SDL_WM_SetCaption(title, 0);
}


SDL_Surface *CINI_get_screen(void) {
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    if (screen == NULL) {
        fprintf(stderr, "Erreur: tentative d'appel à une primitives "
                        "de la bibliothèque graphique sans avoir appelé "
                        "'CINI_open_window' (ou une autre fonction d'initialisation "
                        "au préalable.\n");
        exit(-67);
    }

    return screen;
}


void CINI_close_display() {
    SDL_Quit();
}

void CINI_close_window() {
    CINI_close_display();
}

void CINI_close_fullscreen() {
    CINI_close_display();
}

bool CINI_key_down() {
    SDL_Event event;

    SDL_UpdateWindowSurface(window);
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                return true;
            default :
                return false;
        }
    }
    return false;
}

void CINI_loop_with_keyboard(CINI_keyboard_delegate kd) {
    SDL_Event event;
    int running = 1;

    // Redraw backbuffer.
    SDL_UpdateWindowSurface(window);

    while (running) {
        // Poll system for an event.
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // If the window has been closed, then stop the loop.
                case SDL_QUIT:
                    running = 0;
                    break;

                    // A key has been pressed.
                case SDL_KEYDOWN:

                    // Forward the keycode to the delegate, if it exists.
                    if (kd != NULL) {
                        if (kd(event.key.keysym.sym) == 0)
                            running = 0;

                        // User might have drawn something.
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(2);
                    }

                    // If ESC has been pressed, stop the loop.
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = 0;

                    break;
            }
        }

        // Let the system process other events (avoids 100% CPU).
        SDL_Delay(1);
    }
}

int CINI_loop_until_keydown() {
    SDL_Event event;

    // Redraw backbuffer.
    SDL_UpdateWindowSurface(window);

    while (1) {
        // Poll system for an event.
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // If the window has been closed, then stop the loop.
                case SDL_QUIT:
                    return -1;

                    // A key has been pressed.
                case SDL_KEYDOWN:
                    return event.key.keysym.sym;
            }
        }

        // Let the system process other events (avoids 100% CPU).
        SDL_Delay(1);
    }
}

// An unique event not depending on the time the key is pressed.
int CINI_loop_until_keyup() {
    SDL_Event event;

    // Redraw backbuffer.
    SDL_UpdateWindowSurface(window);

    while (1) {
        // Poll system for an event.
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // If the window has been closed, then stop the loop.
                case SDL_QUIT:
                    return -1;

                    // A key has been pressed.
                case SDL_KEYUP:
                    return event.key.keysym.sym;
            }
        }

        // Let the system process other events (avoids 100% CPU).
        SDL_Delay(1);
    }
}

// An unique event clic
int CINI_loop_until_clic() {
    SDL_Event event;

    // Redraw backbuffer.
    SDL_UpdateWindowSurface(window);

    while (1) {
        // Poll system for an event.
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // If the window has been closed, then stop the loop.
                case SDL_QUIT:
                    return -1;

                    // A mouse button have been pressed
                case SDL_MOUSEBUTTONDOWN:
                    clic_posx = event.button.x;
                    clic_posy = event.button.y;
                    return 0;
            }
        }

        // Let the system process other events (avoids 100% CPU).
        SDL_Delay(1);
    }
}

void CINI_loop(void) {
    // Simply a regular loop with no keyboard delegate to catch
    // keyboard input events (ESC is still polled, to allow user
    // to exit).

    CINI_loop_with_keyboard(NULL);
}

// Error message for invalid color
void CINI_error_color(char *color) {
    fprintf(stderr, "Error: \"%s\" is not a valid color\n", color);
}

// get clic position
//
unsigned int CINI_clic_posx() {
    return clic_posx;
}

unsigned int CINI_clic_posy() {
    return clic_posy;
}

int checkBoundaries(SDL_Surface *screen, int x, int y) {
    char *location = malloc(sizeof(char) * 32);

    int out_x = x >= screen->w ? 1 : (x < 0 ? -1 : 0);
    int out_y = y >= screen->h ? 1 : (y < 0 ? -1 : 0);
    int out = (out_x != 0 || out_y != 0);

    if (out_x == -1 && out_y == -1) strcpy(location, "en haut à gauche");
    else if (out_x == 0 && out_y == -1) strcpy(location, "en haut");
    else if (out_x == 1 && out_y == -1) strcpy(location, "en haut à droite");
    else if (out_x == 1 && out_y == 0) strcpy(location, "à droite");
    else if (out_x == 1 && out_y == 1) strcpy(location, "en bas à droite");
    else if (out_x == 0 && out_y == 1) strcpy(location, "en bas");
    else if (out_x == -1 && out_y == 1) strcpy(location, "en bas à gauche");
    else if (out_x == -1 && out_y == 0) strcpy(location, "à gauche");

    if (out)
        fprintf(stderr,
                "Warning: (%d, %d) -> la fenêtre fait %dx%d, le pixel sort %s.\n",
                x, y, screen->w, screen->h, location);

    /* Alexandre Michalon*/
    /* liberation de la memoire allouee a location */
    free(location);

    return out;
}

void *getPixMem(SDL_Surface *screen, int x, int y) {
    int bpp = screen->format->BytesPerPixel;
    return ((Uint8 *) screen->pixels + (y * screen->pitch) + x * bpp);
}

void putpixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color;
    SDL_Surface *screen = CINI_get_screen();


    // Check whether the pixel is in the screen boundaries.
    if (checkBoundaries(screen, x, y))
        return;


    color = SDL_MapRGB(screen->format, r, g, b);

    if (SDL_MUSTLOCK(screen)) {
        if (SDL_LockSurface(screen) < 0)
            return;
    }

    switch (screen->format->BytesPerPixel) {
        case 1:
            *((Uint8 *) getPixMem(screen, x, y)) = (Uint8) color;
            break;

        case 2:
            *((Uint16 *) getPixMem(screen, x, y)) = (Uint16) color;
            break;

        case 3: {
            Uint8 *pixmem = getPixMem(screen, x, y);

            Uint8 cb0 = (Uint8) (color & 0xff);
            Uint8 cb1 = (Uint8) ((color >> 8) & 0xff);
            Uint8 cb2 = (Uint8) ((color >> 16) & 0xff);

            pixmem[0] = cb2;
            pixmem[1] = cb1;
            pixmem[2] = cb0;
            break;
        }

        case 4:
            *((Uint32 *) getPixMem(screen, x, y)) = color;
            break;
    }

    if (SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);
}

bool CINI_check_pixel_color_rgb(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color;
    bool retval;
    SDL_Surface *screen = CINI_get_screen();


    // Check whether the pixel is in the screen boundaries.
    if (checkBoundaries(screen, x, y))
        return false;


    color = SDL_MapRGB(screen->format, r, g, b);

    if (SDL_MUSTLOCK(screen)) {
        if (SDL_LockSurface(screen) < 0)
            return false;
    }

    switch (screen->format->BytesPerPixel) {
        case 1:
            retval = (*((Uint8 *) getPixMem(screen, x, y)) == (Uint8) color);
            break;
        case 2:
            retval = (*((Uint16 *) getPixMem(screen, x, y)) == (Uint16) color);
            break;
        case 3: {
            Uint8 *pixmem = getPixMem(screen, x, y);

            Uint8 cb1 = (Uint8) ((color >> 8) & 0xff);
            Uint8 cb2 = (Uint8) ((color >> 16) & 0xff);

            retval = ((pixmem[0]) == cb2) && ((pixmem[1]) = cb1) && ((pixmem[2]) == cb1);

            break;
        }
        case 4:
            retval = (*((Uint32 *) getPixMem(screen, x, y)) == color);
            break;
    }

    if (SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);

    return retval;
}

bool CINI_check_pixel_color(int x, int y, string color) {
    CINI_color *c = CINI_parse_color(color);
    if (c != NULL)
        return CINI_check_pixel_color_rgb(x, y, c->r, c->g, c->b);
    else {
        CINI_error_color(color);
        return false;
    }
}


void CINI_draw_pixel_rgb(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    putpixel(x, y, r, g, b);
}

void CINI_draw_pixel(int x, int y, string color) {
    CINI_color *c = CINI_parse_color(color);
    if (c != NULL)
        putpixel(x, y, c->r, c->g, c->b);
    else
        CINI_error_color(color);
}

void drawline(int Ax, int Ay, int Bx, int By, Uint8 r, Uint8 g, Uint8 b) {

    // Implementation entirely poached from Kenny Hoff (95).

    int dX = abs(Bx - Ax);
    int dY = abs(By - Ay);

    int Xincr, Yincr;
    if (Ax > Bx) { Xincr = -1; } else { Xincr = 1; }
    if (Ay > By) { Yincr = -1; } else { Yincr = 1; }


    if (dX >= dY) {
        int dPr = dY << 1;
        int dPru = dPr - (dX << 1);
        int P = dPr - dX;

        for (; dX >= 0; dX--) {
            putpixel(Ax, Ay, r, g, b);
            if (P > 0) {
                Ax += Xincr;
                Ay += Yincr;
                P += dPru;
            } else {
                Ax += Xincr;
                P += dPr;
            }
        }
    } else {
        int dPr = dX << 1;
        int dPru = dPr - (dY << 1);
        int P = dPr - dY;

        for (; dY >= 0; dY--) {
            putpixel(Ax, Ay, r, g, b);
            if (P > 0) {
                Ax += Xincr;
                Ay += Yincr;
                P += dPru;
            } else {
                Ay += Yincr;
                P += dPr;
            }
        }
    }
}

void CINI_draw_line_rgb(int ax, int ay, int bx, int by,
                        Uint8 r, Uint8 g, Uint8 b) {
    drawline(ax, ay, bx, by, r, g, b);
}

void CINI_draw_line(int ax, int ay, int bx, int by, string color) {
    CINI_color *c = CINI_parse_color(color);
    if (c != NULL)
        drawline(ax, ay, bx, by, c->r, c->g, c->b);
    else
        CINI_error_color(color);
}

void CINI_fill_window(string color) {
    SDL_Surface *screen = CINI_get_screen();
    CINI_color *c = CINI_parse_color(color);
    Uint32 uint_color = SDL_MapRGB(screen->format, c->r, c->g, c->b);

    if (c != NULL)
        SDL_FillRect(screen, NULL, uint_color);
    else
        CINI_error_color(color);

}

/***************** Fonction ajoutee ******************************/

void CINI_draw_disc(int x, int y, int rayon, string color) {
    int vx, vy, r2;
    int distance2_N, distance2_O, distance2_NO;
    int ecart_N, ecart_O, ecart_NO;

    vx = x + rayon;
    vy = y;                /* les coordonnees du point de depart */
    r2 = rayon * rayon;

    do {

        /* affichage d'une ligne et de la ligne symetrique */
        CINI_draw_line(vx, vy, 2 * x - vx, vy, color);
        CINI_draw_line(vx, 2 * y - vy, 2 * x - vx, 2 * y - vy, color);

        /* calcul du carre des distances au centre pour les 3 candidats
           N = (vx, vy-1) O = (vx-1, vy) NO = (vx-1, vy-1)  centre = (x, y) */
        distance2_N = ((vx - x) * (vx - x)) + ((vy - 1 - y) * (vy - 1 - y));
        distance2_NO = ((vx - 1 - x) * (vx - 1 - x)) + ((vy - 1 - y) * (vy - 1 - y));
        distance2_O = ((vx - 1 - x) * (vx - 1 - x)) + ((vy - y) * (vy - y));

        /* qui a la distance au carre la plus proche de R2 ? */
        ecart_N = abs(r2 - distance2_N);
        ecart_NO = abs(r2 - distance2_NO);
        ecart_O = abs(r2 - distance2_O);

        if (ecart_O < ecart_N) {
            /* on va vers l'ouest */
            vx = vx - 1;
            if (ecart_NO < ecart_O) {
                /* et aussi vers le nord */
                vy = vy - 1;
            }
        } else {
            /* on va vers le nord */
            vy = vy - 1;
            if (ecart_NO < ecart_N) {
                /* et aussi vers l'ouest */
                vx = vx - 1;
            }
        }
    } while (vx >= x);
}

/*****************************************************************/

void CINI_fill_rect(int x, int y, int w, int h, string color)
/* remplit avec "color" un rectangle de dimensions width x height,
   dont le coin superieur gauche est en (x, y) */
{
    SDL_Surface *screen = CINI_get_screen();
    SDL_Rect rectangle = {x, y, w, h};
    CINI_color *c = CINI_parse_color(color);
    Uint32 uint_color = SDL_MapRGB(screen->format, c->r, c->g, c->b);

    if (c != NULL)
        SDL_FillRect(screen, &rectangle, uint_color);
    else
        CINI_error_color(color);

}

/*****************************************************************/

void blit_surface_to_screen(int x, int y, SDL_Surface *src) {
    SDL_Rect dstrect;
    SDL_Surface *screen = CINI_get_screen();

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = 0; // copy entire src surface
    dstrect.h = 0;

    SDL_BlitSurface(src, NULL, screen, &dstrect);
}

char digit(int i) {
    if ((0 <= i) && (i <= 9)) {
        return (char)('0' + i);
    }
    return '0';
}

/********************************************************/
char *sofi(int n) {
    int i, size, neg = 0;
    char *s;

    if (n < 0) {
        n = -n;
        neg = 1;
    }

    /* size = nb chiffres (n) + 1 (\0) + 1 (signe) */
    if (n == 0) {
        size = 3;
    } else {
        size = (int)ceil(log(n) / log(10)) + 2;
    }
    s = (char *) malloc(size * sizeof(char));
    s[size - 1] = '\0';
    i = size - 2;
    do {
        s[i] = digit(n % 10);
        n = n / 10;
        i--;
    } while (n > 0);

    if (neg) {
        s[i] = '-';
        return (s + i);
    }
    return (s + i + 1);
}

/********************************************************/
char *soff(float f) {
    int i, ent, dec, size, neg = 0;
    char *s;

    if (f < 0) {
        f = -f;
        neg = 1;
    }

    /* size = nb chiffres(E(f)) + 3 (virgule et partie decimale) + 1 (\0) + 1 (signe) */
    if (f == 0) {
        size = 6;
    } else {
        size = (int)ceil(logf(f) / log(10)) + 5;
    }
    s = (char *) malloc(size * sizeof(char));
    ent = (int)floorf(f);                  // partie entiere par valeur inferieure
    dec = (int)rintf((f - (float)ent) * 100);      // arrondi au plus proche. On garde 2 decimales
    s[size - 1] = '\0';
    i = size - 2;
    do {
        s[i] = digit(dec % 10);
        dec = dec / 10;
        i--;
    } while (dec > 0);
    s[i] = '.';
    i--;
    do {
        s[i] = digit(ent % 10);
        ent = ent / 10;
        i--;
    } while (ent > 0);

    if (neg) {
        s[i] = '-';
        return (s + i);
    }
    return (s + i + 1);
}

/********************************************************/

int RenderTextToScreen_Partial(char *fontname, char *color, char *text, int x, int y) {

    CINI_color *c = CINI_parse_color(color);
    if (c == NULL) {
        CINI_error_color(color);
        return 1;
    }
    SDL_Color TXT_Color;
    TXT_Color.r = c->r;
    TXT_Color.g = c->g;
    TXT_Color.b = c->b;
    SDL_Surface *TTF_Message;
    TTF_Font *font;

    if (fontname == NULL) {
        font = TTF_OpenFontRW(SDL_RWFromConstMem(bitmap, sizeof(bitmap)), 1, 24);
    } else {
        font = TTF_OpenFont(fontname, 24);
    }

    if (font == NULL) {
        fprintf(stderr, "Erreur: ne peut pas trouver la police '%s' (%s).\n",
                fontname,
                TTF_GetError());
    }

    if (!(TTF_Message = TTF_RenderText_Solid(font, text, TXT_Color))) {
        SDL_FreeSurface(TTF_Message);
        printf("Erreur: TTF_Message could not be blitted: returned 1 (%s).\n",
               TTF_GetError());
        return 1;
    }


    blit_surface_to_screen(x, y, TTF_Message);

    SDL_FreeSurface(TTF_Message);

    /* Alexandre Michalon */
    /* liberation de la memoire allouee a font */
    TTF_CloseFont(font);

    return 0;
}

void CINI_draw_string(int x, int y, string color, string str) {
    RenderTextToScreen(str, color, x, y);
}

void CINI_draw_int_table(int x, int y, int tab[], int size, string bg_color, string fg_color) {
    int i;
    int colw = 80, colh = 50;
    int xmarg = 5, ymarg = 5;

    CINI_fill_rect(x, y, size * colw, colh, bg_color);
    CINI_draw_line(x, y, x + (colw * size), y, fg_color);
    CINI_draw_line(x, y + colh, x + (colw * size), y + colh, fg_color);

    for (i = 0; i < size; i++) {
        CINI_draw_line(x + (colw * i), y, x + (colw * i), y + colh, fg_color);
        RenderTextToScreen(sofi(tab[i]), fg_color, x + (colw * i) + xmarg, y + ymarg);
    }
    CINI_draw_line(x + (colw * size), y, x + (colw * size), y + colh, fg_color);
}

/*************************** ATTENTION : FONCTION AJOUTEE ***********/
void CINI_draw_bool_table(int x, int y, const bool tab[], int size, string bg_color, string fg_color) {
    int i;
    int colw = 80, colh = 50;
    int xmarg = 5, ymarg = 5;

    CINI_fill_rect(x, y, size * colw, colh, bg_color);
    CINI_draw_line(x, y, x + (colw * size), y, fg_color);
    CINI_draw_line(x, y + colh, x + (colw * size), y + colh, fg_color);

    for (i = 0; i < size; i++) {
        CINI_draw_line(x + (colw * i), y, x + (colw * i), y + colh, fg_color);
        if (tab[i] == false)
            RenderTextToScreen("false", fg_color, x + (colw * i) + xmarg, y + ymarg);
        else
            RenderTextToScreen("true", fg_color, x + (colw * i) + xmarg, y + ymarg);
    }
    CINI_draw_line(x + (colw * size), y, x + (colw * size), y + colh, fg_color);
}

/*************************** ATTENTION : FONCTION MODIFIEE ***********/
void CINI_draw_char_table(int x, int y, const char tab[], int size, string bg_color, string fg_color) {
    int i;
    int colw = 80, colh = 50;
    int xmarg = 5, ymarg = 5;

    char *s = (char *) malloc(2 * sizeof(char));  // pour transformer un caractere en chaine
    s[1] = '\0';

    CINI_fill_rect(x, y, size * colw, colh, bg_color);
    CINI_draw_line(x, y, x + (colw * size), y, fg_color);
    CINI_draw_line(x, y + colh, x + (colw * size), y + colh, fg_color);

    for (i = 0; i < size; i++) {
        CINI_draw_line(x + (colw * i), y, x + (colw * i), y + colh, fg_color);
        s[0] = tab[i];
        RenderTextToScreen(s, fg_color, x + (colw * i) + xmarg, y + ymarg);
    }
    free(s);
    CINI_draw_line(x + (colw * size), y, x + (colw * size), y + colh, fg_color);
}

/********************************************************/
void CINI_draw_float_table(int x, int y, float tab[], int size, string bg_color, string fg_color) {
    int i;
    int colw = 80, colh = 50;
    int xmarg = 5, ymarg = 5;

    CINI_fill_rect(x, y, size * colw, colh, bg_color);
    CINI_draw_line(x, y, x + (colw * size), y, fg_color);
    CINI_draw_line(x, y + colh, x + (colw * size), y + colh, fg_color);

    for (i = 0; i < size; i++) {
        CINI_draw_line(x + (colw * i), y, x + (colw * i), y + colh, fg_color);
        RenderTextToScreen(soff(tab[i]), fg_color, x + (colw * i) + xmarg, y + ymarg);
    }
    CINI_draw_line(x + (colw * size), y, x + (colw * size), y + colh, fg_color);
}
