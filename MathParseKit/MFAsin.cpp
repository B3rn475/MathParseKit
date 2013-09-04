/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFAsin.h"
#include "MFConst.h"
#include "MFDiv.h"
#include "MFPow.h"
#include "MFSqrt.h"
#include "MFSub.h"
#include <sstream>

using namespace mpk;

MFAsin::MFAsin(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ASIN;
}

MFunction* MFAsin::Clone() const{
	return new MFAsin(m_argument);
}

bool MFAsin::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAsin::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAsin::Solve(MVariablesList* variables) const{
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=asin(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFAsin *ret=new MFAsin();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFAsin::Derivate(MVariablesList *variables) const{
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFDiv *ret= new MFDiv();
	ret->SetNum(fn);
	MFSqrt *arg= new MFSqrt();
	MFSub *aarg = new MFSub();
	MFPow *aarghs = new MFPow(m_argument);
	aarghs->SetExponent(new MFConst(2.0));
	aarg->SetLhs(new MFConst(1.0));
	aarg->SetRhs(aarghs);
	arg->SetFn(aarg);
	ret->SetDenum(arg);
	return ret;
}

MVariablesList* MFAsin::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAsin::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	update = m_argument->GetDomain(update);
	if (!update) update=new MSistem();
	MFConst z(-1.0);
	update->Add(MR_MAJOR_OR_EQUAL,*m_argument,z);
	z.SetValue(1.0);
	update->Add(MR_MINOR_OR_EQUAL,*m_argument,z);
	return update;
}

void MFAsin::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

std::wstring MFAsin::ToString() const {
	std::wostringstream stream;
	stream << L"asin(";
	stream << m_argument->ToString();
	stream << L")";
	return stream.str();
}

void MFAsin::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}