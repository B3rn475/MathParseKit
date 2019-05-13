/*!
 * \file
 * \author Carlo Bernaschina (www.bernaschina.com)
 * \copyright Copyright 2013 Carlo Bernaschina. All rights reserved.
 * \license This project is released under the GNU Lesser General Public License.
 */

#include "MParser.h"
#include <wctype.h>
#include <stdio.h>
#include <wchar.h>
#include <algorithm>

using namespace mpk;

MParser::MParser(){
	m_fStr = L"";
	m_it = m_fStr.begin();
	error=MP_OK;
}

MFunction *MParser::ParseFunction(const wchar_t *fStr){
	return ParseFunction((std::wstring)fStr);
}

MFunction *MParser::ParseFunction(const std::wstring &fStr){
	MFunction *ret=NULL;
	m_fStr = fStr;
	transform(
	  m_fStr.begin(), m_fStr.end(),
	  m_fStr.begin(),
	  tolower);
	error=MP_OK;
	m_it = m_fStr.begin();
	if (!AnalizeParentesis())
	{
		return NULL;
	}
	m_it = m_fStr.begin();
	if (!AnalizeCharCoerency())
	{
		return NULL;
	}
	m_it = m_fStr.begin();
	if (!AnalizePlane(&ret))
	{
		return NULL;
	}
	return ret;
}

