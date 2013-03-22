/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFPow.h"
#include "MFMul.h"
#include "MFDiv.h"
#include "MFConst.h"
#include "MFAdd.h"
#include "MFLn.h"
#include "MFSub.h"

using namespace mpk;

MFPow::MFPow(MFunction *base,MFunction *exponent){
	if (base) m_base=base->Clone();
	else m_base=NULL;
	if (exponent) m_exponent=exponent->Clone();
	else m_exponent=NULL;
	m_type=MF_POW;
}

MFunction* MFPow::Clone(){
	return new MFPow(m_base,m_exponent);
}

bool MFPow::IsOk(){
	if (!m_base) return false;
	if (!m_exponent) return false;
	if (!m_base->IsOk()) return false;
	if (!m_exponent->IsOk()) return false;
	return true;
}

bool MFPow::IsConstant(MVariablesList* variables){
	if (m_base)
		if(!m_base->IsConstant(variables)) return false;
	if (m_exponent)
		if(!m_exponent->IsConstant(variables)) return false;
	return true;
}

MFunction* MFPow::Solve(MVariablesList* variables){
	if (!m_base || !m_exponent) return new MFConst(0.0);
	MFunction *base=m_base->Solve(variables);
	MFunction *exponent=m_exponent->Solve(variables);
	if (base->GetType()==MF_CONST && exponent->GetType()==MF_CONST){
		double value=pow(((MFConst*)base)->GetValue(),((MFConst*)exponent)->GetValue());
		base->Release();
		exponent->Release();
		return new MFConst(value);
	}
	MFPow *ret=new MFPow();
	ret->SetBase(base);
	ret->SetExponent(exponent);
	return ret;
}

MFunction* MFPow::Derivate(MVariablesList *variables){
	if (!m_base || !m_exponent) return NULL;
	if (m_base->IsConstant(variables)){
		if (m_exponent->IsConstant(variables)){
			return new MFConst(0.0);
		}else{
			MFunction *fn=m_exponent->Derivate(variables);
			if (!fn) return NULL;
			MFMul *ret = new MFMul();
			MFMul *lhs = new MFMul(this);
			lhs->SetRhs(new MFLn(m_base));
			ret->SetLhs(lhs);
			ret->SetRhs(fn);
			return ret;
		}
	}else{
		if (m_exponent->IsConstant(variables)){
			MFunction *fn=m_base->Derivate(variables);
			if (!fn) return NULL;
			MFMul *ret = new MFMul(m_exponent);
			MFMul *rett = new MFMul();
			MFPow *rhs = new MFPow(m_base);
			MFSub *exp = new MFSub(m_exponent);
			exp->SetRhs(new MFConst(1.0));
			rhs->SetExponent(exp);
			rett->SetLhs(rhs);
			rett->SetRhs(fn);
			ret->SetRhs(rett);
			return ret;
		}else{
			MFunction *base=m_base->Derivate(variables);
			if (!base) return NULL;
			MFunction *exp=m_exponent->Derivate(variables);
			if (!exp){
				base->Release();
				return NULL;
			}
			MFMul *ret = new MFMul(this);
			MFAdd *rhs = new MFAdd();
			MFMul *rlhs = new MFMul();
			rlhs->SetLhs(exp);
			rlhs->SetRhs(new MFLn(m_base));
			MFMul *rrhs = new MFMul(m_exponent);
			MFDiv *rrrhs = new MFDiv();
			rrrhs->SetNum(base);
			rrrhs->SetDenum(m_base->Clone());
			rrhs->SetRhs(rrrhs);
			rhs->SetLhs(rlhs);
			rhs->SetRhs(rrhs);
			ret->SetRhs(rhs);
			return ret;
		}
	}
}

MVariablesList* MFPow::GetVariablesList(MVariablesList *list){
	if (!m_base || !m_exponent) return list;
	list = m_base->GetVariablesList(list);
	return m_exponent->GetVariablesList(list);
}

MSistem* MFPow::CalcDominum(MSistem *update){
	if (!m_base || !m_exponent) return update;
	update = m_base->CalcDominum(update);
	update = m_exponent->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_FINITE,*this,z);
	return update;
}

void MFPow::SetBase(MFunction *base){
	if (m_base) m_base->Release();
	m_base=base;
}

void MFPow::SetExponent(MFunction *exponent){
	if (m_exponent) m_exponent->Release();
	m_exponent=exponent;
}

void MFPow::Release(){
	if (m_base)	m_base->Release();
	if (m_exponent) m_exponent->Release();
	delete this;
}