#ifndef _MFATAN_H
#define _MFATAN_H

#include "MFunction.h"

namespace mtk
{

	class MFAtan:public MFunction{
		protected:
			MFunction *m_argument;

		public:
		MFAtan(MFunction *argument=NULL);
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