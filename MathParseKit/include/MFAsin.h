/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFASIN_H
#define MPK_MFASIN_H

#include "MFunction.h"

namespace mpk
{

	class MFAsin:public MFunction{
		protected:
			MFunction *m_argument;

		public:
		MFAsin(MFunction *argument=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		MFunction *GetArgument(){
			return m_argument;
		}
		void SetArgument(MFunction *argument);
		virtual void Release();
	};

}
#endif