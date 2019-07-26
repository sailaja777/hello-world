/* plotcoords.c */
/*
 *	Define default maximum and minimum plotting coordinates.
 *		P1 (xmin, ymin),  P2 (xmax, ymax)
 *
 *	PaperSize can be:
 *			"A3" ISO (420mm by 297mm)
 *			"A4" ISO (297mm by 210mm)
 *			"A"  ANSI (11" by 8.5")
 *			"B"  ANSI (17" by 11")
 *
 *	Mode can be:	"HPGL" or "DXY"
 *
 * Don McCormick
 */

#include "defn.h"

plotcoords()
{
    if (strcmp(Mode, "HPGL") == 0)
    {
	if (strcmp(PaperSize, "A3") == 0)	/* HP-GL ISO A3 420mm * 297mm */
	{
	    xmax = 15200;
	    ymax = 10800;
	}
	else if(strcmp(PaperSize,"A4") == 0)	/* HP-GL ISO A4 297mm * 210mm */
	{
	    xmax = 10800;
	    ymax = 7680;
	}
	else if(strcmp(PaperSize,"A") == 0)	/* HP-GL ANSI A 11 * 8.5inch */
	{
	    xmax = 10000;
	    ymax = 7200;
	}
	else if(strcmp(PaperSize,"B") == 0)	/* HP-GL ANSI B 17 * 11inch */
	{
	    xmax = 15200;
	    ymax = 10000;
	}
	else 
	{
	    fprintf(stderr,"Illegal paper size\n");
	    exit(-1);
	}
    }
    else
    {
	if (strcmp(PaperSize, "A3") == 0)	/* DXY ISO A3 420mm * 297mm */
	{
	    xmax = 3800;
	    ymax = 2700;
	}
	else				/* DXY ISO A4 297mm * 210mm */
	{
	    xmax = 2700;
	    ymax = 1920;
	}
    }
    /* origin at zero,zero */
    xmin = ymin = 0.0;
    offX = offY = 0.0;
    /* default tick length percentage */
    tlp = tln = 0.005;
}
