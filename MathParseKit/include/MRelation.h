/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#ifndef MPK_MRELATION_H
#define MPK_MRELATION_H

namespace mpk
{

	class MRelation;

}

#include "MFunction.h"


#define MR_EQUAL 0x0001
#define MR_MAJOR 0x0002
#define MR_MINOR 0x0004
#define MR_NOT_EQUAL MR_MAJOR|MR_MINOR
#define MR_MAJOR_OR_EQUAL  MR_EQUAL|MR_MAJOR
#define MR_MINOR_OR_EQUAL  MR_EQUAL|MR_MINOR
#define MR_FINITE 0x0008

namespace mpk
{

	class MRelation{
		
		protected:
			MFunction *m_lhs;
			MFunction *m_rhs;
			int m_type;
		
		public:
			MRelation(int type=MR_EQUAL, const MFunction* lhs=NULL, const MFunction* rhs=NULL);
			MRelation(MRelation &origin);
			~MRelation();
			void SetType(int type=MR_EQUAL){
				m_type=type;
			};
			int GetType() const{
				return m_type;
			};
			bool IsTrue(MVariablesList *variables) const;
			MVariablesList *GetVariablesList() const;
			MRelation *Solve(MVariablesList *variables) const;
			void SetLeftFunction(MFunction &origin);
			void GetRightFunction(MFunction &origin);
			MFunction *GetLeftFunction() const;
			MFunction *GetRightFunction() const;

	};

}
#endif