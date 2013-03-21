#include "MFCoTanh.h"
#include "MFConst.h"
#include "MFPow.h"
#include "MFMul.h"
#include "MFSub.h"
#include "MFOpp.h"

using namespace mtk;

MFCoTanh::MFCoTanh(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_COTANH;
}

MFunction* MFCoTanh::Clone(){
	return new MFCoTanh(m_argument);
}

bool MFCoTanh::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFCoTanh::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFCoTanh::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=1/tanh(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFCoTanh *ret=new MFCoTanh();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFCoTanh::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFSub *lhs= new MFSub();
	MFConst *llhs= new MFConst(1.0);
	lhs->SetLhs(llhs);
	MFCoTanh *arg= new MFCoTanh(m_argument);
	MFPow *rhs= new MFPow();
	MFConst *exp= new MFConst(2.0);
	rhs->SetBase(arg);
	rhs->SetExponent(exp);
	lhs->SetRhs(rhs);
	ret->SetLhs(lhs);
	return ret;
}

MVariablesList* MFCoTanh::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFCoTanh::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFCoTanh::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFCoTanh::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}