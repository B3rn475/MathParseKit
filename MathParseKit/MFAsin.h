#ifndef _MFASIN_H
#define _MFASIN_H

#include "MFunction.h"

namespace mtk
{

	class MFAsin:public MFunction{
		protected:
			MFunction *m_argument;

		public:
		MFAsin(MFunction *argument=NULL);
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