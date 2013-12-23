/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MVariableElement.h"

using namespace mpk;

MVariableElement::MVariableElement(const wchar_t* name,double value){
	this->SetName(name);
	this->SetValue(value);
}

MVariableElement::MVariableElement(const std::wstring &name,double value){
	this->SetName(name);
	this->SetValue(value);
}

MVariableElement::MVariableElement(MVariableElement &origin){
	(*this)=origin;
}
void MVariableElement::SetName(const wchar_t* name){
	if (!name) return;
	m_name = name;
}

void MVariableElement::SetName(const std::wstring &name){
	m_name = name;
}