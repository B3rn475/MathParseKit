/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFLn.h"
#include "MFConst.h"
#include "MFDiv.h"
#include "MFMul.h"
#include <sstream>

using namespace mpk;

MFLn::MFLn(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_LN;
}

MFunction* MFLn::Clone() const{
	return new MFLn(m_argument);
}

bool MFLn::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFLn::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFLn::Solve(MVariablesList* variables) const{
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=log(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFLn *ret=new MFLn();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFLn::Derivate(MVariablesList *variables) const{
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	MFDiv *arg= new MFDiv();
	arg->SetNum(new MFConst(1.0));
	arg->SetDenum(m_argument->Clone());
	ret->SetLhs(arg);
	ret->SetRhs(fn);
	return ret;
}

MVariablesList* MFLn::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFLn::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	update = m_argument->GetDomain(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_MAJOR,*m_argument,z);
	return update;
}

void MFLn::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

std::wstring MFLn::ToString() const {
	std::wostringstream stream;
	stream << L"ln(";
	stream << m_argument->ToString();
	stream << L")";
	return stream.str();
}

void MFLn::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}