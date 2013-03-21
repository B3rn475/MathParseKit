#ifndef _MVariablesList_H
#define _MVariablesList_H
	
#include "MVariableElement.h"

namespace mpk
{

	struct MvariablesItem{
		MVariableElement *link;
		MvariablesItem *next;
	};

	class MVariablesList{
		protected:
			MvariablesItem *m_pt;
			int m_count;
		public:
			MVariablesList();
			MVariablesList(MVariablesList &);
			~MVariablesList();
			inline int Count(){
				return m_count;
			}
			MVariableElement *Add(const wchar_t *name=NULL, double value=0.0);
			MVariableElement *Add(MVariableElement *element);
			MVariableElement *GetItem(int index);
			MVariableElement *GetItem(const wchar_t *name);
			int FindItem(const wchar_t *name);
			int DeleteElement(int index);
			int DeleteElement(const wchar_t *name);
	};

}
#endif