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
		virtual MFunction* Clone();
		virtual bool IsOk();
		virtual bool IsConstant(MVariablesList* variables);
		virtual MFunction* Solve(MVariablesList* variables);
		virtual MFunction* Derivate(MVariablesList *variables);
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
		virtual MSistem* CalcDominum(MSistem *update);
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