PRJ=..
PRJNAME=writerperfect
TARGET=writerperfect

.INCLUDE :  settings.mk

.IF "$(GUI)"=="UNX"
.IF "$(SYSTEM_LIBWPD)" == "YES"
LIBWPD=$(LIBWPD_LIBS)
.ELSE
LIBWPD=-lwpdlib
.ENDIF
.ELSE
.IF "$(GUI)$(COM)"=="WNTGCC"
LIBWPD=-lwpdlib
.ELSE
 LIBWPD=$(LIBPRE) wpdlib.lib
.ENDIF
.ENDIF

LIB1TARGET= $(SLB)$/wpft.lib
LIB1FILES= \
    $(SLB)$/stream.lib  \
    $(SLB)$/filter.lib  \
    $(SLB)$/wpdimp.lib
SHL1LIBS=$(LIB1TARGET)
SHL1STDLIBS+= \
    $(SOTLIB) \
    $(SO2LIB) \
    $(UNOTOOLSLIB) \
    $(TOOLSLIB) \
    $(UCBHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(SALLIB) \
    $(XMLOFFLIB) \
    $(LIBWPD)

SHL1TARGET = wpft$(DLLPOSTFIX)
SHL1IMPLIB = i$(SHL1TARGET)
SHL1LIBS = $(LIB1TARGET)
SHL1VERSIONMAP=$(SOLARENV)/src/component.map
DEF1NAME=$(SHL1TARGET)

.INCLUDE :  target.mk

ALLTAR : $(MISC)/wpft.component

$(MISC)/wpft.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        wpft.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL1TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt wpft.component
