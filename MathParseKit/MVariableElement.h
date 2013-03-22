/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MVariableElement_H
#define _MVariableElement_H

#include <math.h>
#include <float.h>
#include <malloc.h>
#include <wchar.h>

#define variables_MAX_NAME_LEN 16

namespace mpk
{

	class MVariableElement{
		protected:
		wchar_t m_name[variables_MAX_NAME_LEN+1];
		double m_value;

		public:
		MVariableElement(const wchar_t* name=NULL,double value = 0.0);
		MVariableElement(MVariableElement &);
		inline const wchar_t* GetName(){
			return m_name;
		}
		void SetName(const wchar_t* name);
		inline double GetValue(){
			return m_value;
		};
		inline void SetValue(double value){
			m_value=value;
		};

		inline MVariableElement &operator=(MVariableElement &rhs){
			SetName(rhs.GetName());
			SetValue(rhs.GetValue());
			return *this;
		};
		inline MVariableElement&operator=(double& rhs){
			this->SetValue(rhs);
			return *this;
		};
	};
	
}

#endif
