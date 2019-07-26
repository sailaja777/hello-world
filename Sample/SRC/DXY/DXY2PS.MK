# TURBO C memory model
MM=l

.c.obj:
	tcc -m$(MM) -Ic:\tc\include -c $*

OBJ=	dxy2ps.obj

OBJC=	changesi.obj    circle.obj      dxycom.obj      end_draw.obj\
	getopt.obj      getval.obj      hpglcom.obj     linesize.obj\
	linetype.obj\
	manualfe.obj    plotdot.obj     plotinit.obj    plotps.obj\
	userdefc.obj    ps_macro.obj    rectangl.obj    textps.obj\
	viewport.obj    plotcoor.obj    tick.obj

dxy2ps.exe:	$(OBJ) $(OBJC) dxy2ps.mk
	tlink /m @dxy2ps.tl


$(OBJC): defn.h dxy2ps.mk

$(OBJ):	ext.h dxy2ps.mk
