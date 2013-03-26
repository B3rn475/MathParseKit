/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFCONST_H
#define _MFCONST_H

#include "MFunction.h"

namespace mpk
{

	class MFConst:public MFunction{
		protected:
			double m_value;

		public:
		MFConst(double value=0.0);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual MSistem* GetDomain(MSistem *update) const;
		inline double GetValue(){
			return m_value;
		}
		inline void SetValue(double value){
			m_value+=value;
		}
		virtual void Release();
		bool operator==(MFConst &B)const;
		bool operator>=(MFConst &B)const;
		bool operator<=(MFConst &B)const;
		bool operator>(MFConst &B)const;
		bool operator<(MFConst &B)const;
	};

}
#endif