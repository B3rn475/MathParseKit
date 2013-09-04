/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFVar.h"
#include "MFConst.h"

#include <wchar.h>

using namespace mpk;

MFVar::MFVar(const wchar_t *name, unsigned int len){
	m_type=MF_VAR;
	SetName(name,len);
}

MFVar::MFVar(const std::wstring name){
	m_type=MF_VAR;
	SetName(name);
}

MFunction* MFVar::Clone() const{
	return new MFVar(m_name);
}

bool MFVar::IsOk() const{
	if (m_name.length() > 0) return true;
	return false;
}

bool MFVar::IsConstant(MVariablesList *variables) const{
	if (variables->FindItem(m_name)==-1) return true;
	return false;
}

MFunction* MFVar::Solve(MVariablesList* variables) const{
	if (!variables) return Clone();
	MVariableElement *element=variables->GetItem(m_name);
	if (element) return new MFConst(element->GetValue());
	return Clone();
}

MFunction* MFVar::Derivate(MVariablesList *variables) const{
	if (!variables) return NULL;
	if (variables->FindItem(m_name)==-1) return new MFConst(0.0);
	return new MFConst(1.0);
}

MVariablesList* MFVar::GetVariablesList(MVariablesList *list) const{
	if (!list) list= new MVariablesList();
	if (list->FindItem(m_name)==-1)
	list->Add(m_name);
	return list;
}

MSistem* MFVar::GetDomain(MSistem *update) const{
	if (!update) update=new MSistem();
	return update;
}

void MFVar::SetName(const wchar_t *buffer,unsigned int len){
	wchar_t *tName;
	tName=new wchar_t[len+1];
	wcsncpy(tName, buffer, len);
	m_name = tName;
	free(tName);
}

void MFVar::SetName(const std::wstring name){
	m_name = name;
}

std::wstring MFVar::ToString() const {
	return m_name;
}

void MFVar::Release(){
	delete this;
}
