#ifndef _MFLOG_H
#define _MFLOG_H

#include "MFunction.h"

namespace mtk
{

	class MFLog:public MFunction{
		protected:
			MFunction *m_base;
			MFunction *m_argument;

		public:
		MFLog(MFunction *base=NULL,MFunction *argument=NULL);
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
		inline MFunction *GetArgument(){
			return m_argument;
		};
		void SetBase(MFunction *base);
		void SetArgument(MFunction *argument);
	};

}
#endif