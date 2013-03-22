/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MSistem.h"

using namespace mpk;

MSistem::MSistem(){
	m_list=NULL;
	m_count=0;
}

MSistem::MSistem(MSistem &origin){
	m_list=NULL;
	m_count=0;
	for(int i=0;i<origin.Count();i++){
		Add(*origin.Item(i));
	}
}

int MSistem::Add(){
	MSistemItem **walker=&m_list;
	while ((*walker)){
		walker=&((*walker)->next);
	}
	(*walker)=(MSistemItem*)malloc(sizeof(MSistemItem));
	(*walker)->next=NULL;
	(*walker)->relation=new MRelation();
	return ++m_count;
}

int MSistem::Add(int type, MFunction &lhs, MFunction &rhs){
	MSistemItem **walker=&m_list;
	while ((*walker)){
		walker=&((*walker)->next);
	}
	(*walker)=(MSistemItem*)malloc(sizeof(MSistemItem));
	(*walker)->next=NULL;
	(*walker)->relation = new MRelation(type,&lhs,&rhs);
	return ++m_count;
}

int MSistem::Add(MRelation &relation){
	MSistemItem **walker=&m_list;
	while ((*walker)){
		walker=&((*walker)->next);
	}
	(*walker)=(MSistemItem*)malloc(sizeof(MSistemItem));
	(*walker)->next=NULL;
	(*walker)->relation=new MRelation(relation);
	return ++m_count;
}

MRelation *MSistem::Item(int index){
	if ((index>=m_count)||(index<0)) return NULL;
	MSistemItem *walker=m_list;
	for (int i=0;i<index;i++){
		walker=walker->next;
	}
	return walker->relation;
}

int MSistem::Remove(int index){
	if ((index>=m_count)||(index<0)) return -1;
	MSistemItem **walker=&m_list;
	for (int i=0;i<index;i++){
		walker=&((*walker)->next);
	}
	MSistemItem *temp=(*walker);
	(*walker)=(*walker)->next;
	delete temp->relation;
	free(temp);
	return --m_count;
}

bool MSistem::Solve(MVariablesList *variables){
	for (int i=0; i<m_count;i++){
		if (!Item(i)->IsTrue(variables)) return false;
	}
	return true;
}

MSistem::~MSistem(){
	if (m_count==0) return;
	while (Remove(0)){}
}