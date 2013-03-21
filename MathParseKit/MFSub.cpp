#include "MFSub.h"
#include "MFOpp.h"
#include "MFConst.h"

using namespace mpk;

MFSub::MFSub(MFunction *lhs,MFunction *rhs){
	if (lhs) m_lhs=lhs->Clone();
	else m_lhs=NULL;
	if (rhs) m_rhs=rhs->Clone();
	else m_rhs=NULL;
	m_type=MF_SUB;
}

MFunction* MFSub::Clone(){
	return new MFSub(m_lhs,m_rhs);
}

bool MFSub::IsOk(){
	if (!m_lhs) return false;
	if (!m_rhs) return false;
	if (!m_lhs->IsOk()) return false;
	if (!m_rhs->IsOk()) return false;
	return true;
}

bool MFSub::IsConstant(MVariablesList* variables){
	if (m_lhs)
		if(!m_lhs->IsConstant(variables)) return false;
	if (m_rhs)
		if(!m_rhs->IsConstant(variables)) return false;
	return true;
}

MFunction* MFSub::Solve(MVariablesList* variables){
	if (!m_lhs || !m_rhs) return new MFConst(0.0);
	MFunction *lhs=m_lhs->Solve(variables);
	MFunction *rhs=m_rhs->Solve(variables);
	if (lhs->GetType()==MF_CONST && rhs->GetType()==MF_CONST){
		double value=((MFConst*)lhs)->GetValue()-((MFConst*)rhs)->GetValue();
		lhs->Release();
		rhs->Release();
		return new MFConst(value);
	}
	MFSub *ret=new MFSub();
	ret->SetLhs(lhs);
	ret->SetRhs(rhs);
	return ret;
}

MFunction* MFSub::Derivate(MVariablesList *variables){
	if (!m_lhs || !m_rhs) return NULL;
	if (m_lhs->IsConstant(variables)){
		if (m_rhs->IsConstant(variables)){
			return new MFConst(0.0);
		}else{
			MFunction *fn=m_rhs->Derivate(variables);
			if (!fn) return NULL;
			MFOpp *ret= new MFOpp();
			ret->SetFn(fn);
			return ret;
		}
	}else{
		if (m_rhs->IsConstant(variables)){
			return m_lhs->Derivate(variables);
		}else{
			MFunction *lhs=m_lhs->Derivate(variables);
			if (!lhs) return NULL;
			MFunction *rhs=m_rhs->Derivate(variables);
			if (!rhs) return NULL;
			MFSub *ret=new MFSub();
			ret->SetLhs(lhs);
			ret->SetRhs(rhs);
			return ret;
		}
	}
}

MVariablesList* MFSub::GetVariablesList(MVariablesList *list){
	if (!m_lhs || !m_rhs) return list;
	list = m_lhs->GetVariablesList(list);
	return m_rhs->GetVariablesList(list);
}

MSistem* MFSub::CalcDominum(MSistem *update){
	if (!m_lhs || !m_rhs) return update;
	update = m_lhs->CalcDominum(update);
	return m_rhs->CalcDominum(update);
}

void MFSub::SetLhs(MFunction *lhs){
	if (m_lhs) m_lhs->Release();
	m_lhs=lhs;
}

void MFSub::SetRhs(MFunction *rhs){
	if (m_rhs) m_rhs->Release();
	m_rhs=rhs;
}

void MFSub::Release(){
	if (m_rhs)	m_rhs->Release();
	if (m_lhs) m_lhs->Release();
	delete this;
}