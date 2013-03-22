/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFEXP_H
#define _MFEXP_H

#include "MFunction.h"

namespace mpk
{

	class MFExp:public MFunction{
		protected:
			MFunction *m_exponent;

		public:
		MFExp(MFunction *exponent=NULL);
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
		virtual void Release();
		inline MFunction *GetExponent(){
			return m_exponent;
		};
		void SetExponent(MFunction *exponent);
	};

}
#endif