#ifndef _MFMUL_H
#define _MFMUL_H

#include "MFunction.h"

namespace mtk
{

	class MFMul:public MFunction{
		protected:
			MFunction *m_lhs;
			MFunction *m_rhs;

		public:
		MFMul(MFunction *lhs=NULL,MFunction *rhs=NULL);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		virtual void Release();
		inline MFunction *GetLhs(){
			return m_lhs;
		};
		inline MFunction *GetRhs(){
			return m_rhs;
		};
		void SetLhs(MFunction *lhs);
		void SetRhs(MFunction *lhs);
	};

}

#endif