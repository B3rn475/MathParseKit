/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFPOW_H
#define _MFPOW_H

#include "MFunction.h"

namespace mpk
{

	class MFPow:public MFunction{
		protected:
			MFunction *m_base;
			MFunction *m_exponent;

		public:
		MFPow(const MFunction *base=NULL, const MFunction *exponent=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		inline MFunction *GetBase(){
			return m_base;
		};
		inline MFunction *GetExponent(){
			return m_exponent;
		};
		void SetBase(MFunction *base);
		void SetExponent(MFunction *exponent);
	};

}

#endif