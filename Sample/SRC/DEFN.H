/*
 *
 *	The following definations allow for the efficient 
 *	translation of DXY and RD-GL codes to PostScript code
 *
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define CR	'\015'
#define LF	'\012'
#define SPACE	'\040'

/* the definition below was modified by Gordon Jacobs to remove
 * the validity of a comma in a Signed Numeric quantity. The
 * definition below is more accurate and the comma is now removed
 * after reading the digit in getval()
 */
#define SIGNED_NUMERIC  (ungetc(( ch = getc(stream)),stream) != EOF ) &&\
		(((ch>='0') && (ch<='9')) || (ch=='-') || (ch=='+')\
		|| (ch==' ') || (ch == '.'))

#define CIRCLE	21		/* DXY Circle */
#define RCIRCLE 22		/* DXY Relative Circle */
#define CCIRCLE 23		/* DXY Centered Circle */
#define ACIRCLE 24		/* DXY Arc plus Circle */
#define SCIRCLE 25		/* DXY Segment Circle */
#define RDGLCIRCLE 26		/* RD-GL Circle */

#define TEXT	31
#define MARK	32

#define LINETYPE	41
#define LINESCALE	42
#define LINE_TYPE_SCALE	43

#define XTICK 0
#define YTICK 1
/*
 *	Files to open if any
 */
extern FILE	*stream;
extern FILE	*fopen();
/*
 *	Plotting Parameters that will contain the necessary PostScript
 *	commands to plot (see dxy2ps.c for the initialisation) and
 *	ps_macros.c for the plotting macros).
 */
extern char	*MOVE;
extern char	*RMOVE;
extern char	*DRAW;
extern char	*RDRAW;
/*
 *	Definition of "ch" used in SIGNED_NUMERIC
 */
extern char	ch;
/*
 *	Define the function getval() which returns a real number.
 */
extern float	getval();
/*
 *	Scaling parameters used for translation from DXY and RD-GL
 *	coordinate sytem to the PostScript coordinate system which
 *	has been defined in millimeters. (See above)
 */
extern float	SCALE;
extern float	XSCALE;
extern float	YSCALE;
extern float	xmax, xmin;
extern float	ymax, ymin;
extern float   psxmax,psymax;  /* max postscript dimensions */
extern float   tlp,tln;  	/* HP-GL tick length parameters */
extern float   FONT_H_MULT;    /* fudge factor for font height */
extern float   FONT_W_MULT;    /* fudge factor for font width */
/*
 *	End of line terminator (RD-GL / HP-GL)
 */
extern char	EOL;
/*
 *	PostScript Coordinate parameters
 */
extern float	lastXmove;
extern float	lastYmove;
extern float	absX;
extern float	absY;
extern float   offX,offY;   /* used for Scale command */
extern float	xval;
extern float	yval;
extern float	xoffset, yoffset;
/*
 *	Extra parameters
 */
extern float	char_angle;
extern float	char_height;
extern float	char_width;
extern float	char_space;
extern float	char_slant;

extern char	*font;

extern char	symbl;

extern int	dcount;
/*
 *	Degree radian conversion parameter ie: deg_rad = asin(1) / 90.0;
 *	( Defined in dxy2ps.c or rdgl2ps.c )
 */
extern float	deg_rad;
/*
 *	Line / pen size parameter (max 9 sizes)
 */
extern float	pen_size[9];
extern int     pen_number;
/*
 *	Paper size (ie A3 or A4) and Mode (HPGL or DXY)
 */
extern char	*PaperSize;
extern char	*Mode;
/*
 *	Flags
 */
extern int	LANDSCAPE;
extern int	DRAW_FLAG;
extern int	PLOTABS;
extern int	PENDOWN;
extern int	SETDOT; 	/* HP-GL commands only */
extern int	SYMBOL;		/* HP-GL commands only */
