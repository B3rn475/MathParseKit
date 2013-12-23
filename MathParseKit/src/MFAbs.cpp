/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFAbs.h"
#include "MFSign.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"
#include <sstream>

using namespace mpk;

MFAbs::MFAbs(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_ABS;
}

MFunction* MFAbs::Clone() const{
	return new MFAbs(m_fn);
}

bool MFAbs::IsOk() const{
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFAbs::IsConstant(MVariablesList* variables) const{
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAbs::Solve(MVariablesList* variables) const{
	if (!m_fn) return new MFConst(0.0);
	MFunction *fn=m_fn->Solve(variables);
	if (fn->GetType()==MF_CONST){
		double value=abs(((MFConst*)fn)->GetValue());
		fn->Release();
		return new MFConst(value);
	}
	MFAbs *ret=new MFAbs();
	ret->SetFn(fn);
	return ret;
}

MFunction* MFAbs::Derivate(MVariablesList *variables) const{
	if (!m_fn) return new MFConst(0.0);
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_fn->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret=new MFMul();
	ret->SetLhs(fn);
	MFSign *rhs=new MFSign(m_fn);
	ret->SetRhs(rhs);
	return ret;
}

MVariablesList* MFAbs::GetVariablesList(MVariablesList *list) const{
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFAbs::GetDomain(MSistem *update) const{
	if (!m_fn) return update;
	return m_fn->GetDomain(update);
}

void MFAbs::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

std::wstring MFAbs::ToString() const {
	std::wostringstream stream;
	stream << L"abs(";
	stream << m_fn->ToString();
	stream << L")";
	return stream.str();
}

void MFAbs::Release(){
	if (m_fn) m_fn->Release();
	delete this;
}