#include "MFSign.h"
#include "MFAbs.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"

using namespace mpk;

MFSign::MFSign(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_SIGN;
}

MFunction* MFSign::Clone(){
	return new MFSign(m_fn);
}

bool MFSign::IsOk(){
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFSign::IsConstant(MVariablesList* variables){
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFSign::Solve(MVariablesList* variables){
	if (!m_fn) return new MFConst(0.0);
	MFunction *fn=m_fn->Solve(variables);
	if (fn->GetType()==MF_CONST){
		double value=((MFConst*)fn)->GetValue();
		fn->Release();
		if (value == abs(value))
			return new MFConst(1);
		return new MFConst(-1);
	}
	MFSign *ret=new MFSign();
	ret->SetFn(fn);
	return ret;
}

MFunction* MFSign::Derivate(MVariablesList *variables){
	if (!m_fn) return new MFConst(0.0);
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFDiv *ret=new MFDiv(NULL,m_fn);
	ret->SetNum(new MFConst(0.0));
	return ret;
}

MVariablesList* MFSign::GetVariablesList(MVariablesList *list){
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFSign::CalcDominum(MSistem *update){
	if (!m_fn) return update;
	return m_fn->CalcDominum(update);
}

void MFSign::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

void MFSign::Release(){
	if (m_fn) m_fn->Release();
	delete this;
}