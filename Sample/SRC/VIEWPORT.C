/* viewport.c */
/*
 * This procedure sets up the variables for the translation of plotter
 * coordinates to PostScript coordinates.
 *
 * Note: the procedure "defaults" may be incorporated here, however
 *	I have not had the time to work it out properly.
 *
 * Don McCormick
 */
#include "defn.h"
/*  original psxmax */
#define XWIDTH 0.90

viewport()
{
    /* original values for A4 */
    /* float pagewidth = 197.0;		 Page width for Laser Printer  */
    /* float pageheight = 280.0;	 Page height for Laser Printer */
    /* float pwoffset = 12; */
    /* float phoffset = 12; */

    /*  8.5 x 11 inch paper */
    float pagewidth = 200.0;		/* Page width for Laser Printer */
    float pageheight = 265.0;		/* Page height for Laser Printer */
    float pwoffset = 28;
    float phoffset = 6;
    /* values above selected empirically to match HP7550A plot -G.J. */

    /* made global */
    /* float psxmax, psymax;		Sizes scaled to the viewport */

    if (LANDSCAPE)		/* Default mode */
    {
	psymax = pagewidth * XWIDTH;
	psxmax = psymax * (xmax - xmin)/ (ymax - ymin);
	xoffset += (pageheight + phoffset - psxmax) / 2.0;
	yoffset -= (pagewidth + pwoffset + psymax) / 2.0;
	printf("90 rotate\n"); 
    } else
    {
	psxmax = pagewidth * XWIDTH;
	psymax = psxmax * (ymax - ymin) / (xmax - xmin);
	xoffset += (pagewidth + pwoffset - psxmax) / 2.0;
	yoffset += (pageheight + phoffset - psymax) / 2.0;
    }
    printf("%g mm %g mm translate\n", xoffset, yoffset);
    XSCALE = psxmax / (xmax - xmin) * SCALE;
    YSCALE = psymax / (ymax - ymin) * SCALE;
    /* fprintf(stderr,"Xscale = %g  Yscale = %g\n",XSCALE,YSCALE); */
}

/* function called when the HP-GL Scale command is received */
/* Modifies the X,Y SCALE factors and the origin offsets */
/*  Added by Gordon Jacobs */

modify_viewport()
{
    /* re-calculate scale parameters */
    XSCALE = psxmax / (xmax - xmin) * SCALE;
    YSCALE = psymax / (ymax - ymin) * SCALE;

    /* calculate new offset */
    offX = -xmin * XSCALE;
    offY = -ymin * YSCALE;

    /*** debug
    fprintf(stderr,"MODIFY: Xscale = %g  Yscale = %g\n",XSCALE,YSCALE);
    fprintf(stderr,"OFFSET: offX = %g  offY = %g\n",offX,offY);
    **********/
}
