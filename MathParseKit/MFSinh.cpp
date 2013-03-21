#include "MFSinh.h"
#include "MFConst.h"
#include "MFCos.h"
#include "MFMul.h"

using namespace mpk;

MFSinh::MFSinh(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_SINH;
}

MFunction* MFSinh::Clone(){
	return new MFSinh(m_argument);
}

bool MFSinh::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFSinh::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFSinh::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=sinh(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFSinh *ret=new MFSinh();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFSinh::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFCos *arg= new MFCos(m_argument);
	ret->SetLhs(arg);
	return ret;
}

MVariablesList* MFSinh::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFSinh::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFSinh::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFSinh::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}