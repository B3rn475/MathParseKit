#ifndef _MADD_H
#define _MADD_H

#include "MFunction.h"

namespace mtk
{

	class MFAdd : public MFunction{
		
		protected:
			MFunction *m_lhs;
			MFunction *m_rhs;
			
		public:
			MFAdd(MFunction *lhs=NULL,MFunction *rhs=NULL);
			virtual MFunction* Clone();
			virtual bool IsOk();
			virtual bool IsConstant(MVariablesList* variables);
			virtual MFunction* Solve(MVariablesList* variables);
			virtual MFunction* Derivate(MVariablesList *variables);
			virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
			virtual MSistem* CalcDominum(MSistem *update);
			inline MFunction *GetLhs(){
				return m_lhs;
			}
			inline MFunction *GetRhs(){
				return m_rhs;
			}
			void SetLhs(MFunction *);
			void SetRhs(MFunction *);
			virtual void Release();
	};

}
#endif