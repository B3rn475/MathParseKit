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
			int Add(int type, MFunction &lhs, MFunction &rhs);
			int Add(MRelation &relation);
			inline int Count(){
				return m_count;
			};
			MRelation *Item(int index);
			int Remove(int index);
			bool Solve(MVariablesList *variables);
	};

	struct MSistemItem{
		MRelation *relation;
		MSistemItem *next;
	};
}

#endif