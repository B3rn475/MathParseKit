/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFDIV_H
#define MPK_MFDIV_H

#include "MFunction.h"

namespace mpk
{

	class MFDiv:public MFunction{
		protected:
			MFunction *m_num;
			MFunction *m_denum;

		public:
		MFDiv(MFunction *num=NULL,MFunction *denum=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		inline MFunction *GetNum(){
			return m_num;
		};
		inline MFunction *GetDenum(){
			return m_denum;
		};
		void SetNum(MFunction *num);
		void SetDenum(MFunction *denum);
	};

}
#endif