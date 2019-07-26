/*  hpgl2ps.pckd  -  enhanced  version  */  /*   hpgl2ps.ucb    -
Further enhanced version */

There are two filters in this package which are based on the  Ro-
land plotter command set.

1. DXY: A simple command set which is used with all DXY plotters

2. RD-GL: This command set  is  a  superset  of  the  HP  (Hewlet
Packard)
   graphics language.

Not all the commands of DXY or RD-GL (HPGL) are implemented  (ap-
prox  95%  are) and those commands that are not are skipped and a
warning given.  It is very easy to add to this filter if  a  par-
ticular unimplemented command is desired.

If you wish to implement a command go to the relevant portion  in
the  command  switch  "dxycom.c"  or  "hpglcom.c" and call an ap-
propriate  user  written  procedure.   (You  will  need  a   good
knowledge of writing PostScript programs)

The filters use the the procedure "getopt" which is used  to  in-
terpret command line options and arguments and is normally avail-
able on 4.3 bsd and Sys V Unix. For those sites  running  4.1  or
4.2  it  may  be available as a local library and must be written
into the Makefile.

IF YOU DONT HAVE GETOPT YOU WILL HAVE REWRITE THE CODE  THAT  IN-
TERPRETS COMMAND LINE OPTIONS AND ARGUMENTS.

NOTE 1: The method of writing text is not fully  compatible  with
HPGL and will be changed at a later date.

NOTE 2: The PostScript macros are written into a C  procedure  to
allow  each filter to be a single stand alone program. These mac-
ros can easily be incorporated into other filter programs.

I have written some test  procedures  for  the  testing  of  each
filter  they  are  "test1.hpgl"  for  hpgl2ps and "test1.dxy" for
dxy2ps.

Don McCormick.

------------------------- Notes on first enhancement:

Support for user defined characters added by Gerald William Koko-
dyniak  B.A.Sc.  M.A.Sc.   University  of  Toronto, Department of
Mechanical Engineering

------------------------- Notes on  second  enhancement:  Support
for  Scaling, tickmarks, and better user defined characters added
by Gordon Jacobs, (Ph.D., since we're into titles above)  Univer-
sity of California, Berkeley in July 1989.

Mods  were  made  ONLY  for  the  hpgl2ps  program  and  are  not
guaranteed to work for dxy2ps.  HP-GL code from the Tektronix DSA
602 Digitizing Signal Analyzer  (scope)  were  used  as  a  test.
Laserwriter  output  was  compared  directly  with  plots  from a
HP7550A plotter reading the same HP-GL file.

Support for scaling was added.  The Scaling  involves  re-setting
the  coordinate  system  by  re-calculating the XSCALE and YSCALE
numbers and adding an offset to the origin.  The offset had to be
added to all files that make use of the scaling parameters.

Tick marks were added with tick.c.  Uses relative  draw  commands
to  make  the  tick marks and adds two global variables which are
the tick length as a percentage of the overall dimensions.

The parser was changed.  The SIGNED_NUMERIC  macro  recognized  a
comma  as a valid character which does not make sense.  The HP-GL
code from the DSA 602 often contains a  mnemonic  followed  by  a
comma,  but with no parameters.  This is valid code although most
sources will not place a comma unless optional parameters actual-
ly follow.  The comma was removed as a valid SIGNED_NUMERIC char-
acter and the function getval() was modified to read all trailing
commas  and  spaces.   In  this way the parser works for both the
standard and odd case mentioned above.

The user defined character routine was modified heavily.   Origi-
nal  function  did not take into account the angle of characters.
The new function  reads  the  current  angle  of  characters  and
orients the user defined character in the same way.  The scaling,
which was originally huge for some reason now is dynamically  set
to  a  proportion  of  the  size  of regular text character.  The
linewidth of the user defined character  is  arbitrarily  set  to
0.25mm  and  then the restored to the previous value.  This width
seems to fit the "linewidth" of the characters in the  postscript
helvetica font sized for the DSA 602 output.

The default paper size is changed to be 8.5 x 11 inch paper  with
command line options added to support all others.

The command line options -w and -h were added because  the  rela-
tive  scaling  of fonts with the "SR" HP-GL command, while imple-
mented correctly, gives much smaller  character  sizes  than  the
HP7550A  plotter.   The  defaults  were  set empirically to match
plotter output.

The sizes in viewport.c were modified to get correct  positioning
on  the  8.5 x 11 paper when compared to a plot directly from the
HP7550A on the same type of paper.

The textps() routine was modified to move the  position  pointers
to the end of a string when a string is drawn.  This was comment-
ed out in the code that I received, but needed to be restored for
the  user  defined  character  to  be  in the correct place.  The
results match the  HP  plotter  for  the  same  code.   
----------------------
