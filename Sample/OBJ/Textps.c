/* textps.c */
#include "defn.h"

#define MAXBUFSIZE 100

textps(type)
int     type;
{
    char    string[4];
    char    buffer[MAXBUFSIZE];
    float   Xch, Ych;
    int	    intval;
    int     i;

    end_draw();

    if (type == TEXT)
    {
	for (i = 0 ; i < MAXBUFSIZE; i++)	/* Clear buffer */
	    buffer[i] = NULL;

	i = 0;					/* Reset buffer counter */

	while (((ch = getc(stream)) != EOF)
			&& ch != CR && ch != LF && ch != EOL) {
	    buffer[i++] = ch;
	}

	printf("%g %g 1 %g (%s) Text\n", absX, absY, char_angle, buffer);

	/* move to end of string */
	absX += (i * (char_space)) * cos(char_angle * deg_rad) ;
        absY += (i * (char_space)) * sin(char_angle * deg_rad) ;

    } else			/* Must be a MARK */
    {
	int     symb_num;

	if (SIGNED_NUMERIC)
	    symb_num = getval();
	else
	{
	    fprintf(stderr,
		    "Error: expecting a symbol number not %c (%d)",
		    symb_num, symb_num);
	    exit(1);
	}
	intval = (int)(getval() + 0.5);
	switch (intval)
	{
	case 0:
	    strcpy(string, "*");
	    break;

	case 1:
	    strcpy(string, "+");
	    break;

	case 2:
	    strcpy(string, "#");
	    break;

	case 3:
	    strcpy(string, "@");
	    break;

	case 4:
	    strcpy(string, "%");
	    break;

	case 5:
	    strcpy(string, "|");
	    break;

	case 6:
	    strcpy(string, "=");
	    break;

	case 7:
	    strcpy(string, "&");
	    break;

	case 9:
	    strcpy(string, "O");
	    break;

	case 10:
	    strcpy(string, "0");
	    break;

	case 11:
	    strcpy(string, "Y");
	    break;

	case 12:
	    strcpy(string, "X");
	    break;

	case 13:
	    strcpy(string, "Z");
	    break;

	case 14:
	    strcpy(string, "S");
	    break;

	case 15:
	    strcpy(string, "Q");
	    break;

	default:
	    fprintf(stderr, "Warning symbol number is %d\n", symb_num);
	    strcpy(string, "*");
	    break;
	}
	printf("%g %g 5 %g (%s) Text\n", absX, absY, char_angle, string);
    }
}
