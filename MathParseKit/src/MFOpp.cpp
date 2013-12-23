/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFOpp.h"
#include "MFConst.h"
#include <sstream>

using namespace mpk;

MFOpp::MFOpp(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_OPP;
}

MFunction* MFOpp::Clone() const{
	return new MFOpp(m_fn);
}

bool MFOpp::IsOk() const{
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFOpp::IsConstant(MVariablesList* variables) const{
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFOpp::Solve(MVariablesList* variables) const{
	if (!m_fn) return new MFConst(0.0);
	MFunction *fn=m_fn->Solve(variables);
	if (fn->GetType()==MF_CONST){
		double value=-((MFConst*)fn)->GetValue();
		fn->Release();
		return new MFConst(value);
	}
	MFOpp *ret=new MFOpp();
	ret->SetFn(fn);
	return ret;
}

MFunction* MFOpp::Derivate(MVariablesList *variables) const{
	if (!m_fn) return NULL;
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_fn->Derivate(variables);
	if (!fn) return NULL;
	MFOpp *ret=new MFOpp();
	ret->SetFn(fn);
	return ret;
}

MVariablesList* MFOpp::GetVariablesList(MVariablesList *list) const{
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFOpp::GetDomain(MSistem *update) const{
	if (!m_fn) return update;
	return m_fn->GetDomain(update);
}

void MFOpp::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

std::wstring MFOpp::ToString() const {
	std::wostringstream stream;
	stream << L"-";
	stream << m_fn->ToString();
	return stream.str();
}

void MFOpp::Release(){
	if (m_fn)	m_fn->Release();
	delete this;
}