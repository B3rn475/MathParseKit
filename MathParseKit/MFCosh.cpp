/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFCosh.h"
#include "MFConst.h"
#include "MFCos.h"
#include "MFMul.h"

using namespace mpk;

MFCosh::MFCosh(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_COSH;
}

MFunction* MFCosh::Clone() const{
	return new MFCosh(m_argument);
}

bool MFCosh::IsOk() const{
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFCosh::IsConstant(MVariablesList* variables) const{
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFCosh::Solve(MVariablesList* variables) const{
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=cosh(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFCosh *ret=new MFCosh();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFCosh::Derivate(MVariablesList *variables) const{
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFCos *arg= new MFCos(m_argument);
	ret->SetLhs(arg);
	return ret;
}

MVariablesList* MFCosh::GetVariablesList(MVariablesList *list) const{
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFCosh::GetDomain(MSistem *update) const{
	if (!m_argument) return update;
	return m_argument->GetDomain(update);
}

void MFCosh::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFCosh::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}