#
# File:  Makefile (for library)
#
CC=g++
CFLAGS=-lm
LIB=MathParseKit.a
LIBDEST=./

LIBSRC=	./MathParseKit/MFAbs.cpp	\
	./MathParseKit/MFAcos.cpp	\
	./MathParseKit/MFAcotan.cpp	\
	./MathParseKit/MFAdd.cpp	\
	./MathParseKit/MFAsin.cpp	\
	./MathParseKit/MFAtan.cpp	\
	./MathParseKit/MFConst.cpp	\
	./MathParseKit/MFCos.cpp	\
	./MathParseKit/MFCosh.cpp	\
	./MathParseKit/MFCoTan.cpp	\
	./MathParseKit/MFCoTanh.cpp	\
	./MathParseKit/MFDiv.cpp	\
	./MathParseKit/MFExp.cpp	\
	./MathParseKit/MFLn.cpp	\
	./MathParseKit/MFLog10.cpp	\
	./MathParseKit/MFLog.cpp	\
	./MathParseKit/MFMul.cpp	\
	./MathParseKit/MFOpp.cpp	\
	./MathParseKit/MFPow.cpp	\
	./MathParseKit/MFSign.cpp	\
	./MathParseKit/MFSin.cpp	\
	./MathParseKit/MFSinh.cpp	\
	./MathParseKit/MFSqrt.cpp	\
	./MathParseKit/MFSub.cpp	\
	./MathParseKit/MFTan.cpp	\
	./MathParseKit/MFTanh.cpp	\
	./MathParseKit/MFVar.cpp	\
	./MathParseKit/MParser.cpp	\
	./MathParseKit/MRelation.cpp	\
	./MathParseKit/MSistem.cpp	\
	./MathParseKit/MVariableElement.cpp \
	./MathParseKit/MVariablesList.cpp

LIBOBJ=$(LIBSRC:.cpp=.o)

all: $(LIB)
	#@echo lib Makefile - installing $(LIB)
	#@install -m 444 $(LIB) $(LIBDEST)
	
$(LIB): $(LIBOBJ)
	@echo lib Makefile - archiving $(LIB)
	@$(AR) -cvq $(LIB) $(LIBOBJ)

.cpp.o:
	@echo lib Makefile - compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@
