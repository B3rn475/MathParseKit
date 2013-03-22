/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MPARSER_H
#define _MPARSER_H

#include "MFunction.h"
#include "MFAbs.h"
#include "MFAcos.h"
#include "MFAcotan.h"
#include "MFAdd.h"
#include "MFAsin.h"
#include "MFAtan.h"
#include "MFConst.h"
#include "MFCos.h"
#include "MFCoTan.h"
#include "MFDiv.h"
#include "MFExp.h"
#include "MFLn.h"
#include "MFLog.h"
#include "MFLog10.h"
#include "MFMul.h"
#include "MFOpp.h"
#include "MFPow.h"
#include "MFSin.h"
#include "MFSub.h"
#include "MFTan.h"
#include "MFVar.h"
#include "MFSign.h"
#include "MFSinh.h"
#include "MFCosh.h"
#include "MFTanh.h"
#include "MFCoTanh.h"
#include "MFSqrt.h"
#include "MRelation.h"
#include "MSistem.h"
#include "MVariableElement.h"
#include "MVariablesList.h"

#define MP_OK 0
#define MP_UNEXPECTED_END 1
#define MP_UNEXPECTED_CHAR 2
#define MP_UNKNOWN_FUNCTION 3

namespace mpk
{

	struct FListElement{
		wchar_t op;
		MFunction *func;
		FListElement *next;
	};

	/*!MParser
	 * Parser Class
	 * 
	 * Parser class that allow to convert a string into a tree of matematical functions
	 */
	class MParser{
		protected:
			unsigned int m_pos;
			int error;

		public:
			MParser();
			MFunction *ParseFunction(const wchar_t*fStr);
			wchar_t *Clean(wchar_t * str) const;
			inline int GetLastError()
			{
				return error;
			}
			inline int GetErrorPosition()
			{
				return m_pos;
			}

		protected:
			bool AnalizeParentesis(const wchar_t *fStr);
			bool AnalizePlane(const wchar_t *fStr, MFunction **pt,wchar_t delimiter=')');
			unsigned int IsFunction(const wchar_t *fStr);
			bool AnalizeFunction(const wchar_t *fStr, MFunction **pt);
			bool AnalizeCharCoerency(const wchar_t *fStr);
			bool CreateList(const wchar_t *fStr, FListElement **pt, wchar_t delimiter);
			bool ConvertList(FListElement *pt);
			bool ConvertElement(const wchar_t *fStr, MFunction **pt);
	};
}
#endif
