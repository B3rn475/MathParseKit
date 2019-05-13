/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MFunction_H
#define MPK_MFunction_H

/*!No function.*/
#define MF_NONE 0
/*!Constant.*/
#define MF_CONST 1
/*!Variable.*/
#define MF_VAR 2
/*!Opposite.*/
#define MF_OPP 3
/*!Sum.*/
#define MF_ADD 4
/*!Subtraction.*/
#define MF_SUB 5
/*!Multiplication.*/
#define MF_MUL 6
/*!Division.*/
#define MF_DIV 7
/*!Logaritm.*/
#define MF_LOG 8
/*!Natural Base Logarithm.*/
#define MF_LN 9
/*!Base 10 Logarithm.*/
#define MF_LOG10 10
/*!Power.*/
#define MF_POW 11
/*!Natural Exponential.*/
#define MF_EXP 12
/*!Sine.*/
#define MF_SIN 13
/*!Cosine.*/
#define MF_COS 14
/*!Tangent.*/
#define MF_TAN 15
/*!Contangent.*/
#define MF_COTAN 16
/*!Arcsine.*/
#define MF_ASIN 17
/*!Arccosine.*/
#define MF_ACOS 18
/*!Arctangent.*/
#define MF_ATAN 19
/*!Arccotangent.*/
#define MF_ACOTAN 20
/*!Absolute Value.*/
#define MF_ABS 21
/*!Signum.*/
#define MF_SIGN 22
/*!Hyperbolic Sine.*/
#define MF_SINH 23
/*!Hyperbolic Cosine.*/
#define MF_COSH 24
/*!Hyperbolic Tangent.*/
#define MF_TANH 25
/*!Hyperbolic  Cotangent.*/
#define MF_COTANH 26
/*!Square Root.*/
#define MF_SQRT 27
/*!Percentage.*/
#define MF_PER 28
/*!.*/

/*!Use defined functions.*/
#define MF_USER 30

namespace mpk
{

	class MFunction;

}

#include "MVariablesList.h"
#include "MSistem.h"

#define _USE_MATH_DEFINES 

#include <math.h>
#include <stdlib.h>
#include <string>

namespace mpk
{
	/*!MFunction
	 * Virtual class base for all functions
	 */
	class MFunction{
		protected:
			/*! Function Type
			 * 
			 * \sa  MF_NONE MF_CONST MF_VAR MF_OPP MF_ADD MF_SUB MF_MUL MF_DIV MF_LOG MF_LN MF_LOG10 MF_POW MF_EXP MF_SIN MF_COS MF_TAN MF_COTAN MF_ASIN MF_ACOS MF_ATAN MF_ACOTAN MF_ABS MF_SIGN MF_SINH MF_COSH MF_TANH MF_COTANH MF_SQRT MF_PER MF_USER
			 */
			int m_type;

		public:
		/*! Clone this function and all the child recursively
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * 
		 * \return Returns a clone of this function (recursive).
		 */
		virtual MFunction* Clone() const=0;
		
		/*! Are there any problems?
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * \return Returns true if there are no errors (recursive).
		 */
		virtual bool IsOk() const=0;
		
		/*! This function is constant relativelly to this list of variables
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * \param variables Variables respect with control the constantness (recursive).
		 * \return Returns true if it is constant.
		 */
		virtual bool IsConstant(MVariablesList* variables) const=0;
		
		/*! Solve this function with respect to this variables
		 * 
		 * If not all the variables defined in the function tree are presente in the list the function may return another tree
		 * It needs to be reimplemented in child classes
		 * 
		 * \param variables Variables that are used during resolution (recursive).
		 * \return Returns the solution respect to the variables values.
		 */
		virtual MFunction* Solve(MVariablesList* variables) const=0;
		
		/*! Derivate this function with respect to this variables (generally 1)
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * \param variables Variables respect with derivate (recursive).
		 * \return Returns the derivate of this function.
		 */
		virtual MFunction* Derivate(MVariablesList *variables) const=0;
		
		/*! Get all the variables defined in the function tree recursivelly
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * \param list Optional pointer to an existing variable list (if NULL a new one is created).
		 * \return Returns the variable list (if list is NULL you need to delete it at the end, if not it is equal to list).
		 */
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL) const=0;
		
		/*! Return the function as a string
		 *
		 * \Return function as a string
		 */
		virtual std::wstring ToString() const=0;

		/*! Return the dominium of the function as a system
		 * 
		 * It needs to be reimplemented in child classes
		 * 
		 * \param update Optional pointer to an existing system (if NULL a new one is created).
		 * \return Returns the domain of this function (if update is NULL you need to delete it at the end, if not it is equal to update).
		 */
		virtual MSistem* GetDomain(MSistem *update) const=0;
		
		/*! Get the type of the function
		 * 
		 * \return Return the type of the function
		 */
		int GetType() const{
			return m_type;
		};
		
		/*! Release this function and all the children
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual void Release()=0;
	};

}
#endif
