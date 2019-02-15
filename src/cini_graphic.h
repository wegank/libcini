#include "cini_core.h"

#ifndef FONTFILE
#define FONTFILE "font.ttf"
#endif

CINI_color *CINI_parse_color(char *color_str);

void CINI_open_display(int width, int height, uint32_t flags);
void CINI_open_window(int width, int height, string title);
void CINI_open_fullscreen(void);

void CINI_close_display();
void CINI_close_window();
void CINI_close_fullscreen();


bool CINI_check_pixel_color(int x, int y, string color);
bool CINI_check_pixel_color_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);


typedef int (*CINI_keyboard_delegate)(int keycode);

bool CINI_key_down(void);

void CINI_loop_with_keyboard(CINI_keyboard_delegate kd);
int CINI_loop_until_keydown();
int CINI_loop_until_keyup();
int CINI_loop_until_clic();
void CINI_loop(void);

/* get clic position */
unsigned int CINI_clic_posx();
unsigned int CINI_clic_posy();

void CINI_fill_window(string color);
void CINI_fill_rect(int x, int y, int w, int h, string color);

void CINI_draw_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);
void CINI_draw_pixel(int x, int y, string color);

void CINI_draw_line_rgb(int ax, int ay, int bx, int by,
			uint8_t r, uint8_t g, uint8_t b);

void CINI_draw_line(int ax, int ay, int bx, int by, string color);

void CINI_draw_disc(int x, int y, int rayon, string color);

void CINI_draw_string(int x, int y, string color, string str);

void CINI_draw_bool_table(int x, int y, bool tab[], int size, string bg_color, string fg_color);
void CINI_draw_int_table(int x, int y, int tab[], int size, string bg_color, string fg_color);
void CINI_draw_char_table(int x, int y, char tab[], int size, string bg_color, string fg_color);
void CINI_draw_float_table(int x, int y, float tab[], int size, string bg_color, string fg_color);

int RenderTextToScreen_Partial(char *fontname, char *color, char *text, int x, int y);

#ifndef NO_FUNCDEF
#define NO_FUNCDEF
int RenderTextToScreen(char *text, char *color, int x, int y)
{
#ifdef WIN32
  char *path = getenv ("CINIFONT");
  if (path != NULL && *path)
    return RenderTextToScreen_Partial(path, color, text, x, y);
  else
#endif
  return RenderTextToScreen_Partial(FONTFILE, color, text, x, y);
}
#endif
