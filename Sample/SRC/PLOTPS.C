/* plotps.c */
#include "defn.h"

#define MAXDRAWPOINTS	100

plotps(type)
char   *type;
{
    if (type == MOVE || type == RMOVE)
    {
	while (SIGNED_NUMERIC)
	{
	    if (type == MOVE)
	    {
		end_draw();
		absX = lastXmove = getval() * XSCALE + offX;
		absY = lastYmove = getval() * YSCALE + offY;
	    } else
	    if (type == RMOVE)
	    {
		end_draw();
		lastXmove = absX += getval() * XSCALE ;
		lastYmove = absY += getval() * YSCALE ;
	    }
	}
    }
    else			/* Must be a DRAW or RDRAW */
    {
	while (SIGNED_NUMERIC)
	{
	    if (dcount++ >= MAXDRAWPOINTS)
	    {
		end_draw();
		printf("newpath\n");
		printf("  %g %g %s\n", absX, absY, MOVE);
		DRAW_FLAG = 1;
		/* fprintf(stderr, "Warning exceeded %d draw points\n",
			  MAXDRAWPOINTS); */
	    }
	    xval = getval() * XSCALE;
	    yval = getval() * YSCALE;
	    if (!DRAW_FLAG)
	    {
		printf("newpath\n");
		printf("  %g %g %s\n", absX, absY, MOVE);
		DRAW_FLAG = 1;
	    }
	    if (type == RDRAW)
	    {
		absX += xval;
		absY += yval;
		printf("  %g %g %s\n", xval, yval, RDRAW);
	    } else
	    if (type == DRAW)
	    {
		absX = xval + offX;
		absY = yval + offY;
		printf("  %g %g %s\n", absX, absY, DRAW);
	    } else
	    {
		fprintf(stderr, "Error: expecting draw command not %s\n", type);
		exit(1);
	    }
	}
    }
}
