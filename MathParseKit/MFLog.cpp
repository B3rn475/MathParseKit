#include "MFLog.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"
#include "MFLn.h"

using namespace mpk;

MFLog::MFLog(MFunction *base,MFunction *argument){
	if (base) this->m_base=base->Clone();
	else m_base=NULL;
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_LOG;
}

MFunction* MFLog::Clone(){
	return new MFLog(m_base,m_argument);
}

bool MFLog::IsOk(){
	if (!m_base) return false;
	if (!m_argument) return false;
	if (!m_base->IsOk()) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFLog::IsConstant(MVariablesList* variables){
	if (m_base)
		if(!m_base->IsConstant(variables)) return false;
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFLog::Solve(MVariablesList* variables){
	if (!m_base || !m_argument) return new MFConst(0.0);
	MFunction *base=m_base->Solve(variables);
	MFunction *argument=m_argument->Solve(variables);
	if (base->GetType()==MF_CONST && argument->GetType()==MF_CONST){
		double value=log(((MFConst*)argument)->GetValue())/log(((MFConst*)base)->GetValue());
		base->Release();
		argument->Release();
		return new MFConst(value);
	}
	MFLog *ret=new MFLog();
	ret->SetBase(base);
	ret->SetArgument(argument);
	return ret;
}

MFunction *MFLog::Derivate(MVariablesList *variables){
	if (!m_base || !m_argument) return NULL;
	if (m_base->IsConstant(variables) && m_argument->IsConstant(variables)){
		return new MFConst(0.0);
	}
	MFDiv *eq= new MFDiv();
	eq->SetNum(new MFLn(m_argument));
	eq->SetDenum(new MFLn(m_base));
	MFunction *ret=eq->Derivate(variables);
	eq->Release();
	delete eq;
	return ret;
}

MVariablesList* MFLog::GetVariablesList(MVariablesList *list){
	if (!m_base || !m_argument) return list;
	list = m_base->GetVariablesList(list);
	return m_argument->GetVariablesList(list);
}

MSistem* MFLog::CalcDominum(MSistem *update){
	if (!m_base || !m_argument) return update;
	update = m_base->CalcDominum(update);
	update = m_argument->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_MAJOR,*m_base,z);
	update->Add(MR_MAJOR,*m_argument,z);
	z.SetValue(1.0);
	update->Add(MR_NOT_EQUAL,*m_base,z);
	return update;
}

void MFLog::SetBase(MFunction *base){
	if (m_base) m_base->Release();
	m_base=base;
}

void MFLog::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFLog::Release(){
	if (m_argument)	m_argument->Release();
	if (m_base) m_base->Release();
	delete this;
}