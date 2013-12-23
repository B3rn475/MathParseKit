/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFOPP_H
#define _MFOPP_H

#include "MFunction.h"

namespace mpk
{

	class MFOpp:public MFunction{
		protected:
			MFunction *m_fn;

		public:
		MFOpp(MFunction *fn=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		inline MFunction *GetFn(){
			return m_fn;
		}
		void SetFn(MFunction *fn);
	};

}

#endif