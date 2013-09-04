/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFCoTan.h"
#include "MFConst.h"
#include "MFPow.h"
#include "MFMul.h"
#include "MFDiv.h"
#include "MFSin.h"
#include "MFOpp.h"
#include <sstream>

using namespace mpk;

MFCoTan::MFCoTan(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_COTAN;
}

MFunction* MFCoTan::Clone() const{
	return new MFCoTan(m_argument);
}

bool MFCoTan::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFCoTan::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFCoTan::Solve(MVariablesList* variables) const{
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=1/tan(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFCoTan *ret=new MFCoTan();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFCoTan::Derivate(MVariablesList *variables) const{
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFDiv *lhs= new MFDiv();
	MFConst *num= new MFConst(1.0);
	lhs->SetNum(num);
	MFSin *arg= new MFSin(m_argument);
	MFPow *denum= new MFPow();
	MFConst *exp= new MFConst(2.0);
	denum->SetBase(arg);
	denum->SetExponent(exp);
	lhs->SetDenum(denum);
	MFOpp *op=new MFOpp();
	op->SetFn(lhs);
	ret->SetLhs(op);
	return ret;
}

MVariablesList* MFCoTan::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFCoTan::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	return m_argument->GetDomain(update);
}

void MFCoTan::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

std::wstring MFCoTan::ToString() const {
	std::wostringstream stream;
	stream << L"cotan(";
	stream << m_argument->ToString();
	stream << L")";
	return stream.str();
}

void MFCoTan::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}