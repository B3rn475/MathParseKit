/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MPARSER_H
#define MPK_MPARSER_H

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
#include "MFPer.h"
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

/*!Parse Completed with success.*/ 
#define MP_OK 0
/*!Parse Error the function is trucated.
 * 
 * Generally is a missing closing bracket.
 */ 
#define MP_UNEXPECTED_END 1
/*!Parse Error the char is unexpected.
 * 
 * Generally is a due to missing element '2+*5' or too much parameters 'Log10(5,2)'
 */ 
#define MP_UNEXPECTED_CHAR 2
/*!Parse Error unknown function.
 * 
 * Generally wrong function name 'Log7(5)'
 */ 
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
			std::wstring::iterator m_it; /*!< Last error position, used as internal "walker" during parsing */
			int error; /*!< Last error code */
			std::wstring m_fStr;

		public:
			MParser();

			/*! Parse a string
			 * 
			 * \param fStr A string containing a function to parse
			 * \return Pointer to the root element of the function.
			 */
			MFunction *ParseFunction(const wchar_t*fStr);

			/*! Parse a string
			 * 
			 * \param fStr A string containing a function to parse
			 * \return Pointer to the root element of the function.
			 */
			MFunction *ParseFunction(const std::wstring &fStr);

			/*! Get the error code of the last error encountered
			 * 
			 * \return Error code.
			 * \sa MP_OK MP_UNEXPECTED_END MP_UNEXPECTED_CHAR MP_UNKNOWN_FUNCTION
			 */
			int GetLastError() const
			{
				return error;
			}

			/*! Get the error position of the last error encountered
			 * 
			 * \return Position in the parsed string.
			 */
			int GetErrorPosition() const
			{
				return m_it - m_fStr.begin();
			}

		protected:
			/*! Clean the string while parsing
			 * 
			 * Ignores characters that are not valid for the parser
			 * Chars : ' '
			 * 
			 * \param str String that needs to be Cleaned.
			 */
			void Clean();
			
			/*! Check parentesis/brakets number and nesting
			 * 
			 * ...(....(...)....(...)...)... => OK
			 * ...(....)...)....(...(...)... => KO
			 * ...(....(...).... => KO
			 * 
			 * \param fStr String to check.
			 * \return Returns Test passed without errors.
			 */
			bool AnalizeParentesis();

			/*! Analize a sequence of chars as a matematical function
			 * 
			 * 
			 * \param fStr String to check.
			 * \return Returns True if no Errors.
			 */
			bool AnalizePlane(MFunction **pt, wchar_t delimiter = ')');
			
			/*! Analize a sequence of chars that can be a function or a variable
			 * 
			 * 0 = variable
			 * other = number of chars composing the function name
			 *
			 * \param fStr String to check.
			 * \return Returns number of chars composing the function name.
			 */

			unsigned int IsFunction();
			
			/*! Analize a sequence of chars that can be a function or a variable
			 * 
			 * 
			 * \param fStr String to check.
			 * \return Returns True if no Errors.
			 */
			bool AnalizeFunction(MFunction **pt);
			
			/*! Check if all chars are valid
			 * 
			 * (),.+-*^/%abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789
			 * 
			 * \param fStr String to check.
			 * \return Returns Test passed without errors.
			 */
			bool AnalizeCharCoerency();

			/*! Analize a sequence of chars that form a sequence of elements and operators
			 * 
			 * 
			 * \param fStr String to check.
			 * \return Returns True if no Errors.
			 */
			bool CreateList(FListElement **pt, wchar_t delimiter);

			/*! Convert a list of FListElements in a tree
			 * 
			 * this function compact in sequence ^ power * and / multiplication and division + and - summation subtraction
			 * 
			 * \param fStr String to check.
			 * \return Returns True if no Errors.
			 */
			bool ConvertList(FListElement *pt);

			/*! Analize a sequence of chars that can be a constant, a function or a variable
			 * 
			 * 
			 * \param fStr String to check.
			 * \return Returns True if no Errors.
			 */
			bool ConvertElement(MFunction **pt);
	};
}
#endif
