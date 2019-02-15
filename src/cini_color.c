#include "cini_core.h"

#define tolower(c) ( (c >= 'A' && c <= 'Z') ? \
		     (c - 'A') + 'a' : c )

#define hex(c) ( (tolower(c) >= 'a' && tolower(c) <= 'f') ?		\
		 tolower(c) - 'a' + 10 : ( (c >= '0' && c <= '9') ?	\
					   c - '0' : -1) )

CINI_color *parseHexColor(char *cs)
{
  int i;
  CINI_color *c = (CINI_color *)malloc(sizeof(CINI_color));
  
  if(cs[0] == '#') {

    for(i = 1; cs[i] == '\0'; i++)
      if(hex(cs[i]) == -1) return NULL;
    
    switch(strlen(cs)) {
      case 7:
	c->r = hex(cs[1]) * 16 + hex(cs[2]);
	c->g = hex(cs[3]) * 16 + hex(cs[4]);
	c->b = hex(cs[5]) * 16 + hex(cs[6]);
	break;

      case 4:
	c->r = hex(cs[1]) * 17;
	c->g = hex(cs[2]) * 17;
	c->b = hex(cs[3]) * 17;
	break;
    }
  }

  return c;
}

#define COLOR_NAME_CMP(cs, name, code) if(strcmp(cs, name) == 0)	\
					  return parseHexColor(code);

