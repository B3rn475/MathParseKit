/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MVariableElement_H
#define MPK_MVariableElement_H

#include <math.h>
#include <float.h>
#include <malloc.h>
#include <wchar.h>
#include <string>

namespace mpk
{

	class MVariableElement{
		protected:
		std::wstring m_name;
		double m_value;

		public:
		MVariableElement(const wchar_t* name=NULL,double value = 0.0);
		MVariableElement(const std::wstring &name,double value = 0.0);
		MVariableElement(MVariableElement &);
		const std::wstring &GetName() const{
			return m_name;
		}
		void SetName(const wchar_t* name);
		void SetName(const std::wstring &name);
		double GetValue() const{
			return m_value;
		};
		void SetValue(double value){
			m_value=value;
		};

		MVariableElement &operator=(MVariableElement &rhs){
			SetName(rhs.GetName());
			SetValue(rhs.GetValue());
			return *this;
		};
		MVariableElement&operator=(double& rhs){
			this->SetValue(rhs);
			return *this;
		};
	};
	
}

#endif
