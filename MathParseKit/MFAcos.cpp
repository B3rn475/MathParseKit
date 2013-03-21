#include "MFAcos.h"
#include "MFConst.h"
#include "MFDiv.h"
#include "MFOpp.h"
#include "MFSqrt.h"
#include "MFPow.h"
#include "MFSub.h"

using namespace mtk;

MFAcos::MFAcos(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ASIN;
}

MFunction* MFAcos::Clone(){
	return new MFAcos(m_argument);
}

bool MFAcos::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAcos::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAcos::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=acos(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFAcos *ret=new MFAcos();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFAcos::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFOpp *ret= new MFOpp();
	MFDiv *rarg= new MFDiv();
	MFSqrt *arg= new MFSqrt();
	MFSub *aarg = new MFSub();
	MFPow *aarghs = new MFPow(m_argument);
	aarghs->SetExponent(new MFConst(2.0));
	aarg->SetLhs(new MFConst(1.0));
	aarg->SetRhs(aarg);
	arg->SetFn(aarg);
	rarg->SetNum(fn);
	rarg->SetDenum(arg);
	ret->SetFn(rarg);
	return ret;
}

MVariablesList* MFAcos::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAcos::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	update = m_argument->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(-1.0);
	update->Add(MR_MAJOR_OR_EQUAL,*m_argument,z);
	z.SetValue(1.0);
	update->Add(MR_MINOR_OR_EQUAL,*m_argument,z);
	return update;
}

void MFAcos::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFAcos::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}