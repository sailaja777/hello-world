/* plotdot.c */
/*
 * Plot a dot or symbol on the paper 
 */
#include "defn.h"

plotdot(type)
char   *type;
{
    end_draw();

    while (SIGNED_NUMERIC)
    {
	xval = getval() * XSCALE;
	yval = getval() * YSCALE;
	if (type == RMOVE)
	{
	    absX += xval;
	    absY += yval;
	} else
	if (type == MOVE)
	{
	    absX = xval + offX;
	    absY = yval + offY;
	} else
	{
	    fprintf(stderr, "Error: expecting move command not %s\n", type);
	    exit(1);
	}

	if (SYMBOL)
	    printf("%g %g 5 %g (%c) Text\n", absX, absY, char_angle, symbl);
    	else if (SETDOT)
	{
    	    printf("newpath\n");
    	    printf("  %g %g %s %g %g %s\n", absX, absY, MOVE, absX, absY, DRAW);
	    printf("stroke\n");
	}
    }
}
