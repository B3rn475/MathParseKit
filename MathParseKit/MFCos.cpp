#include "MFCos.h"
#include "MFConst.h"
#include "MFOpp.h"
#include "MFMul.h"
#include "MFSin.h"

using namespace mpk;

MFCos::MFCos(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ACOS;
}

MFunction* MFCos::Clone(){
	return new MFCos(m_argument);
}

bool MFCos::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFCos::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFCos::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=cos(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFCos *ret=new MFCos();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFCos::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFOpp *lhs= new MFOpp();
	MFSin *arg= new MFSin(m_argument);
	lhs->SetFn(arg);
	ret->SetLhs(lhs);
	return ret;
}

MVariablesList* MFCos::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFCos::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFCos::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFCos::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}