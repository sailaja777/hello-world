/* userdefchar.c */
/*
 * userdefchar(type)
 *
 * function for handling the USER DEFINED CHARACTER (UC) command
 * in Hewlett-Packard Graphics Language (HP-GL).
 *
 * Written by Gerald William Kokodyniak B.A.Sc. M.A.Sc.
 * University of Toronto, Department of Mechanical Engineering
 *
 * Heavily modified by Gordon Jacobs, University of Calif, Berkeley
 *  Now scales user character size to that of regular characters
 *  Orients user character the same as regular characters
 *  Linewidth chosed to always be 0.25mm to better match
 *  postscript font.
 *
 */

#include "defn.h"
#define MAXDRAWPOINTS	100

/* standard resolution user-def character pen control numbers */
/*     for enhanced, change to -9999,9999 */
#define PENUPCTL -99.0
#define PENDNCTL  99.0

/* linewidth in mm for user defined characters */
#define DEFCHAR_LINEWIDTH 0.25

/* Scaling parameters */
#define CHAR_CELL_H  5.0
#define CHAR_CELL_W  2.5

userdefchar()
{
    float   number, rad, angl;
    float   theMagnitude(), theAngle();
    PENDOWN = 0;
    printf("%g mm setlinewidth\n", DEFCHAR_LINEWIDTH);

    while (SIGNED_NUMERIC)
    {
	number = getval();
	if (number >= PENDNCTL) {
	    PENDOWN = 1;
	    number = getval();
	}
        else if (number <= PENUPCTL) {
	    PENDOWN = 0;
	    number = getval();
	}

        if (number < PENDNCTL && number > PENUPCTL) {
	    if (PENDOWN) {
	        if (dcount++ >= MAXDRAWPOINTS) {
		    end_draw();
		    printf("newpath\n");
		    printf("  %g %g %s\n", absX, absY, MOVE);
		    DRAW_FLAG = 1;
	        }
	        xval = number / CHAR_CELL_W * char_width * XSCALE;
	        yval = getval() / CHAR_CELL_H * char_height * YSCALE;
	        if (!DRAW_FLAG) {
		    printf("newpath\n");
		    printf("  %g %g %s\n", absX, absY, MOVE);
		    DRAW_FLAG = 1;
	        }
		/* perform rotation */
		rad = theMagnitude(xval,yval);
		angl = theAngle(xval,yval);
		angl += char_angle * deg_rad;
		xval =  rad *cos(angl);
		yval =  rad *sin(angl);
		absX += xval;
	        absY += yval;
	        printf("  %g %g %s\n", xval, yval, RDRAW);
            } else {
		end_draw();
		xval = number  / CHAR_CELL_W * char_width *XSCALE;
		yval = getval() / CHAR_CELL_H * char_height * YSCALE;

		rad = theMagnitude(xval,yval);
		angl = theAngle(xval,yval);
		angl += char_angle * deg_rad;

	        lastXmove = absX += rad * cos(angl);
	        lastYmove = absY += rad * sin(angl);
	    }
	}
	else {
	    if(number >= PENDNCTL)
		PENDOWN = 1;
	    else if(number <= PENUPCTL)
		PENDOWN = 0;
	}
    }
    PENDOWN = 0;
    end_draw();
    /* move a fraction of a space so next character doesn't abutt */
    absX += 0.2 * char_space * cos(char_angle * deg_rad);
    absY += 0.2 * char_space * sin(char_angle * deg_rad);
    printf("%g mm setlinewidth\n", pen_size[pen_number]);
}

float
theMagnitude(x,y)
float x,y;
{
    return( sqrt(x*x + y*y) );
}

float
theAngle(x,y)
float x,y;
{
    if(x != 0.0)
	return(atan(y/x));
    else
	return((y > 0.0) ? M_PI_2 : (M_PI + M_PI_2));
}
