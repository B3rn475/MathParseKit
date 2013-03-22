/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFOpp.h"
#include "MFConst.h"

using namespace mpk;

MFOpp::MFOpp(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_OPP;
}

MFunction* MFOpp::Clone(){
	return new MFOpp(m_fn);
}

bool MFOpp::IsOk(){
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFOpp::IsConstant(MVariablesList* variables){
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFOpp::Solve(MVariablesList* variables){
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

MFunction* MFOpp::Derivate(MVariablesList *variables){
	if (!m_fn) return NULL;
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_fn->Derivate(variables);
	if (!fn) return NULL;
	MFOpp *ret=new MFOpp();
	ret->SetFn(fn);
	return ret;
}

MVariablesList* MFOpp::GetVariablesList(MVariablesList *list){
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFOpp::CalcDominum(MSistem *update){
	if (!m_fn) return update;
	return m_fn->CalcDominum(update);
}

void MFOpp::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

void MFOpp::Release(){
	if (m_fn)	m_fn->Release();
	delete this;
}