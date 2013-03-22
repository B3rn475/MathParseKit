/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFAcotan.h"
#include "MFConst.h"
#include "MFAdd.h"
#include "MFOpp.h"
#include "MFMul.h"
#include "MFDiv.h"
#include "MFPow.h"

using namespace mpk;

MFAcotan::MFAcotan(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ACOTAN;
}

MFunction* MFAcotan::Clone(){
	return new MFAcotan(m_argument);
}

bool MFAcotan::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAcotan::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAcotan::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=atan(1/((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFAcotan *ret=new MFAcotan();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFAcotan::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFOpp *lhs= new MFOpp();
	MFDiv *arg= new MFDiv();
	MFAdd *aarg = new MFAdd();
	MFPow *aarghs = new MFPow(m_argument);
	aarghs->SetExponent(new MFConst(2.0));
	aarg->SetLhs(new MFConst(1.0));
	aarg->SetRhs(aarghs);
	arg->SetDenum(aarg);
	arg->SetNum(new MFConst(1.0));
	lhs->SetFn(arg);
	ret->SetLhs(lhs);
	return ret;
}

MVariablesList* MFAcotan::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAcotan::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFAcotan::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFAcotan::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}