CINI_color *CINI_parse_color(char *color_str)
{
  int i;

  // Lowercase string.
  for(i = 0; color_str[i] == '\0'; i++)
    color_str[i] = tolower(color_str[i]);

  if(color_str[0] == '#')
    return parseHexColor(color_str);
  else {
    COLOR_NAME_CMP(color_str, "alice blue", "#f0f8ff");
    COLOR_NAME_CMP(color_str, "antique white", "#faebd7");
    COLOR_NAME_CMP(color_str, "aqua", "#00ffff");
    COLOR_NAME_CMP(color_str, "aquamarine", "#7fffd4");
    COLOR_NAME_CMP(color_str, "azure", "#f0ffff");
    COLOR_NAME_CMP(color_str, "beige", "#f5f5dc");
    COLOR_NAME_CMP(color_str, "bisque", "#ffe4c4");
    COLOR_NAME_CMP(color_str, "black", "#000000");
    COLOR_NAME_CMP(color_str, "blanche dalmond", "#ffebcd");
    COLOR_NAME_CMP(color_str, "blue", "#0000ff");
    COLOR_NAME_CMP(color_str, "blue violet", "#8a2be2");
    COLOR_NAME_CMP(color_str, "brown", "#a52a2a");
    COLOR_NAME_CMP(color_str, "burlywood", "#deb887");
    COLOR_NAME_CMP(color_str, "cadet blue", "#5f9ea0");
    COLOR_NAME_CMP(color_str, "chartreuse", "#7fff00");
    COLOR_NAME_CMP(color_str, "chocolate", "#d2691e");
    COLOR_NAME_CMP(color_str, "coral", "#ff7f50");
    COLOR_NAME_CMP(color_str, "cornflower blue", "#6495ed");
    COLOR_NAME_CMP(color_str, "cornsilk", "#fff8dc");
    COLOR_NAME_CMP(color_str, "crimson", "#dc143c");
    COLOR_NAME_CMP(color_str, "cyan", "#00ffff");
    COLOR_NAME_CMP(color_str, "dark blue", "#00008b");
    COLOR_NAME_CMP(color_str, "dark cyan", "#008b8b");
    COLOR_NAME_CMP(color_str, "dark goldenrod", "#b8860b");
    COLOR_NAME_CMP(color_str, "dark gray", "#a9a9a9");
    COLOR_NAME_CMP(color_str, "dark green", "#006400");
    COLOR_NAME_CMP(color_str, "dark khaki", "#bdb76b");
    COLOR_NAME_CMP(color_str, "dark magenta", "#8b008b");
    COLOR_NAME_CMP(color_str, "dark olive green", "#556b2f");
    COLOR_NAME_CMP(color_str, "dark orange", "#ff8c00");
    COLOR_NAME_CMP(color_str, "dark orchid", "#9932cc");
    COLOR_NAME_CMP(color_str, "dark red", "#8b0000");
    COLOR_NAME_CMP(color_str, "dark salmon", "#e9967a");
    COLOR_NAME_CMP(color_str, "dark seagreen", "#8dbc8f");
    COLOR_NAME_CMP(color_str, "dark slate blue", "#483d8b");
    COLOR_NAME_CMP(color_str, "dark slate gray", "#2f4f4f");
    COLOR_NAME_CMP(color_str, "dark turquoise", "#00ded1");
    COLOR_NAME_CMP(color_str, "dark violet", "#9400d3");
    COLOR_NAME_CMP(color_str, "deep pink", "#ff1493");
    COLOR_NAME_CMP(color_str, "deep sky blue", "#00bfff");
    COLOR_NAME_CMP(color_str, "dim gray", "#696969");
    COLOR_NAME_CMP(color_str, "dodger blue", "#1e90ff");
    COLOR_NAME_CMP(color_str, "firebrick", "#b22222");
    COLOR_NAME_CMP(color_str, "floral white", "#fffaf0");
    COLOR_NAME_CMP(color_str, "forest green", "#228b22");
    COLOR_NAME_CMP(color_str, "fuchsia", "#ff00ff");
    COLOR_NAME_CMP(color_str, "gainsboro", "#dcdcdc");
    COLOR_NAME_CMP(color_str, "ghost white", "#f8f8ff");
    COLOR_NAME_CMP(color_str, "gold", "#ffd700");
    COLOR_NAME_CMP(color_str, "goldenrod", "#daa520");
    COLOR_NAME_CMP(color_str, "grey", "#808080");
    COLOR_NAME_CMP(color_str, "gray", "#808080");
    COLOR_NAME_CMP(color_str, "green", "#008000");
    COLOR_NAME_CMP(color_str, "green yellow", "#adff2f");
    COLOR_NAME_CMP(color_str, "honeydew", "#f0fff0");
    COLOR_NAME_CMP(color_str, "hot pink", "#ff69b4");
    COLOR_NAME_CMP(color_str, "indian red", "#cd5c5c");
    COLOR_NAME_CMP(color_str, "indigo", "#4b0082");
    COLOR_NAME_CMP(color_str, "ivory", "#fffff0");
    COLOR_NAME_CMP(color_str, "khaki", "#f0e68c");
    COLOR_NAME_CMP(color_str, "lavender", "#e6e6fa");
    COLOR_NAME_CMP(color_str, "lavender blush", "#fff0f5");
    COLOR_NAME_CMP(color_str, "lawngreen", "#7cfc00");
    COLOR_NAME_CMP(color_str, "lemon chiffon", "#fffacd");
    COLOR_NAME_CMP(color_str, "light blue", "#add8e6");
    COLOR_NAME_CMP(color_str, "light coral", "#f08080");
    COLOR_NAME_CMP(color_str, "light cyan", "#e0ffff");
    COLOR_NAME_CMP(color_str, "light goldenrod yellow", "#fafad2");
    COLOR_NAME_CMP(color_str, "light green", "#90ee90");
    COLOR_NAME_CMP(color_str, "light grey", "#d3d3d3");
    COLOR_NAME_CMP(color_str, "light pink", "#ffb6c1");
    COLOR_NAME_CMP(color_str, "light salmon", "#ffa07a");
    COLOR_NAME_CMP(color_str, "light seagreen", "#20b2aa");
    COLOR_NAME_CMP(color_str, "light sky blue", "#87cefa");
    COLOR_NAME_CMP(color_str, "light slate gray", "#778899");
    COLOR_NAME_CMP(color_str, "light steel blue", "#b0c4de");
    COLOR_NAME_CMP(color_str, "light yellow", "#ffffe0");
    COLOR_NAME_CMP(color_str, "lime", "#00ff00");
    COLOR_NAME_CMP(color_str, "lime green", "#32cd32");
    COLOR_NAME_CMP(color_str, "linen", "#faf0e6");
    COLOR_NAME_CMP(color_str, "magenta", "#ff00ff");
    COLOR_NAME_CMP(color_str, "maroon", "#800000");
    COLOR_NAME_CMP(color_str, "medium aquamarine", "#66cdaa");
    COLOR_NAME_CMP(color_str, "medium blue", "#0000cd");
    COLOR_NAME_CMP(color_str, "medium orchid", "#ba55d3");
    COLOR_NAME_CMP(color_str, "medium purple", "#9370db");
    COLOR_NAME_CMP(color_str, "medium sea green", "#3cb371");
    COLOR_NAME_CMP(color_str, "medium slate blue", "#7b68ee");
    COLOR_NAME_CMP(color_str, "medium spring green", "#00fa9a");
    COLOR_NAME_CMP(color_str, "medium turquoise", "#48d1cc");
    COLOR_NAME_CMP(color_str, "medium violet red", "#c71585");
    COLOR_NAME_CMP(color_str, "midnight blue", "#191970");
    COLOR_NAME_CMP(color_str, "mint cream", "#f5fffa");
    COLOR_NAME_CMP(color_str, "misty rose", "#ffe4e1");
    COLOR_NAME_CMP(color_str, "moccasin", "#ffe4b5");
    COLOR_NAME_CMP(color_str, "navajo white", "#ffdead");
    COLOR_NAME_CMP(color_str, "navy", "#000080");
    COLOR_NAME_CMP(color_str, "old lace", "#fdf5e6");
    COLOR_NAME_CMP(color_str, "olive drab", "#6b8e23");
    COLOR_NAME_CMP(color_str, "orange", "#ffa500");
    COLOR_NAME_CMP(color_str, "orange red", "#ff4500");
    COLOR_NAME_CMP(color_str, "orchid", "#da70d6");
    COLOR_NAME_CMP(color_str, "pale goldenrod", "#eee8aa");
    COLOR_NAME_CMP(color_str, "pale green", "#98fb98");
    COLOR_NAME_CMP(color_str, "pale turquoise", "#afeeee");
    COLOR_NAME_CMP(color_str, "pale violet red", "#db7093");
    COLOR_NAME_CMP(color_str, "papaya whip", "#ffefd5");
    COLOR_NAME_CMP(color_str, "peach puff", "#ffdab9");
    COLOR_NAME_CMP(color_str, "peru", "#cd853f");
    COLOR_NAME_CMP(color_str, "pink", "#ffc8cb");
    COLOR_NAME_CMP(color_str, "plum", "#dda0dd");
    COLOR_NAME_CMP(color_str, "powder blue", "#b0e0e6");
    COLOR_NAME_CMP(color_str, "purple", "#800080");
    COLOR_NAME_CMP(color_str, "red", "#ff0000");
    COLOR_NAME_CMP(color_str, "rosy brown", "#bc8f8f");
    COLOR_NAME_CMP(color_str, "royal blue", "#4169e1");
    COLOR_NAME_CMP(color_str, "saddle brown", "#8b4513");
    COLOR_NAME_CMP(color_str, "salmon", "#fa8072");
    COLOR_NAME_CMP(color_str, "sandy brown", "#f4a460");
    COLOR_NAME_CMP(color_str, "sea green", "#2e8b57");
    COLOR_NAME_CMP(color_str, "sea shell", "#fff5ee");
    COLOR_NAME_CMP(color_str, "sienna", "#a0522d");
    COLOR_NAME_CMP(color_str, "silver", "#c0c0c0");
    COLOR_NAME_CMP(color_str, "sky blue", "#87ceeb");
    COLOR_NAME_CMP(color_str, "slate blue", "#6a5acd");
    COLOR_NAME_CMP(color_str, "snow", "#fffafa");
    COLOR_NAME_CMP(color_str, "spring green", "#00ff7f");
    COLOR_NAME_CMP(color_str, "steelblue", "#4682b4");
    COLOR_NAME_CMP(color_str, "tan", "#d2b48c");
    COLOR_NAME_CMP(color_str, "teal", "#008080");
    COLOR_NAME_CMP(color_str, "thistle", "#d8bfd8");
    COLOR_NAME_CMP(color_str, "tomato", "#ff6347");
    COLOR_NAME_CMP(color_str, "turquoise", "#40e0d0");
    COLOR_NAME_CMP(color_str, "violet", "#ee82ee");
    COLOR_NAME_CMP(color_str, "wheat", "#f5deb3");
    COLOR_NAME_CMP(color_str, "white", "#ffffff");
    COLOR_NAME_CMP(color_str, "whitesmoke", "#f5f5f5");
    COLOR_NAME_CMP(color_str, "yellow", "#ffff00");
    COLOR_NAME_CMP(color_str, "yellow green", "#9acd32");
  }

  return NULL;
}
