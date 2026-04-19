/*
* WinAPI声明
*
* Author: Maple
* date: 2021-7-13 Create
* Copyright winmoes.com
*/

#include "framework.h"
#include "WinAPI.h"
#include <io.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

void Log(std::wstring log)
{
	OutputDebugStringW((L"\n[Debug]: " + log).c_str());
}

void Log(int log)
{
	Log(std::to_wstring(log));
}

std::wstring GetCurDllDir()
{
	wchar_t sPath[MAX_PATH];
	GetModuleFileNameW(g_hModule, sPath, MAX_PATH);
	std::wstring path = sPath;
	path = path.substr(0, path.rfind(L"\\"));

	return path;
}

bool FileIsExist(std::wstring FilePath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFileW(FilePath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return true;
	}
	return false;
}

std::wstring GetWindowTitle(HWND hWnd)
{
	const int size = GetWindowTextLengthW(hWnd);
	if (size <= 0)
		return std::wstring();

	std::wstring text(static_cast<size_t>(size) + 1, L'\0');
	GetWindowTextW(hWnd, &text[0], size + 1);
	text.resize(static_cast<size_t>(size));
	return text;
}

std::wstring GetWindowClassName(HWND hWnd)
{
	wchar_t pText[MAX_PATH]{};
	GetClassNameW(hWnd, pText, MAX_PATH);
	return std::wstring(pText);
}

std::wstring GetIniString(std::wstring FilePath, std::wstring AppName, std::wstring KeyName)
{
	if (FileIsExist(FilePath)) {
		HANDLE pFile = CreateFileW(FilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (pFile == INVALID_HANDLE_VALUE)
			return std::wstring();

		LARGE_INTEGER fileSize;
		if (!GetFileSizeEx(pFile, &fileSize))
		{
			CloseHandle(pFile);
			return std::wstring();
		}

		DWORD bufferChars = static_cast<DWORD>(fileSize.QuadPart + 2);
		if (bufferChars < 256)
			bufferChars = 256;

		std::wstring data(static_cast<size_t>(bufferChars), L'\0');
		GetPrivateProfileStringW(AppName.c_str(), KeyName.c_str(), NULL, &data[0], bufferChars, FilePath.c_str());

		std::wstring ret = data.c_str();

		CloseHandle(pFile);
		return ret;
	}
	return std::wstring();
}

void EnumFiles(std::wstring path, std::wstring append, std::vector<std::wstring>& fileList)
{
	//文件句柄 
	intptr_t  hFile = 0;
	//文件信息 
	struct _wfinddata_t fileinfo;
	std::wstring p;
	if ((hFile = _wfindfirst(p.assign(path).append(L"\\" + append).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				std::wstring path_ = path + L"\\";
				path_ += fileinfo.name;
				fileList.push_back(path_);
			}
		} while (_wfindnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

std::wstring GetFileName(std::wstring path)
{
	std::wstring::size_type iPos = path.find_last_of('\\') + 1;

	return path.substr(iPos, path.length() - iPos).c_str();
}

size_t GetFileSize(std::wstring path)
{
	WIN32_FILE_ATTRIBUTE_DATA fileInfo;

	// 获取文件信息
	if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &fileInfo))
	{
		return -1; // 获取文件信息失败
	}

	// 计算文件大小
	ULARGE_INTEGER fileSize;
	fileSize.HighPart = fileInfo.nFileSizeHigh;
	fileSize.LowPart = fileInfo.nFileSizeLow;

	return fileSize.QuadPart;
}

BitmapGDI::BitmapGDI(std::wstring path)
{
	//这样加载是为了防止文件被占用
	FILE* file = nullptr;
	_wfopen_s(&file, path.c_str(), L"rb");
	if (file) {
		fseek(file, 0L, SEEK_END);
		long len = ftell(file);
		rewind(file);
		BYTE* pdata = new BYTE[len];
		fread(pdata, 1, len, file);
		fclose(file);

		IStream* stream = SHCreateMemStream(pdata, len);
		delete[] pdata;

		src = Gdiplus::Bitmap::FromStream(stream);
		if (src) {
			pMem = CreateCompatibleDC(0);
			Size = { (LONG)src->GetWidth(), (LONG)src->GetHeight() };
			src->GetHBITMAP(0, &pBmp);
			SelectObject(pMem, pBmp);

			stream->Release();
		}
		else if (stream)
			stream->Release();
	}
}

BitmapGDI::~BitmapGDI()
{
delete src;
	if (pMem)
		DeleteDC(pMem);
	if (pBmp)
		DeleteObject(pBmp);
}
