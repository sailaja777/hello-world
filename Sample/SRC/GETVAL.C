/* getval.c
 * Returns a real number 
 */

#include "defn.h"

#define ERROR "Two or more decimal places in a number"

float
getval()
{
    char    valbuf[10];
    float   value;
    int     DECIMAL = 0;
    int     i;

    /* Null the value buffer "valbuf" */
    for (i = 0; i < 10; i++)
	valbuf[i] = NULL;

    i = 0;

    ch = getc(stream);

    while ((ch == ' ') || (ch == ','))
	ch = getc(stream);

    while ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-' || ch == '+')
    {
	if (ch == '.')
	{
	    if (DECIMAL)
	    {
		fprintf(stderr,"Error: %s\n", ERROR);
		exit(1);
	    }
	    DECIMAL = 1;
	}
	valbuf[i++] = ch;
	ch = getc(stream);
    }
    /* remove trailing space or comma to set-up for 
       next digit or mnemonic */
    /* added by Gordon Jacobs so that definition of 
       SIGNED_NUMERIC in defn.h could be made more accurate.
       Solves problem of commands like PA,PD0,0... where
       optional comma is present.  (Tektronix scope outputs!) */ 
    while ((ch == ' ') || (ch == ','))
	ch = getc(stream);

    ungetc(ch, stream);		/* Put non numeric char back */
    value = atof (valbuf);
    return (value);
}
