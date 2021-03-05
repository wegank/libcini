#include <cini.h>

int main() {
    CINI_print_string("Test\n");
    CINI_open_window(250, 100, "Test");
    CINI_fill_window("white");
    CINI_draw_disc(125, 50, 38, "red");
    CINI_draw_string(12, 30, "black", "Cini vous dit bonjour !" );
    CINI_loop();
    return 0;
}

