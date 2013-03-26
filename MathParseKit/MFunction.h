/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef _MFunction_H
#define _MFunction_H

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

namespace mpk
{
	/*!MFunction
	 * Virtual class base for all functions
	 * 
	 * Parser class that allow to convert a string into a tree of matematical functions
	 */
	class MFunction{
		protected:
			/*! Function Type
			 * 
			 * \sa  MF_NONE MF_CONST MF_VAR MF_OPP MF_ADD MF_SUB MF_MUL MF_DIV MF_LOG MF_LN MF_LOG10 MF_POW MF_EXP MF_SIN MF_COS MF_TAN MF_COTAN MF_ASIN MF_ACOS MF_ATAN MF_ACOTAN MF_ABS MF_SIGN MF_SINH MF_COSH MF_TANH MF_COTANH MF_SQRT MF_USER
			 */
			int m_type;

		public:
		/*! Clone
		 * Clone This function and all the child recursively
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual MFunction* Clone()=0;
		
		/*! IsOk
		 * Are there any problems?
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual bool IsOk()=0;
		
		/*! IsConstant
		 * This function is constant relativelly to this list of variables
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual bool IsConstant(MVariablesList* variables)=0;
		
		/*! Solve
		 * Solve this function with respect to this variables
		 * 
		 * If not all the variables defined in the function tree are presente in the list the function may return another tree
		 * It needs to be reimplemented in child classes
		 */
		virtual MFunction* Solve(MVariablesList* variables)=0;
		
		/*! Derivate
		 * Derivate this function with respect to this variables (generally 1)
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual MFunction* Derivate(MVariablesList *)=0;
		
		/*! GetVariablesList
		 * Get all the variables defined in the function tree recursivelly
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL)=0;
		
		/*! CalcDominum
		 * Return the dominium of the function as a system
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual MSistem* CalcDominum(MSistem *update)=0;
		
		/*! GetType
		 * Return the type of the function
		 */
		inline int GetType() const{
			return m_type;
		};
		
		/*! Release
		 * Release this function and all the children
		 * 
		 * It needs to be reimplemented in child classes
		 */
		virtual void Release()=0;
	};

}
#endif
