/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFMUL_H
#define MPK_MFMUL_H

#include "MFunction.h"

namespace mpk
{

	class MFMul:public MFunction{
		protected:
			MFunction *m_lhs;
			MFunction *m_rhs;

		public:
		MFMul(const MFunction *lhs=NULL, const MFunction *rhs=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		MFunction *GetLhs(){
			return m_lhs;
		};
		MFunction *GetRhs(){
			return m_rhs;
		};
		void SetLhs(MFunction *lhs);
		void SetRhs(MFunction *lhs);
	};

}

#endif