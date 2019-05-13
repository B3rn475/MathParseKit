/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFPer.h"
#include "MFAdd.h"
#include "MFOpp.h"
#include "MFConst.h"
#include <sstream>

using namespace mpk;

MFPer::MFPer(const MFunction *lhs,const MFunction *rhs){
	if (lhs) m_lhs=lhs->Clone();
	else m_lhs=NULL;
	if (rhs) m_rhs=rhs->Clone();
	else m_rhs=NULL;
	m_type=MF_PER;
}

MFunction* MFPer::Clone() const{
	return new MFPer(m_lhs,m_rhs);
}

bool MFPer::IsOk() const{
	if (!m_lhs) return false;
	if (!m_rhs) return false;
	if (!m_lhs->IsOk()) return false;
	if (!m_rhs->IsOk()) return false;
	return true;
}

bool MFPer::IsConstant(MVariablesList* variables) const{
	if (m_lhs)
		if(!m_lhs->IsConstant(variables)) return false;
	if (m_rhs)
		if(!m_rhs->IsConstant(variables)) return false;
	return true;
}

MFunction* MFPer::Solve(MVariablesList* variables) const{
	if (!m_lhs || !m_rhs) return new MFConst(0.0);
	MFunction *lhs=m_lhs->Solve(variables);
	MFunction *rhs=m_rhs->Solve(variables);
	if (lhs->GetType()==MF_CONST && rhs->GetType()==MF_CONST){
		//double value=((MFConst*)lhs)->GetValue()*((MFConst*)rhs)->GetValue();
		//val1% of val2
		double val1 = ((MFConst*)lhs)->GetValue();
		double val2 = ((MFConst*)rhs)->GetValue();
		double value = val1 * (val2 / 100);

		lhs->Release();
		rhs->Release();
		return new MFConst(value);
	}
	MFPer *ret=new MFPer();
	ret->SetLhs(lhs);
	ret->SetRhs(rhs);
	return ret;
}

MFunction* MFPer::Derivate(MVariablesList *variables) const{
	if (!m_lhs || !m_rhs) return NULL;
	if (m_lhs->IsConstant(variables)){
		if (m_rhs->IsConstant(variables)){
			return new MFConst(0.0);
		}else{
			MFunction *fn=m_rhs->Derivate(variables);
			if (!fn) return NULL;
			MFPer *ret = new MFPer(m_lhs);
			ret->SetRhs(fn);
			return ret;
		}
	}else{
		if (m_rhs->IsConstant(variables)){
			MFunction *fn=m_lhs->Derivate(variables);
			if (!fn) return NULL;
			MFPer *ret = new MFPer(m_rhs);
			ret->SetRhs(fn);
			return ret;
		}else{
			MFunction *lhs=m_lhs->Derivate(variables);
			if (!lhs) return NULL;
			MFunction *rhs=m_rhs->Derivate(variables);
			if (!rhs) return NULL;
			MFAdd *ret=new MFAdd();
			MFPer *temp1= new MFPer(m_rhs);
			temp1->SetRhs(lhs);
			MFPer *temp2= new MFPer(m_lhs);
			temp2->SetRhs(rhs);
			ret->SetLhs(temp1);
			ret->SetRhs(temp2);
			return ret;
		}
	}
}

MVariablesList* MFPer::GetVariablesList(MVariablesList *list) const{
	if (!m_lhs || !m_rhs) return list;
	list = m_lhs->GetVariablesList(list);
	return m_rhs->GetVariablesList(list);
}

MSistem* MFPer::GetDomain(MSistem *update) const{
	if (!m_lhs || !m_rhs) return update;
	update = m_lhs->GetDomain(update);
	return m_rhs->GetDomain(update);
}

void MFPer::SetLhs(MFunction *lhs){
	if (m_lhs) m_lhs->Release();
	m_lhs=lhs;
}

void MFPer::SetRhs(MFunction *rhs){
	if (m_rhs) m_rhs->Release();
	m_rhs=rhs;
}

std::wstring MFPer::ToString() const {
	std::wostringstream stream;
	bool parentesis = m_lhs->GetType() == MF_ADD || m_lhs->GetType() == MF_SUB;
	if (parentesis)
		stream << "(";
	stream << m_lhs->ToString();
	if (parentesis)
		stream << ")";
	stream << L"*";
	parentesis = m_rhs->GetType() == MF_ADD || m_rhs->GetType() == MF_SUB;
	if (parentesis)
		stream << "(";
	stream << m_rhs->ToString();
	if (parentesis)
		stream << ")";
	return stream.str();
}

void MFPer::Release(){
	if (m_rhs) m_rhs->Release();
	if (m_lhs) m_lhs->Release();
	delete this;
}