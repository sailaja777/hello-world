/* plotinit.c */
#include "defn.h"

plotinit()
{
    /*
     * Initialisation of PostScript plot macros 
     */
    MOVE = "M";
    RMOVE = "R";
    DRAW = "D";
    RDRAW = "I";

    LANDSCAPE = 1;		/* Display plot in Landscape mode */

    SCALE = 1;			/* Default Scale */

    PLOTABS = 1;		/* Absolute plot coordinates */

    PENDOWN = 0;		/* Penup */

    SETDOT = 0;			/* HP-GL only for linetype = 0 */

    SYMBOL = 0;			/* HP-GL only */

    FONT_H_MULT = 1.2;
    FONT_W_MULT = 3.6;		/* necessary for postscript fonts to match */
				/*  when using relative font sizing */
    /*
     *	   Default line/pen sizes (in mm)
     */
    pen_size[0] = 0.1;
    pen_size[1] = 0.2;
    pen_size[2] = 0.3;
    pen_size[3] = 0.4;
    pen_size[4] = 0.5;
    pen_size[5] = 0.7;
    pen_size[6] = 1.0;
    pen_size[7] = 1.25;
    pen_size[8] = 1.5;

    font = "Helvetica";		/* Default font */

    EOL = '\003';		/* End of line terminator default */

    /*
     * Default character specifications
     */
    char_angle = 0;		/* Degrees  */
    char_slant = 0;		/* tan(angle) */
    /* modified for larger defaults  GJ 
    char_height = 2.7;
    char_space = 0.8;
    char_width = 1.9;
    */ 
    char_height = 4.0;		/* mm */
    char_space = 1.2;		/* mm */
    char_width = 2.8;		/* mm */

    /*
     * Page offsets set to zero
     */
    xoffset = yoffset = 0;
    /*
     * Define degree to radian parameter
     */
    deg_rad = asin(1.0) / 90.0;
}
