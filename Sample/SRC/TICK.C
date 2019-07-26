/* tick.c */
/*
 * tick(type)
 *
 * function for handling the XT,YT commands 
 * in Hewlett-Packard Graphics Language (HP-GL).
 *
 * Written by Gordon Jacobs 
 * University of California, Berkeley , Dept of EECS.
 */


#include "defn.h"

tick(type)
int  type;
{
    float Xtlengthp,Xtlengthn,Ytlengthp,Ytlengthn;

    /* Compute tick lengths as a function of viewport dimensions */
    /* Xticks are in Y direction: */
    Xtlengthp = tlp * (ymax - ymin) * XSCALE; 
    Xtlengthn = tln * (ymax - ymin) * XSCALE; 
    /* Yticks are in X direction */
    Ytlengthp = tlp * (xmax - xmin) * YSCALE; 
    Ytlengthn = tln * (xmax - xmin) * YSCALE; 

    /* Ticks: Don't mess with position pointers,
     *   just use relative draw and move commands 
     */
    if (type == XTICK) {
	if(tlp != 0.0) {
		lastYmove = absY += Xtlengthp;
		printf("  %g %g %s\n",0.0,Xtlengthp,RMOVE);
		printf("  %g %g %s\n",0.0,-Xtlengthp,RDRAW);
	}
	if(tln != 0.0) {
		lastYmove = absY -= Xtlengthp;
		printf("  %g %g %s\n",0.0,-Xtlengthn,RMOVE);
		printf("  %g %g %s\n",0.0,Xtlengthn,RDRAW);
	}
    }
    else {
	if(tlp != 0.0) {
		lastXmove = absX += Xtlengthp;
		printf("  %g %g %s\n",Ytlengthp,0.0,RMOVE);
		printf("  %g %g %s\n",-Ytlengthp,0.0,RDRAW);
	}
	if(tln != 0.0) {
		lastXmove = absX -= Xtlengthp;
		printf("  %g %g %s\n",-Ytlengthn,0.0,RMOVE);
		printf("  %g %g %s\n",Ytlengthn,0.0,RDRAW);
	}
    }
}
