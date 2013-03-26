/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFSign.h"
#include "MFAbs.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"

using namespace mpk;

MFSign::MFSign(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_SIGN;
}

MFunction* MFSign::Clone() const{
	return new MFSign(m_fn);
}

bool MFSign::IsOk() const{
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFSign::IsConstant(MVariablesList* variables) const{
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFSign::Solve(MVariablesList* variables) const{
	if (!m_fn) return new MFConst(0.0);
	MFunction *fn=m_fn->Solve(variables);
	if (fn->GetType()==MF_CONST){
		double value=((MFConst*)fn)->GetValue();
		fn->Release();
		if (value == abs(value))
			return new MFConst(1);
		return new MFConst(-1);
	}
	MFSign *ret=new MFSign();
	ret->SetFn(fn);
	return ret;
}

MFunction* MFSign::Derivate(MVariablesList *variables) const{
	if (!m_fn) return new MFConst(0.0);
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFDiv *ret=new MFDiv(NULL,m_fn);
	ret->SetNum(new MFConst(0.0));
	return ret;
}

MVariablesList* MFSign::GetVariablesList(MVariablesList *list) const{
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFSign::GetDomain(MSistem *update) const{
	if (!m_fn) return update;
	return m_fn->GetDomain(update);
}

void MFSign::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

void MFSign::Release(){
	if (m_fn) m_fn->Release();
	delete this;
}