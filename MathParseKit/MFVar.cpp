#include "MFVar.h"
#include "MFConst.h"

#include <wchar.h>

using namespace mpk;

MFVar::MFVar(const wchar_t *name, unsigned int len){
	m_type=MF_VAR;
	m_name=NULL;
	SetName(name,len);
}
MFunction* MFVar::Clone(){
	return new MFVar(m_name);
}

bool MFVar::IsOk(){
	if (m_name) return true;
	return false;
}

bool MFVar::IsConstant(MVariablesList *variables){
	if (variables->FindItem(m_name)==-1) return true;
	return false;
}

MFunction* MFVar::Solve(MVariablesList* variables){
	if (!variables) return Clone();
	MVariableElement *element=variables->GetItem(m_name);
	if (element) return new MFConst(element->GetValue());
	return Clone();
}

MFunction* MFVar::Derivate(MVariablesList *variables){
	if (!variables) return NULL;
	if (variables->FindItem(m_name)==-1) return new MFConst(0.0);
	return new MFConst(1.0);
}

MVariablesList* MFVar::GetVariablesList(MVariablesList *list){
	if (!list) list= new MVariablesList();
	if (list->FindItem(m_name)==-1)
	list->Add(m_name);
	return list;
}

MSistem* MFVar::CalcDominum(MSistem *update){
	if (!update) update=new MSistem();
	return update;
}

int MFVar::GetName(wchar_t *buffer){
	wcscpy(buffer,m_name);
	return wcslen(m_name);
}

void MFVar::SetName(const wchar_t *buffer,unsigned int len){
	if (!buffer){
		if (m_name) free(m_name);
		m_name=NULL;
		return;
	};
	if (m_name){
		m_name=(wchar_t*)realloc((void*)m_name,(len+1)*sizeof(wchar_t));
	}else{
		m_name=(wchar_t*)malloc((len+1)*sizeof(wchar_t));
	}
	for (unsigned int i=0; i<len; i++)
	{
		*(m_name+i) = *(buffer+i);
	}
	*(m_name+len) = L'\0';
}

void MFVar::Release(){
	if (m_name)	free(m_name);
	delete this;
}
