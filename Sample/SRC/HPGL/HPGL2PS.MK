# Define the extensions for the object and executable files.

# TURBO C Memory model
MM=l

# Define the compilation rules.

.c.obj:
	tcc -m$(MM) -Ic:\tc\include -c $*


OBJ =	hpgl2ps.obj

OBJC =	changesi.obj \
circle.obj \
dxycom.obj \
end_draw.obj \
getopt.obj \
getval.obj \
hpglcom.obj \
linesize.obj \
linetype.obj \
manualfe.obj \
plotdot.obj \
plotinit.obj \
plotps.obj \
userdefc.obj \
ps_macro.obj \
rectangl.obj \
textps.obj \
viewport.obj \
plotcoor.obj \
tick.obj

hpgl2ps.exe:	$(OBJ) $(OBJC) hpgl2ps.mk
	tlink /m @hpgl2ps.tl

$(OBJC): defn.h hpgl2ps.mk
$(OBJ):	ext.h hpgl2ps.mk
