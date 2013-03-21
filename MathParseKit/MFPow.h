#ifndef _MFPOW_H
#define _MFPOW_H

#include "MFunction.h"

namespace mtk
{

	class MFPow:public MFunction{
		protected:
			MFunction *m_base;
			MFunction *m_exponent;

		public:
		MFPow(MFunction *base=NULL,MFunction *exponent=NULL);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		virtual void Release();
		inline MFunction *GetBase(){
			return m_base;
		};
		inline MFunction *GetExponent(){
			return m_exponent;
		};
		void SetBase(MFunction *base);
		void SetExponent(MFunction *exponent);
	};

}

#endif