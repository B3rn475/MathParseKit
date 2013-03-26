/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFLOG_H
#define _MFLOG_H

#include "MFunction.h"

namespace mpk
{

	class MFLog:public MFunction{
		protected:
			MFunction *m_base;
			MFunction *m_argument;

		public:
		MFLog(MFunction *base=NULL,MFunction *argument=NULL);
		virtual MFunction* Clone() const;
		virtual bool IsOk() const;
		virtual bool IsConstant(MVariablesList* variables) const;
		virtual MFunction* Solve(MVariablesList* variables) const;
		virtual MFunction* Derivate(MVariablesList *variables) const;
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const;
		virtual MSistem* GetDomain(MSistem *update) const;
		virtual void Release();
		inline MFunction *GetBase(){
			return m_base;
		};
		inline MFunction *GetArgument(){
			return m_argument;
		};
		void SetBase(MFunction *base);
		void SetArgument(MFunction *argument);
	};

}
#endif