/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFLog10.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"
#include <sstream>

using namespace mpk;

MFLog10::MFLog10(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_LOG10;
}

MFunction* MFLog10::Clone() const{
	return new MFLog10(m_argument);
}

bool MFLog10::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFLog10::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFLog10::Solve(MVariablesList* variables) const{
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=log10(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFLog10 *ret=new MFLog10();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFLog10::Derivate(MVariablesList *variables) const{
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	MFDiv *arg= new MFDiv();
	arg->SetNum(new MFConst(1.0));
	MFMul *denum = new MFMul(m_argument);
	denum->SetLhs(new MFConst(M_LN10));
	arg->SetDenum(denum);
	ret->SetLhs(arg);
	ret->SetRhs(fn);
	return ret;
}

MVariablesList* MFLog10::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFLog10::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	update = m_argument->GetDomain(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_MAJOR,*m_argument,z);
	return update;
}

void MFLog10::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

std::wstring MFLog10::ToString() const {
	std::wostringstream stream;
	stream << L"log10(";
	stream << m_argument->ToString();
	stream << L")";
	return stream.str();
}


void MFLog10::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}