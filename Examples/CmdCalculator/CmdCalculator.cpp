#include <iostream>
#include <MParser.h>

using namespace mpk;

int wmain(int argc, wchar_t* argv[])
{
	//Check if parameter is present
	if (argc < 2) return 0;

	//Initialize praser
	MParser parser;
	//Parse Parameter
	MFunction *f = parser.ParseFunction(argv[1]);
	if (f == NULL)
	{
		std::wcout << "Error " << parser.GetLastError() << " at Position " << parser.GetErrorPosition();
		return 0;
	}

	//Get Variables inside the function
	MVariablesList list;
	f->GetVariablesList(&list);

	//Ask for Variables values
	for (int i = 0; i<list.Count(); i++)
	{
		std::wcout << L"Variable " << list.GetItem(i)->GetName() << " = ";
		double value;
		std::wcin >> value;
		list.GetItem(i)->SetValue(value);
	}

	//Solve
	MFunction *ret = f->Solve(&list);

	//Check solution type
	if (ret->GetType() == MF_CONST)
	{
		std::cout << "Result = " << ((MFConst*)ret)->GetValue();
	}

	//Release objects
	f->Release();
	ret->Release();

	return 0;
}