bool MParser::AnalizeParentesis(){
	if (m_fStr.length() == 0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	unsigned int  par=0;
	for (; m_it<m_fStr.end();m_it++){
		if ('('==*(m_it)) par++;
		if (')'==*(m_it)){
			if (par==0){
				error=MP_UNEXPECTED_CHAR;
				return false;
			}
			par--;
		}
	}
	if (par!=0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	return true;
}

bool MParser::AnalizePlane(MFunction **pt, wchar_t delimiter){
	Clean();
	if (m_fStr.end() == m_it){
		error=MP_UNEXPECTED_END;
		return false;
	}
	if (*m_it==')' || *m_it==',' || *m_it=='*' || *m_it=='/' || *m_it == '%' || *m_it=='^'){
		error=MP_UNEXPECTED_CHAR;
		return false;
	}
	FListElement *fpt;
	if (!CreateList(&fpt,delimiter)){
		return false;
	}
	if (!ConvertList(fpt)){
		while (fpt){
			FListElement *temp=fpt;
			fpt=fpt->next;
			free(temp);
		}
		return false;
	}
	(*pt)= fpt->func;
	free(fpt);
	return true;
}

unsigned int MParser::IsFunction(){
	unsigned int len = m_fStr.end() - m_it;
	if (len < 2) return 0; // remaining chars less then 2
	if (m_fStr.compare(m_it-m_fStr.begin(), 2, L"pi") == 0){
		if (len < 3) return 2;
		if (!iswalpha(*(m_it +3 ))) return 2;
		return 0;
	}
	if (m_fStr.end() - m_it < 3) return 0;
	if (m_fStr.compare(m_it-m_fStr.begin(), 3, L"ln(") == 0) return 3;

	if (len < 4) return 0;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"abs(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"log(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"sin(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"cos(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"tan(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"exp(") == 0) return 4;
	if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"pow(") == 0) return 4;

	if (len < 5) return 0;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"sqrt(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"sinh(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"cosh(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"tanh(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"asin(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"acos(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"atan(") == 0) return 5;
	if (m_fStr.compare(m_it-m_fStr.begin(), 5, L"sign(") == 0) return 5;

	if (len < 6) return 0;
	if (m_fStr.compare(m_it-m_fStr.begin(), 6, L"log10(") == 0) return 6;
	if (m_fStr.compare(m_it-m_fStr.begin(), 6, L"cotan(") == 0) return 6;

	if (len < 7) return 0;
	if (m_fStr.compare(m_it-m_fStr.begin(), 7, L"cotanh(") == 0) return 7;
	if (m_fStr.compare(m_it-m_fStr.begin(), 7, L"acotan(") == 0) return 7;
	return 0;
}

bool MParser::AnalizeFunction(MFunction **pt){
	Clean();
	if (m_fStr.end() - m_it == 0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	unsigned int len=IsFunction();
	if (len == 0){
		len = 1;
		while(m_it + len != m_fStr.end() && iswalpha(*(m_it+len))){
			len++;
			if (m_fStr.end() - m_it == len){
				break;
			}
		}
		(*pt)=new MFVar(std::wstring(m_it,m_it+len));
		m_it += len;
		Clean();
		return true;
	}else{
		if (m_fStr.compare(m_it-m_fStr.begin(), 2, L"pi") == 0){
			(*pt)=new MFConst(2*asin(1.0));
			m_it += 2;
			return true;
		}else{
			bool nelem=false;
			if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"log(") == 0) nelem=true;
			if (m_fStr.compare(m_it-m_fStr.begin(), 4, L"pow(") == 0) nelem=true;
			
			std::wstring str(m_it, m_it + len);

			MFunction *p1=NULL;
			MFunction *p2=NULL;

			if (nelem) {
				m_it += len;
				Clean();
				if (!AnalizePlane(&p1,',')) return false;
				m_it++;
				Clean();
				if (!AnalizePlane(&p2,')')){
					p1->Release();
					return false;
				}
				m_it++;
				Clean();
			}else{
				m_it += len;
				Clean();
				if (!AnalizePlane(&p1,')')) return false;
				m_it++;
				Clean();
			}

			if (str.compare(L"ln(") == 0){
				(*pt)=(MFunction*) new MFLn(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"abs(") == 0){
				(*pt)=(MFunction*) new  MFAbs(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"log(") == 0){
				(*pt)=(MFunction*) new  MFLog(p1,p2);
				if (p1) p1->Release();
				if (p2) p2->Release();
				return true;
			}else if (str.compare(L"sin(") == 0){
				(*pt)=(MFunction*) new  MFSin(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"cos(") == 0){
				(*pt)=(MFunction*) new  MFCos(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"tan(") == 0){
				(*pt)=(MFunction*) new  MFTan(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"exp(") == 0){
				(*pt)=(MFunction*) new  MFExp(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"pow(") == 0){
				(*pt)=(MFunction*) new  MFPow(p1,p2);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (str.compare(L"sqrt(") == 0){
				(*pt)=(MFunction*) new  MFSqrt(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (str.compare(L"cosh(") == 0){
				(*pt)=(MFunction*) new  MFCosh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (str.compare(L"sinh(") == 0){
				(*pt)=(MFunction*) new  MFSinh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (str.compare(L"tanh(") == 0){
				(*pt)=(MFunction*) new  MFTanh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (str.compare(L"asin(") == 0){
				(*pt)=(MFunction*) new  MFAsin(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"acos(") == 0){
				(*pt)=(MFunction*) new  MFAcos(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"atan(") == 0){
				(*pt)=(MFunction*) new  MFAtan(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"sign(") == 0){
				(*pt)=(MFunction*) new  MFSign(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"log10(") == 0){
				(*pt)=(MFunction*) new  MFLog10(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"cotan(") == 0){
				(*pt)=(MFunction*) new  MFCoTan(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"cotanh(") == 0){
				(*pt)=(MFunction*) new  MFCoTanh(p1);
				if (p1) p1->Release();
				return true;
			}else if (str.compare(L"acotan(") == 0){
				(*pt)=(MFunction*) new  MFAcotan(p1);
				if (p1) p1->Release();
				return true;
			}
			if (p1)	p1->Release();
			if (p2) p2->Release();
			error=MP_UNKNOWN_FUNCTION;
			return false;
		}
	}
}

bool MParser::AnalizeCharCoerency(){
	wchar_t mask[]=L" (),.+-*/^%abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int pos = wcsspn(m_fStr.c_str(),mask);
	if (pos==wcslen(m_fStr.c_str())) return true;
	m_it = m_fStr.begin() + pos;
	error=MP_UNEXPECTED_CHAR;
	return false;
}


bool MParser::CreateList(FListElement **pt, wchar_t delimiter){
	Clean();
	(*pt) = (FListElement*)malloc(sizeof(FListElement));
	if (m_it != m_fStr.end() && (*m_it == '-' || *m_it == '+')){
		(*pt)->op = *m_it;
		m_it++;
		if (m_fStr.end() - m_it == 0){
			error=MP_UNEXPECTED_END;
			return false;
		}
	}else (*pt)->op='+';
	FListElement *walker = (*pt);
	walker->func = NULL;
	walker->next = NULL;
	if (!ConvertElement(&(walker->func))) return false;
	Clean();
	if (m_it != m_fStr.end() && (*m_it == ')' || *m_it == ',')){
		if (*m_it == delimiter){
			return true;
		}else{
			error = MP_UNEXPECTED_CHAR;
			return false;
		}
	}
	while (m_it != m_fStr.end() && (*m_it == '+' || *m_it == '-' || *m_it == '*' || *m_it == '/' || *m_it == '%' || *m_it == '^')){
		walker->next = (FListElement*)malloc(sizeof(FListElement));
		walker = walker->next;
		walker->op = *m_it;
		walker->func = NULL;
		walker->next = NULL;
		m_it++;
		Clean();
		if (!ConvertElement(&(walker->func))) return false;
		Clean();
	}
	if (m_it != m_fStr.end() && (*m_it == ')' || *m_it == ',')){
		if (*m_it == delimiter){
			return true;
		}else{
			error = MP_UNEXPECTED_CHAR;
			return false;
		}
	}
	if (m_it == m_fStr.end()){
		return true;
	}
	error=MP_UNEXPECTED_CHAR;
	return false;
}

bool MParser::ConvertList(FListElement *pt){
	if (!pt){
		return false;
	}
	FListElement *tp = pt;
	while (tp->next){
		if(tp->next->op == '^'){
			FListElement *temp = tp->next;
			tp->next = tp->next->next;
			MFPow *ftemp = new MFPow();
			ftemp->SetBase(tp->func);
			ftemp->SetExponent(temp->func);
			tp->func = (MFunction*)ftemp;
			free(temp);
		}else{
			tp = tp->next;
		}
	}
	tp=pt;
	while (tp->next){
		if (tp->next->op == '*') {
			FListElement *temp = tp->next;
			tp->next = tp->next->next;
			MFMul *ftemp = new MFMul();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func = (MFunction*)ftemp;
			free(temp);
		}else if (tp->next->op == '%') {
				FListElement *temp = tp->next;
				tp->next = tp->next->next;
				MFPer *ftemp = new MFPer();
				ftemp->SetLhs(tp->func);
				ftemp->SetRhs(temp->func);
				tp->func = (MFunction*)ftemp;
				free(temp);
		}else if (tp->next->op=='/'){
			FListElement *temp = tp->next;
			tp->next = tp->next->next;
			MFDiv *ftemp = new MFDiv();
			ftemp->SetNum(tp->func);
			ftemp->SetDenum(temp->func);
			tp->func = (MFunction*)ftemp;
			free(temp);
		}else{
			tp = tp->next;
		}
	}
	tp=pt;
	if (tp->op == '-'){
		MFOpp *fn = new MFOpp();
		fn->SetFn(tp->func);
		tp->func = fn;
	}
	while (tp->next){
		if (tp->next->op == '+'){
			FListElement *temp = tp->next;
			tp->next = tp->next->next;
			MFAdd *ftemp = new MFAdd();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func = (MFunction*)ftemp;
			free(temp);
		}else if (tp->next->op == '-'){
			FListElement *temp = tp->next;
			tp->next = tp->next->next;
			MFSub *ftemp = new MFSub();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func = (MFunction*)ftemp;
			free(temp);
		}else{
			return false;
		}
	}
	return true;
}

bool MParser::ConvertElement(MFunction **pt){
	Clean();
	if (m_it == m_fStr.end()){
		error = MP_UNEXPECTED_END;
		return false;
	}
	if (*m_it == '+' || *m_it == '-' || *m_it == '/' || *m_it == '*' || *m_it == '%' || *m_it == '^' || *m_it == ')'){
		error = MP_UNEXPECTED_CHAR;
		return false;
	}
	if (iswdigit(*m_it)){
		double value;
		swscanf(std::wstring(m_it, m_fStr.end()).c_str(),L"%Lf",&value);
		while(m_it != m_fStr.end() && (iswdigit(*m_it) || *m_it=='.')){
			m_it++;
		}
		*pt = new MFConst(value);
		return true;
	}else{
		if (*m_it == '('){
			m_it++;
			if (m_it == m_fStr.end()){
				error=MP_UNEXPECTED_END;
				return false;
			}
			if (!AnalizePlane(pt,')')) return false;
			m_it++;
			return true;
		}
		if (AnalizeFunction(pt)) return true;
		return false;
	}
}

void MParser::Clean(){
	while (m_it != m_fStr.end() && *m_it == ' ')
	{
		m_it++;
	}
}
