/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFSQRT_H
#define _MFSQRT_H

#include "MFunction.h"

namespace mpk
{

	class MFSqrt:public MFunction{
		protected:
			MFunction *m_fn;

		public:
		MFSqrt(MFunction *fn=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		inline MFunction *GetFn(){
			return m_fn;
		}
		void SetFn(MFunction *fn);
		virtual void Release();
	};

}
#endif