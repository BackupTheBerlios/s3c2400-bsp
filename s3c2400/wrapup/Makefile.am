##
## Makefile.am,v 1.8 2002/12/10 12:01:04 ralf Exp
##

BSP_PIECES = clock console startup timer irq

# bummer; have to use $foreach since % pattern subst rules only replace 1x
OBJS = $(foreach piece, $(BSP_PIECES), ../$(piece)/$(ARCH)/*.$(OBJEXT))
LIB = $(ARCH)/libbsp.a

include $(top_srcdir)/../../../../../../automake/compile.am
include $(top_srcdir)/../../../../../../automake/lib.am

#
# (OPTIONAL) Add local stuff here using +=
#

$(LIB): $(OBJS)
	$(make-library)

all: $(ARCH) $(OBJS) $(LIB) $(TMPINSTALL_FILES)

include $(top_srcdir)/../../../../../../automake/local.am
