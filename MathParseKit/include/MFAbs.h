/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFABS_H
#define MPK_MFABS_H

#include "MFunction.h"

namespace mpk
{

	class MFAbs:public MFunction{
		protected:
			MFunction *m_fn;

		public:
		MFAbs(MFunction *fn=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		MFunction *GetFn(){
			return m_fn;
		}
		void SetFn(MFunction *fn);
		virtual void Release();
	};

}

#endif