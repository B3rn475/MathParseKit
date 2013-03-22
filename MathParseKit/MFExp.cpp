/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFExp.h"
#include "MFConst.h"
#include "MFMul.h"

using namespace mpk;

MFExp::MFExp(MFunction *exponent){
	if (exponent) m_exponent=exponent->Clone();
	else m_exponent=NULL;
	m_type=MF_EXP;
}

MFunction* MFExp::Clone(){
	return new MFExp(m_exponent);
}

bool MFExp::IsOk(){
	if (!m_exponent) return false;
	if (!m_exponent->IsOk()) return false;
	return true;
}

bool MFExp::IsConstant(MVariablesList* variables){
	if (m_exponent)
		if(!m_exponent->IsConstant(variables)) return false;
	return true;
}

MFunction* MFExp::Solve(MVariablesList* variables){
	if (!m_exponent) return new MFConst(0.0);
	MFunction *exponent=m_exponent->Solve(variables);
	if (exponent->GetType()==MF_CONST){
		double value=exp(((MFConst*)exponent)->GetValue());
		exponent->Release();
		return new MFConst(value);
	}
	MFExp *ret=new MFExp();
	ret->SetExponent(exponent);
	return ret;
}

MFunction* MFExp::Derivate(MVariablesList *variables){
	if (!m_exponent) return NULL;
	if (m_exponent->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_exponent->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul(this);
	ret->SetRhs(fn);
	return ret;
}

MVariablesList* MFExp::GetVariablesList(MVariablesList *list){
	if (!m_exponent) return list;
	return m_exponent->GetVariablesList(list);
}

MSistem* MFExp::CalcDominum(MSistem *update){
	if (!m_exponent) return update;
	return m_exponent->CalcDominum(update);
}

void MFExp::SetExponent(MFunction *exponent){
	if (m_exponent) m_exponent->Release();
	m_exponent=exponent;
}

void MFExp::Release(){
	if (m_exponent) m_exponent->Release();
	delete this;
}