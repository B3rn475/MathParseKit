/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFCONST_H
#define MPK_MFCONST_H

#include "MFunction.h"

namespace mpk
{
	/*!MFConst
	 * Constant element in a function
	 */
	class MFConst:public MFunction{
		protected:
			double m_value; /*!< Value of the constant */

		public:
		MFConst(double value=0.0);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		
		/*! Get Value of the constant
		 * 
		 * \return Returns the Value of the constant.
		 */
		double GetValue() const{
			return m_value;
		}
		/*! Set Value of the constant
		 * 
		 * \param value New value of the constant.
		 */
		void SetValue(double value){
			m_value = value;
		}
		
		bool operator==(MFConst &B)const;
		bool operator>=(MFConst &B)const;
		bool operator<=(MFConst &B)const;
		bool operator>(MFConst &B)const;
		bool operator<(MFConst &B)const;
	};

}
#endif