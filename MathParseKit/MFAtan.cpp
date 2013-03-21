#include "MFAtan.h"
#include "MFConst.h"
#include "MFDiv.h"
#include "MFMul.h"
#include "MFAdd.h"
#include "MFPow.h"

using namespace mtk;

MFAtan::MFAtan(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_COTAN;
}

MFunction* MFAtan::Clone(){
	return new MFAtan(m_argument);
}

bool MFAtan::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAtan::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAtan::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=atan(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFAtan *ret=new MFAtan();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFAtan::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFDiv *arg= new MFDiv();
	MFAdd *aarg = new MFAdd();
	MFPow *aarghs = new MFPow(m_argument);
	aarghs->SetExponent(new MFConst(2.0));
	aarg->SetLhs(new MFConst(1.0));
	aarg->SetRhs(aarghs);
	arg->SetDenum(aarg);
	arg->SetNum(new MFConst(1.0));
	ret->SetLhs(arg);
	return ret;
}

MVariablesList* MFAtan::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAtan::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFAtan::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFAtan::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}