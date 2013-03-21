#include "MParser.h"
#include <wctype.h>
#include <stdio.h>
#include <wchar.h>

using namespace mtk;

MParser::MParser(){
	m_pos=0;
	error=MP_OK;
}

MFunction *MParser::ParseFunction(const wchar_t*fStr){
	MFunction *ret=NULL;
	int len = wcslen(fStr);
	wchar_t *fStrLower = new wchar_t[len+1];
	for (int i=0; i<len;i++)
	{
		*(fStrLower+i) = towlower(*(fStr+i));
	}
	*(fStrLower+len)='\0';
	error=MP_OK;
	m_pos=0;
	if (!AnalizeParentesis(fStrLower))
	{
		delete[] fStrLower;
		return NULL;
	}
	m_pos=0;
	if (!AnalizeCharCoerency(fStrLower))
	{
		delete[] fStrLower;
		return NULL;
	}
	m_pos=0;
	if (!AnalizePlane(fStrLower,&ret))
	{
		delete[] fStrLower;
		return NULL;
	}
	m_pos=0;
	delete[] fStrLower;
	return ret;
}

bool MParser::AnalizeParentesis(const wchar_t *fStr){
	if (!fStr){
		if (fStr) error=MP_UNEXPECTED_END;
		return false;
	}
	unsigned int  par=0;
	for (m_pos=0; m_pos<wcslen(fStr);m_pos++){
		if ('('==*(fStr+m_pos)) par++;
		if (')'==*(fStr+m_pos)){
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

bool MParser::AnalizePlane(const wchar_t *fStr, MFunction **pt, wchar_t delimiter){
	if (wcslen((fStr+m_pos))==0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	if (*(fStr+m_pos)==')' || *(fStr+m_pos)==',' || *(fStr+m_pos)=='*' || *(fStr+m_pos)=='/' || *(fStr+m_pos)=='^'){
		error=MP_UNEXPECTED_CHAR;
		return false;
	}
	FListElement *fpt;
	if (!CreateList(fStr,&fpt,delimiter)){
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

unsigned int MParser::IsFunction(const wchar_t *fStr){
		if (wcslen(fStr)<2) return 0;
		if (wcsncmp(fStr,L"pi",2)==0){
			if (wcslen(fStr)<3) return 2;
			if (!iswalpha(*(fStr+2))) return 2;
			return 0;
		}
		if (wcslen(fStr)<3) return 0;
		if (wcsncmp(fStr,L"ln(",3)==0)return 3;
		if (wcslen(fStr)<4) return 0;
		if (wcsncmp(fStr,L"abs(",4)==0)return 4;
		if (wcsncmp(fStr,L"log(",4)==0)return 4;
		if (wcsncmp(fStr,L"sin(",4)==0)return 4;
		if (wcsncmp(fStr,L"cos(",4)==0)return 4;
		if (wcsncmp(fStr,L"tan(",4)==0)return 4;
		if (wcsncmp(fStr,L"exp(",4)==0)return 4;
		if (wcsncmp(fStr,L"pow(",4)==0)return 4;
		if (wcslen(fStr)<5) return 0;
		if (wcsncmp(fStr,L"sqrt(",5)==0)return 5;
		if (wcsncmp(fStr,L"sinh(",5)==0)return 5;
		if (wcsncmp(fStr,L"cosh(",5)==0)return 5;
		if (wcsncmp(fStr,L"tanh(",5)==0)return 5;
		if (wcsncmp(fStr,L"asin(",5)==0)return 5;
		if (wcsncmp(fStr,L"acos(",5)==0)return 5;
		if (wcsncmp(fStr,L"atan(",5)==0)return 5;
		if (wcsncmp(fStr,L"sign(",5)==0)return 5;
		if (wcslen(fStr)<6) return 0;
		if (wcsncmp(fStr,L"log10(",6)==0)return 6;
		if (wcsncmp(fStr,L"cotan(",6)==0)return 6;
		if (wcslen(fStr)<7) return 0;
		if (wcsncmp(fStr,L"cotanh(",7)==0)return 7;
		if (wcsncmp(fStr,L"acotan(",7)==0)return 7;
		return 0;
}

bool MParser::AnalizeFunction(const wchar_t *fStr, MFunction **pt){
	if (wcslen((fStr+m_pos))==0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	const wchar_t *temps=(fStr+m_pos);
	unsigned int  len=IsFunction(temps);
	if (len==0){
		len=1;
		while(iswalpha(*(fStr+m_pos+len))){
			len++;
			if (0==wcslen((fStr+m_pos+len))){
				break;
			}
		}
		(*pt)=new MFVar((fStr+m_pos),len);
		m_pos=m_pos+len;
		return true;
	}else{
		if (wcsncmp((fStr+m_pos),L"pi",2)==0){
			(*pt)=new MFConst(2*asin(1.0));
			m_pos+=2;
			return true;
		}else{
			bool nelem=false;
			if (wcsncmp((fStr+m_pos),L"log(",4)==0) nelem=true;
			if (wcsncmp((fStr+m_pos),L"pow(",4)==0) nelem=true;
			
			MFunction *p1=NULL;
			MFunction *p2=NULL;
			
			const wchar_t *str=(fStr+m_pos);

			if (nelem) {
				m_pos+=len;
				if (!AnalizePlane(fStr,&p1,',')) return false;
				m_pos++;
				if (!AnalizePlane(fStr,&p2,')')){
					p1->Release();
					return false;
				}
				m_pos++;
			}else{
				m_pos+=len;
				if (!AnalizePlane(fStr,&p1,')')) return false;
				m_pos++;
			}

			if (wcsncmp(str,L"ln(",3)==0){
				(*pt)=(MFunction*) new MFLn(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"abs(",4)==0){
				(*pt)=(MFunction*) new  MFAbs(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"log(",4)==0){
				(*pt)=(MFunction*) new  MFLog(p1,p2);
				if (p1) p1->Release();
				if (p2) p2->Release();
				return true;
			}else if (wcsncmp(str,L"sin(",4)==0){
				(*pt)=(MFunction*) new  MFSin(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"cos(",4)==0){
				(*pt)=(MFunction*) new  MFCos(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"tan(",4)==0){
				(*pt)=(MFunction*) new  MFTan(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"exp(",4)==0){
				(*pt)=(MFunction*) new  MFExp(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"pow(",4)==0){
				(*pt)=(MFunction*) new  MFPow(p1,p2);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (wcsncmp(str,L"sqrt(",4)==0){
				(*pt)=(MFunction*) new  MFSqrt(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (wcsncmp(str,L"cosh(",4)==0){
				(*pt)=(MFunction*) new  MFCosh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (wcsncmp(str,L"sinh(",4)==0){
				(*pt)=(MFunction*) new  MFSinh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (wcsncmp(str,L"tanh(",4)==0){
				(*pt)=(MFunction*) new  MFTanh(p1);
				if (p1) p1->Release();
				if (p2)	p2->Release();
				return true;
			}else if (wcsncmp(str,L"asin(",5)==0){
				(*pt)=(MFunction*) new  MFAsin(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"acos(",5)==0){
				(*pt)=(MFunction*) new  MFAcos(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"atan(",5)==0){
				(*pt)=(MFunction*) new  MFAtan(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"sign(",5)==0){
				(*pt)=(MFunction*) new  MFSign(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"log10(",6)==0){
				(*pt)=(MFunction*) new  MFLog10(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"cotan(",6)==0){
				(*pt)=(MFunction*) new  MFCoTan(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"cotanh(",6)==0){
				(*pt)=(MFunction*) new  MFCoTanh(p1);
				if (p1) p1->Release();
				return true;
			}else if (wcsncmp(str,L"acotan(",7)==0){
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

bool MParser::AnalizeCharCoerency(const wchar_t*fStr){
	wchar_t mask[]=L"(),.+-*/^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	m_pos=wcsspn(fStr,mask);
	if (m_pos==wcslen(fStr)) return true;
	error=MP_UNEXPECTED_CHAR;
	return false;
}


bool MParser::CreateList(const wchar_t *fStr, FListElement **pt, wchar_t delimiter){
	(*pt)=(FListElement*)malloc(sizeof(FListElement));
	if (*(fStr+m_pos)=='-' || *(fStr+m_pos)=='+'){
		(*pt)->op=*(fStr+m_pos);
		m_pos++;
		if (wcslen((fStr+m_pos))==0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	}else (*pt)->op='+';
	FListElement *walker=(*pt);
	walker->func=NULL;
	walker->next=NULL;
	if (!ConvertElement(fStr,&(walker->func))) return false;
	if (*(fStr+m_pos)==')' || *(fStr+m_pos)==','){
		if (*(fStr+m_pos)==delimiter){
			return true;
		}else{
			error=MP_UNEXPECTED_CHAR;
			return false;
		}
	}
	while (*(fStr+m_pos)=='+' || *(fStr+m_pos)=='-' || *(fStr+m_pos)=='*' || *(fStr+m_pos)=='/' || *(fStr+m_pos)=='^'){
		walker->next=(FListElement*)malloc(sizeof(FListElement));
		walker=walker->next;
		walker->op=*(fStr+m_pos);
		walker->func=NULL;
		walker->next=NULL;
		m_pos++;
		if (!ConvertElement(fStr,&(walker->func))) return false;
	}
	if (*(fStr+m_pos)==')' || *(fStr+m_pos)==','){
		if (*(fStr+m_pos)==delimiter){
			return true;
		}else{
			error=MP_UNEXPECTED_CHAR;
			return false;
		}
	}
	if (wcslen(fStr)==m_pos){
		return true;
	}
	error=MP_UNEXPECTED_CHAR;
	return false;
}

bool MParser::ConvertList(FListElement *pt){
	if (!pt){
		return false;
	}
	FListElement *tp=pt;
	while (tp->next){
		if(tp->next->op=='^'){
			FListElement *temp=tp->next;
			tp->next=tp->next->next;
			MFPow *ftemp= new MFPow();
			ftemp->SetBase(tp->func);
			ftemp->SetExponent(temp->func);
			tp->func=(MFunction*)ftemp;
			free(temp);
		}else{
			tp=tp->next;
		}
	}
	tp=pt;
	while (tp->next){
		if(tp->next->op=='*'){
			FListElement *temp=tp->next;
			tp->next=tp->next->next;
			MFMul *ftemp= new MFMul();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func=(MFunction*)ftemp;
			free(temp);
		}else if (tp->next->op=='/'){
			FListElement *temp=tp->next;
			tp->next=tp->next->next;
			MFDiv *ftemp= new MFDiv();
			ftemp->SetNum(tp->func);
			ftemp->SetDenum(temp->func);
			tp->func=(MFunction*)ftemp;
			free(temp);
		}else{
			tp=tp->next;
		}
	}
	tp=pt;
	if (tp->op=='-'){
		MFOpp *fn=new MFOpp();
		fn->SetFn(tp->func);
		tp->func= fn;
	}
	while (tp->next){
		if (tp->next->op=='+'){
			FListElement *temp=tp->next;
			tp->next=tp->next->next;
			MFAdd *ftemp= new MFAdd();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func=(MFunction*)ftemp;
			free(temp);
		}else if (tp->next->op=='-'){
			FListElement *temp=tp->next;
			tp->next=tp->next->next;
			MFSub *ftemp= new MFSub();
			ftemp->SetLhs(tp->func);
			ftemp->SetRhs(temp->func);
			tp->func=(MFunction*)ftemp;
			free(temp);
		}else{
			return false;
		}
	}
	return true;
}

bool MParser::ConvertElement(const wchar_t *fStr, MFunction **pt){
	if (wcslen((fStr+m_pos))==0){
		error=MP_UNEXPECTED_END;
		return false;
	}
	if (*(fStr+m_pos)=='+' || *(fStr+m_pos)=='-' || *(fStr+m_pos)=='/' || *(fStr+m_pos)=='*' || *(fStr+m_pos)=='^' || *(fStr+m_pos)==')'){
		error=MP_UNEXPECTED_CHAR;
		return false;
	}
	if (iswdigit(*(fStr+m_pos))){
		double value;
		swscanf((fStr+m_pos),L"%Lf",&value);
		while(iswdigit(*(fStr+m_pos))||*(fStr+m_pos)=='.'){
			m_pos++;
		}
		*pt = new MFConst(value);
		return true;
	}else{
		if (*(fStr+m_pos)=='('){
			m_pos++;
			if (wcslen((fStr+m_pos))==0){
				error=MP_UNEXPECTED_END;
				return false;
			}
			if (!AnalizePlane(fStr,pt,')')) return false;
			m_pos++;
			return true;
		}
		if (AnalizeFunction(fStr,pt)) return true;
		return false;
	}
}

wchar_t *MParser::Clean(wchar_t * str) const{
	const wchar_t *s=L" ";
	unsigned int pos=wcscspn(str,s);
	while(pos!=wcslen(str)){
		wcscpy((str+pos),(str+pos+1));
		pos=wcscspn(str,s);
	}
	return str;
}
