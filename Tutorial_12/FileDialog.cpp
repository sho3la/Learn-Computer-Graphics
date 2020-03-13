#include "FileDialog.h"
#include <Windows.h>

char * FileDialog::Open()
{
	char* filter = "All Files (*.*)\0*.*\0";
	OPENFILENAME ofn;

	char filename[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;

	if(GetOpenFileName(&ofn))
	{
		char* res = new char[MAX_PATH];
		memcpy(res, filename,MAX_PATH);
		return res;
	}

	return nullptr;
}
