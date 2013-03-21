#ifndef _MFCOTANH_H
#define _MFCOTANH_H

#include "MFunction.h"

namespace mtk
{

	class MFCoTanh:public MFunction{
		protected:
			MFunction *m_argument;

		public:
		MFCoTanh(MFunction *argument=NULL);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		virtual void Release();
		inline MFunction *GetArgument(){
			return m_argument;
		}
		void SetArgument(MFunction *argument);
	};

}
#endif