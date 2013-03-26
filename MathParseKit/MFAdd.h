/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MADD_H
#define _MADD_H

#include "MFunction.h"

namespace mpk
{

	class MFAdd : public MFunction{
		
		protected:
			MFunction *m_lhs;
			MFunction *m_rhs;
			
		public:
			MFAdd(MFunction *lhs=NULL,MFunction *rhs=NULL);
			virtual MFunction* Clone() const;
			virtual bool IsOk() const;
			virtual bool IsConstant(MVariablesList* variables) const;
			virtual MFunction* Solve(MVariablesList* variables) const;
			virtual MFunction* Derivate(MVariablesList *variables) const;
			virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
			virtual MSistem* GetDomain(MSistem *update) const;
			inline MFunction *GetLhs(){
				return m_lhs;
			}
			inline MFunction *GetRhs(){
				return m_rhs;
			}
			void SetLhs(MFunction *);
			void SetRhs(MFunction *);
			virtual void Release();
	};

}
#endif