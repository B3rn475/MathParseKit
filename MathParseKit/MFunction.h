#ifndef _MFunction_H
#define _MFunction_H

#define MF_NONE 0
#define MF_CONST 1
#define MF_VAR 2
#define MF_OPP 3
#define MF_ADD 4
#define MF_SUB 5
#define MF_MUL 6
#define MF_DIV 7
#define MF_LOG 8
#define MF_LN 9
#define MF_LOG10 10
#define MF_POW 11
#define MF_EXP 12
#define MF_SIN 13
#define MF_COS 14
#define MF_TAN 15
#define MF_COTAN 16
#define MF_ASIN 17
#define MF_ACOS 18
#define MF_ATAN 19
#define MF_ACOTAN 20
#define MF_ABS 21
#define MF_SIGN 22
#define MF_SINH 23
#define MF_COSH 24
#define MF_TANH 25
#define MF_COTANH 26
#define MF_SQRT 27

#define MF_USER 30

namespace mtk
{

	class MFunction;

}

#include "MVariablesList.h"
#include "MSistem.h"

#define _USE_MATH_DEFINES 

#include <math.h>
#include <stdlib.h>

namespace mtk
{

	class MFunction{
		protected:
			int m_type;

		public:
		virtual MFunction* Clone()=0;
		virtual bool IsOk()=0;
		virtual bool IsConstant(MVariablesList* variables)=0;
		virtual MFunction* Solve(MVariablesList* variables)=0;
		virtual MFunction* Derivate(MVariablesList *)=0;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL)=0;
		virtual MSistem* CalcDominum(MSistem *update)=0;
		inline int GetType(){
			return m_type;
		};
		virtual void Release()=0;
	};

}
#endif
