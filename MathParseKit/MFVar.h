#ifndef _MFVAR_H
#define _MFVAR_H

#include "MFunction.h"
namespace mpk
{

	class MFVar:public MFunction{
		protected:
			wchar_t *m_name;

		public:
		MFVar(const wchar_t *name=NULL, unsigned int len=1);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		virtual void Release();
		int GetName(wchar_t *buffer);
		void SetName(const wchar_t *buffer, unsigned int len=1);
	};

}
#endif