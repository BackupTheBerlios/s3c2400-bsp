##
## Makefile.am,v 1.8 2002/03/28 00:38:11 joel Exp
##

ACLOCAL_AMFLAGS = -I ../../../../../../aclocal

# wrapup is the one that actually builds and installs the library
#  from the individual .rel files built in other directories
SUBDIRS = . include clock console startup start timer irq wrapup

include $(top_srcdir)/../../bsp.am

EXTRA_DIST = bsp_specs

include $(top_srcdir)/../../../../../../automake/subdirs.am
include $(top_srcdir)/../../../../../../automake/local.am
