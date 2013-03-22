/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MRelation.h"
#include "MFConst.h"

#include <limits>

using namespace mpk;

template<typename T> bool is_finite(T arg)
{
    return arg == arg && 
           arg != std::numeric_limits<T>::infinity() &&
           arg != -std::numeric_limits<T>::infinity();
}

MRelation::MRelation(int type,MFunction *lhs,MFunction *rhs){
	m_type=type;
	m_lhs=lhs->Clone();
	m_rhs=rhs->Clone();
}

MRelation::MRelation(MRelation &origin){
	m_type=origin.m_type;
	m_lhs=origin.m_lhs->Clone();
	m_rhs=origin.m_rhs->Clone();
}

MRelation::~MRelation(){
	m_lhs->Release();
	m_rhs->Release();
}

bool MRelation::IsTrue(MVariablesList *variables){
	MFunction *flhs,*frhs;
	flhs=m_lhs->Solve(variables);
	if (flhs->GetType()!=MF_CONST){
		delete flhs;
		return false;
	}
	frhs=m_rhs->Solve(variables);
	if (frhs->GetType()!=MF_CONST){
		delete flhs;
		delete frhs;
		return false;
	}
	MFConst	*l, *r;
	l=(MFConst*)flhs;
	r=(MFConst*)frhs;
	bool ret=false;
	if (m_type & MR_EQUAL)
		if (*l==*r)	ret = true;
	if (m_type & MR_MAJOR)
		if (*l>*r) ret = true;
	if (m_type & MR_MINOR)
		if (*l<*r) ret = true;
	if (m_type & MR_FINITE)
		if (is_finite(l->GetValue())) ret=true;
	delete l;
	delete r;
	return ret;
}

MVariablesList* MRelation::GetVariablesList(){
	MVariablesList *list=m_lhs->GetVariablesList();
	return m_rhs->GetVariablesList(list);
}

MRelation *MRelation::Solve(MVariablesList *variables){
	MRelation *ret=new MRelation(m_type);
	ret->m_lhs=m_lhs->Solve(variables);
	ret->m_rhs=m_rhs->Solve(variables);
	return ret;
}

void MRelation::SetLeftFunction(MFunction &origin){
	if(m_lhs) delete m_lhs;
	m_lhs=origin.Clone();
}

void MRelation::GetRightFunction(MFunction &origin){
	if(m_rhs) delete m_lhs;
	m_rhs=origin.Clone();
}

MFunction *MRelation::GetLeftFunction(){
	return m_lhs->Clone();
}

MFunction *MRelation::GetRightFunction(){
	return m_rhs->Clone();
}
