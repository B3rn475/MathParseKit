#include "MFMul.h"
#include "MFAdd.h"
#include "MFOpp.h"
#include "MFConst.h"

using namespace mtk;

MFMul::MFMul(MFunction *lhs,MFunction *rhs){
	if (lhs) m_lhs=lhs->Clone();
	else m_lhs=NULL;
	if (rhs) m_rhs=rhs->Clone();
	else m_rhs=NULL;
	m_type=MF_MUL;
}

MFunction* MFMul::Clone(){
	return new MFMul(m_lhs,m_rhs);
}

bool MFMul::IsOk(){
	if (!m_lhs) return false;
	if (!m_rhs) return false;
	if (!m_lhs->IsOk()) return false;
	if (!m_rhs->IsOk()) return false;
	return true;
}

bool MFMul::IsConstant(MVariablesList* variables){
	if (m_lhs)
		if(!m_lhs->IsConstant(variables)) return false;
	if (m_rhs)
		if(!m_rhs->IsConstant(variables)) return false;
	return true;
}

MFunction* MFMul::Solve(MVariablesList* variables){
	if (!m_lhs || !m_rhs) return new MFConst(0.0);
	MFunction *lhs=m_lhs->Solve(variables);
	MFunction *rhs=m_rhs->Solve(variables);
	if (lhs->GetType()==MF_CONST && rhs->GetType()==MF_CONST){
		double value=((MFConst*)lhs)->GetValue()*((MFConst*)rhs)->GetValue();
		lhs->Release();
		rhs->Release();
		return new MFConst(value);
	}
	MFMul *ret=new MFMul();
	ret->SetLhs(lhs);
	ret->SetRhs(rhs);
	return ret;
}

MFunction* MFMul::Derivate(MVariablesList *variables){
	if (!m_lhs || !m_rhs) return NULL;
	if (m_lhs->IsConstant(variables)){
		if (m_rhs->IsConstant(variables)){
			return new MFConst(0.0);
		}else{
			MFunction *fn=m_rhs->Derivate(variables);
			if (!fn) return NULL;
			MFMul *ret = new MFMul(m_lhs);
			ret->SetRhs(fn);
			return ret;
		}
	}else{
		if (m_rhs->IsConstant(variables)){
			MFunction *fn=m_lhs->Derivate(variables);
			if (!fn) return NULL;
			MFMul *ret = new MFMul(m_rhs);
			ret->SetRhs(fn);
			return ret;
		}else{
			MFunction *lhs=m_lhs->Derivate(variables);
			if (!lhs) return NULL;
			MFunction *rhs=m_rhs->Derivate(variables);
			if (!rhs) return NULL;
			MFAdd *ret=new MFAdd();
			MFMul *temp1= new MFMul(m_rhs);
			temp1->SetRhs(lhs);
			MFMul *temp2= new MFMul(m_lhs);
			temp2->SetRhs(rhs);
			ret->SetLhs(temp1);
			ret->SetRhs(temp2);
			return ret;
		}
	}
}

MVariablesList* MFMul::GetVariablesList(MVariablesList *list){
	if (!m_lhs || !m_rhs) return list;
	list = m_lhs->GetVariablesList(list);
	return m_rhs->GetVariablesList(list);
}

MSistem* MFMul::CalcDominum(MSistem *update){
	if (!m_lhs || !m_rhs) return update;
	update = m_lhs->CalcDominum(update);
	return m_rhs->CalcDominum(update);
}

void MFMul::SetLhs(MFunction *lhs){
	if (m_lhs) m_lhs->Release();
	m_lhs=lhs;
}

void MFMul::SetRhs(MFunction *rhs){
	if (m_rhs) m_rhs->Release();
	m_rhs=rhs;
}

void MFMul::Release(){
	if (m_rhs) m_rhs->Release();
	if (m_lhs) m_lhs->Release();
	delete this;
}