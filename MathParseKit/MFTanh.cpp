#include "MFTanh.h"
#include "MFConst.h"
#include "MFPow.h"
#include "MFMul.h"
#include "MFSub.h"
#include "MFOpp.h"

using namespace mtk;

MFTanh::MFTanh(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_TANH;
}

MFunction* MFTanh::Clone(){
	return new MFTanh(m_argument);
}

bool MFTanh::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFTanh::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFTanh::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=tanh(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFTanh *ret=new MFTanh();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFTanh::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFSub *lhs= new MFSub();
	MFConst *llhs= new MFConst(1.0);
	lhs->SetLhs(llhs);
	MFTanh *arg= new MFTanh(m_argument);
	MFPow *rhs= new MFPow();
	MFConst *exp= new MFConst(2.0);
	rhs->SetBase(arg);
	rhs->SetExponent(exp);
	lhs->SetRhs(rhs);
	ret->SetLhs(lhs);
	return ret;
}

MVariablesList* MFTanh::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFTanh::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFTanh::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFTanh::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}