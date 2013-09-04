/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MFConst.h"
#include <sstream>

using namespace mpk;

MFConst::MFConst(double value){
	m_type=MF_CONST;
	m_value=value;
}

MFunction* MFConst::Clone() const{
	return new MFConst(m_value);
}

bool MFConst::IsOk() const{
	return true;
}

bool MFConst::IsConstant(MVariablesList* variables) const{
	return true;
}

MFunction* MFConst::Solve(MVariablesList* variables) const{
	return this->Clone();
}

MFunction* MFConst::Derivate(MVariablesList *) const{
	return new MFConst();
}

MVariablesList* MFConst::GetVariablesList(MVariablesList *list) const{
	if (!list) list= new MVariablesList();
	return list;
}

MSistem* MFConst::GetDomain(MSistem *update) const{
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

std::wstring MFConst::ToString() const {
	std::wostringstream stream;
	stream << m_value;
	return stream.str();
}

void MFConst::Release(){
	delete this;
}