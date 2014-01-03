/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFVAR_H
#define MPK_MFVAR_H

#include "MFunction.h"
namespace mpk
{
	/*!MFVar
	 * Variable element in a function
	 */
	class MFVar:public MFunction{
		protected:
			std::wstring m_name; /*!< Name of the variable */

		public:
		MFVar(const wchar_t *name=NULL, unsigned int len=1);
		MFVar(const std::wstring name);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual std::wstring ToString() const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		/*! Get Name of the variable
		 * 
		 * \return Returns a constant reference to the name of the variable
		 */
		inline const std::wstring &GetName() const{
			return m_name;
		};
		/*! Get Name of the variable
		 * 
		 * \param buffer String containing the name of the variable
		 * \param len Number of chars to copy
		 */
		void SetName(const wchar_t *buffer, unsigned int len=1);
		/*! Get Name of the variable
		 * 
		 * \param String containing the name of the variable
		 * \param len Number of chars to copy
		 */
		void SetName(const std::wstring name);
	};

}
#endif