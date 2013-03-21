#include "MFConst.h"

using namespace mpk;

MFConst::MFConst(double value){
	m_type=MF_CONST;
	m_value=value;
}

MFunction* MFConst::Clone(){
	return new MFConst(m_value);
}

bool MFConst::IsOk(){
	return true;
}

bool MFConst::IsConstant(MVariablesList* variables){
	return true;
}

MFunction* MFConst::Solve(MVariablesList* variables){
	return this->Clone();
}

MFunction* MFConst::Derivate(MVariablesList *){
	return new MFConst();
}

MVariablesList* MFConst::GetVariablesList(MVariablesList *list){
	if (!list) list= new MVariablesList();
	return list;
}

MSistem* MFConst::CalcDominum(MSistem *update){
	if (!update) update=new MSistem();
	return update;
}

bool MFConst::operator==(MFConst &B)const{
	return (m_value==B.m_value);
}
bool MFConst::operator>=(MFConst &B)const{
	return (m_value>=B.m_value);
}
bool MFConst::operator<=(MFConst &B)const{
	return (m_value<=B.m_value);
}
bool MFConst::operator>(MFConst &B)const{
	return (m_value>B.m_value);
}
bool MFConst::operator<(MFConst &B)const{
	return (m_value<B.m_value);
}

void MFConst::Release(){
	delete this;
}