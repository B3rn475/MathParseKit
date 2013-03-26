/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

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
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		int GetName(wchar_t *buffer);
		void SetName(const wchar_t *buffer, unsigned int len=1);
	};

}
#endif