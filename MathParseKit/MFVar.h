/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFVAR_H
#define _MFVAR_H

#include "MFunction.h"
namespace mpk
{
	/*!MFVar
	 * Variable element in a function
	 */
	class MFVar:public MFunction{
		protected:
			wchar_t *m_name; /*!< Name of the variable */

		public:
		MFVar(const wchar_t *name=NULL, unsigned int len=1);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		/*! Get Name of the variable
		 * 
		 * \param buffer Destination buffer
		 * \return Returns number of chars copied to the buffer
		 */
		int GetName(wchar_t *buffer) const;
		/*! Get Name of the variable
		 * 
		 * \return Returns a constant pointer to the name of the variable
		 */
		inline const wchar_t *GetName() const{
			return m_name;
		};
		/*! Get Name of the variable
		 * 
		 * \param buffer String containing the name of the variable
		 * \param len Number of chars to copy
		 */
		void SetName(const wchar_t *buffer, unsigned int len=1);
	};

}
#endif