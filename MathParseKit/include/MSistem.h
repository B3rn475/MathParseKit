/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */


#ifndef _MSISTEM_H
#define _MSISTEM_H

namespace mpk
{
	class MSistem;
}

#include "MFunction.h"
#include "MRelation.h"

namespace mpk
{

	struct MSistemItem;

	class MSistem{

		protected:
			MSistemItem *m_list;
			int m_count;

		public:
			MSistem();
			MSistem(MSistem &origin);
			~MSistem();
			int Add();
			int Add(int type, const MFunction &lhs, const MFunction &rhs);
			int Add(MRelation &relation);
			inline int Count() const{
				return m_count;
			};
			MRelation *Item(int index);
			const MRelation *Item(int index) const;
			int Remove(int index);
			bool Solve(MVariablesList *variables) const;
	};

	struct MSistemItem{
		MRelation *relation;
		MSistemItem *next;
	};
}

#endif