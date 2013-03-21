#ifndef _MFACOTAN_H
#define _MFACOTAN_H

#include "MFunction.h"

namespace mtk
{

	class MFAcotan:public MFunction{
		protected:
			MFunction *m_argument;

		public:
		MFAcotan(MFunction *argument=NULL);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		inline MFunction *GetArgument(){
			return m_argument;
		}
		void SetArgument(MFunction *argument);
		virtual void Release();
	};

}
#endif