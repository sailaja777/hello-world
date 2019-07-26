/* hpgl2ps.c */
#include "ext.h"

#define USAGE "Usage: hpgl2ps [-43BAmr] [-l line sizes] [-s scale] [-x offset] [-y offset] [-w font_width] [-h font_height] [file]\n"

main(argc, argv)
/*
 *  hpgl2ps.c
 *
 *  Modified by J.R. Nickerson, G.W. Kokodyniak
 *  University of Toronto, Department of Mechanical Enginnering
 *
 *  Further modified by Gordon Jacobs, University of Calif, Berkeley
 *   Added Scaling,Ticks,modified userdefchar(),sizes for 8.5x11 paper
 *
 */
int     argc;
char   *argv[];
{
    extern int optind;
    extern char *optarg;

    int     ch;                                 /* GWKMOD */
    int     op;                                 /* GWKMOD */
    /* GWK: char    op; */
    int	    MANUAL_FEED = 0;			/* DEFAULT: No manual feed */

    PaperSize = "A";
    Mode = "HPGL";
    plotcoords();

    plotinit();			/* Get other initialiasations */

    while ((ch = getopt(argc, argv, "AB43l:ms:x:y:rh:w:")) != EOF)
    {
	switch (ch)
	{
	case '4':		/* HP-GL ISO A4 297mm * 210mm */
	    PaperSize = "A4";
	    plotcoords();
	    break;

	case '3':		/* HP-GL ISO A3 420mm * 297mm */
	    PaperSize = "A3";
	    plotcoords();
	    break;

	case 'A':		/* HP-GL ANSI A 11 * 8.5inch */
	    PaperSize = "A";
	    plotcoords();
	    break;

	case 'B':		/* HP-GL ANSI B 17 * 11inch */
	    PaperSize = "B";
	    plotcoords();
	    break;

	case 'l':		/* change line size option */
	    changesizes(optarg);
	    break;

	case 'm':		/* enable manual feed on Laserwriter */
	    MANUAL_FEED = 1;
	    break;

	case 'r':		/* rotate the plot 90 degrees */
	    LANDSCAPE = 0;
	    break;

	case 's':		/* scale the plot from 0.1 to 3.0 times */
	    SCALE = atof(optarg);
	    if (SCALE < 0.1)
		SCALE = 0.1;
	    else
	    if (SCALE > 3)
		SCALE = 3;
	    break;

	case 'h':
	    FONT_H_MULT = atof(optarg);
	    break;

	case 'w':
	    FONT_W_MULT = atof(optarg);
	    break;

	case 'x':		/* place an X offset (in mm) */
	    xoffset = atof(optarg);
	    break;

	case 'y':		/* place an Y offset (in mm) */
	    yoffset = atof(optarg);
	    break;

	default:
	    fprintf(stderr, "%s\n", USAGE);
	    exit(1);
	}
    }
    if (optind == argc)
	stream = stdin;
    else if ((stream = fopen(argv[optind], "r")) == NULL)
    {
	fprintf(stderr, "ERROR: cannot open \"%s\"\n", argv[optind]);
	exit(1);
    }
    ps_macros();			/* Output PostScript Macros */

    viewport();				/* Scale the viewport for the plot */

    printf("/%s %g Font\n", font, char_height);

    if (MANUAL_FEED)
	manualfeed(1);

    while ((op = getc(stream)) != EOF)
	if (isalpha(op) > 0)
	    hpglcom(op);

    end_draw();

    printf("showpage\n");

    if (MANUAL_FEED)
	manualfeed(0);
}
