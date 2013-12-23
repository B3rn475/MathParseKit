#
# File:  Makefile (for library)
#
CC=g++
INC1=./MathParseKit/include
INCDIRS=-I${INC1}
LDFLAGS=-lm
CFLAGS=${INCDIRS}
LIB=MathParseKit.a
LIBD=MathParseKitd.a
LIBDEST=./

LIBSRC=	./MathParseKit/src/MFAbs.cpp	\
	./MathParseKit/src/MFAcos.cpp	\
	./MathParseKit/src/MFAcotan.cpp	\
	./MathParseKit/src/MFAdd.cpp	\
	./MathParseKit/src/MFAsin.cpp	\
	./MathParseKit/src/MFAtan.cpp	\
	./MathParseKit/src/MFConst.cpp	\
	./MathParseKit/src/MFCos.cpp	\
	./MathParseKit/src/MFCosh.cpp	\
	./MathParseKit/src/MFCoTan.cpp	\
	./MathParseKit/src/MFCoTanh.cpp	\
	./MathParseKit/src/MFDiv.cpp	\
	./MathParseKit/src/MFExp.cpp	\
	./MathParseKit/src/MFLn.cpp	\
	./MathParseKit/src/MFLog10.cpp	\
	./MathParseKit/src/MFLog.cpp	\
	./MathParseKit/src/MFMul.cpp	\
	./MathParseKit/src/MFOpp.cpp	\
	./MathParseKit/src/MFPow.cpp	\
	./MathParseKit/src/MFSign.cpp	\
	./MathParseKit/src/MFSin.cpp	\
	./MathParseKit/src/MFSinh.cpp	\
	./MathParseKit/src/MFSqrt.cpp	\
	./MathParseKit/src/MFSub.cpp	\
	./MathParseKit/src/MFTan.cpp	\
	./MathParseKit/src/MFTanh.cpp	\
	./MathParseKit/src/MFVar.cpp	\
	./MathParseKit/src/MParser.cpp	\
	./MathParseKit/src/MRelation.cpp	\
	./MathParseKit/src/MSistem.cpp	\
	./MathParseKit/src/MVariableElement.cpp	\
	./MathParseKit/src/MVariablesList.cpp

LIBOBJ=$(LIBSRC:.cpp=.o)

all: $(LIB) $(LIBD)
	#@echo lib Makefile - installing $(LIB)
	#@install -m 444 $(LIB) $(LIBDEST)
	
$(LIB): $(LIBOBJ)
	@echo lib Makefile - archiving release $(LIB)
	DFLAGS=
	@$(AR) -cvq $(LIB) $(LIBOBJ)
	
$(LIBD): $(LIBOBJ)
	@echo lib Makefile - archiving debug $(LIBD)
	DFLAGS=-DDEBUG
	@$(AR) -cvq $(LIBD) $(LIBOBJ)

.cpp.o:
	@echo lib Makefile - compiling $<
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DFLAGS) -c $< -o $@ 
