#include "cini_core.h"

void CINI_newline();

void CINI_print_bool(bool b);
void CINI_print_int(int n);
void CINI_print_float(float f);
void CINI_print_string(char *s);
void CINI_print_char(char c);

#define CINI_print(x)							\
  ({									\
    if (__builtin_types_compatible_p( typeof(x), int ))			\
      CINI_print_int( (int) x);						\
    else if(__builtin_types_compatible_p( typeof(x), char * ))		\
      CINI_print_string( (char *) x);					\
    else if(__builtin_types_compatible_p( typeof(x), char[] ))		\
      CINI_print_string( (char *) x);					\
    else if(__builtin_types_compatible_p( typeof(x), char ))		\
      CINI_print_char( (char) x );					\
    else								\
      printf("<erreur: " #x ">\n");					\
  })

int CINI_read_int();
float CINI_read_float();
char CINI_read_char();
/* char *CINI_read_string(); */

#define CINI_read(x)						\
  ({								\
    typeof(x) tmp;						\
    if (__builtin_types_compatible_p( typeof(x), int ))		\
      tmp = CINI_read_int();					\
    else if(__builtin_types_compatible_p( typeof(x), char ))	\
      tmp = CINI_read_char();					\
    else							\
      printf("<erreur: " #x ">\n");				\
    x = tmp;							\
  })

#ifdef NO_DEBUG
#define CINI_was_here() {}
#endif

#ifndef NO_DEBUG
#define CINI_was_here()							\
  ({									\
    if(strcmp(__FUNCTION__,""))						\
      fprintf(stderr,							\
	      "Debug: appel à partir de ligne %d, %s (fonction '%s').\n", \
	      __LINE__, __FILE__, __FUNCTION__);			\
    else                                                                \
      fprintf(stderr,							\
	      "Debug: appel à partir de la ligne %d du fichier %s.",	\
	      __LINE__, __FILE__);					\
  })
#endif

int CINI_random(int min, int max);

#define CINI_round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

