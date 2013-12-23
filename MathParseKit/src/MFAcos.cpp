/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFAcos.h"
#include "MFConst.h"
#include "MFDiv.h"
#include "MFOpp.h"
#include "MFSqrt.h"
#include "MFPow.h"
#include "MFSub.h"
#include <sstream>

using namespace mpk;

MFAcos::MFAcos(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ASIN;
}

MFunction* MFAcos::Clone() const{
	return new MFAcos(m_argument);
}

bool MFAcos::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAcos::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAcos::Solve(MVariablesList* variables) const{
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

MFunction* MFAcos::Derivate(MVariablesList *variables) const{
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

MVariablesList* MFAcos::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAcos::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	update = m_argument->GetDomain(update);
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

std::wstring MFAcos::ToString() const {
	std::wostringstream stream;
	stream << L"acos(";
	stream << m_argument->ToString();
	stream << L")";
	return stream.str();
}

void MFAcos::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}