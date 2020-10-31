/**
 @file		FileUtility.cpp
 @brief		ファイルハンドルを伴わないファイルIOに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "FileUtility.h"

using namespace alt;

BOOL FileUtility::Delete(LPCTSTR name)
{
	return ::DeleteFile(name);
}

BOOL FileUtility::Copy(LPCTSTR source, LPCTSTR dest, BOOL bFailIfExists)
{
	return ::CopyFile(source, dest, bFailIfExists);
}

BOOL FileUtility::Move(LPCTSTR source, LPCTSTR dest)
{
	return ::MoveFile(source, dest);
}

BOOL FileUtility::MakeDir(LPCTSTR name)
{
	return ::CreateDirectory(name, nullptr);
}

BOOL FileUtility::RemoveDir(LPCTSTR name)
{
	return ::RemoveDirectory(name);
}

BOOL FileUtility::IsExist(LPCTSTR name)
{
	WIN32_FIND_DATA myFindData;
	HANDLE hFind;
	BOOL ret;

	hFind = ::FindFirstFile(name, &myFindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}
	else
	{
		::FindClose(hFind);
		ret = TRUE;
	}

	return ret;
}

skeleton::Array<TString> FileUtility::Find(LPCTSTR name)
{
	WIN32_FIND_DATA myFindData;
	HANDLE hFind;
	skeleton::Array<TString> ret;

	hFind = ::FindFirstFile(name, &myFindData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (myFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// skip
			}
			else
			{
				ret.Add(new TString(myFindData.cFileName));
			}
		} while (::FindNextFile(hFind, &myFindData));
	}

	return ret;
}

BOOL FileUtility::DirectoryWatch(LPCTSTR watchDirectory)
{
	HANDLE hDirectory =
		::CreateFile(
			watchDirectory,
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			nullptr,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			nullptr);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwNotifyFilter;
	dwNotifyFilter =
		FILE_NOTIFY_CHANGE_FILE_NAME |
		FILE_NOTIFY_CHANGE_DIR_NAME |
		FILE_NOTIFY_CHANGE_ATTRIBUTES |
		FILE_NOTIFY_CHANGE_LAST_WRITE |
		FILE_NOTIFY_CHANGE_LAST_ACCESS |
		FILE_NOTIFY_CHANGE_CREATION;

	BOOL ret;
	DWORD dwResponse;

	while (1) // TODO:ループから抜ける方法がない。…FileUtilityでは収まらないようだ。
	{
		WCHAR* buffer = new WCHAR[1024];
		ZeroMemory(buffer, sizeof(WCHAR) * 1024);

		ret = ::ReadDirectoryChangesW(
			hDirectory,
			buffer,
			sizeof(WCHAR) * 1024,
			TRUE,
			dwNotifyFilter,
			&dwResponse,
			nullptr,
			nullptr
		);

		if (ret == FALSE)
		{
			return ret;
		}

		PFILE_NOTIFY_INFORMATION currentPFNI = (PFILE_NOTIFY_INFORMATION)buffer;
		for (int i = 0; ;)
		{
			switch (currentPFNI->Action)
			{
				case FILE_ACTION_ADDED:
					_tprintf(TEXT("FILE_ACTION_ADDED FileName=%s\n"), currentPFNI->FileName);
					break;

				case FILE_ACTION_MODIFIED:
					_tprintf(TEXT("FILE_ACTION_MODIFIED FileName=%s\n"), currentPFNI->FileName);
					break;

				case FILE_ACTION_REMOVED:
					_tprintf(TEXT("FILE_ACTION_REMOVED FileName=%s\n"), currentPFNI->FileName);
					break;

				case FILE_ACTION_RENAMED_NEW_NAME:
					_tprintf(TEXT("FILE_ACTION_RENAMED_NEW_NAME FileName=%s\n"), currentPFNI->FileName);
					break;

				case FILE_ACTION_RENAMED_OLD_NAME:
					_tprintf(TEXT("FILE_ACTION_RENAMED_OLD_NAME FileName=%s\n"), currentPFNI->FileName);
					break;

				default:
					break;
			}

			currentPFNI += currentPFNI->NextEntryOffset;
			if (currentPFNI->NextEntryOffset == 0) break;
			i += currentPFNI->NextEntryOffset;
		}

		delete[] buffer;
	}

	CloseHandle(hDirectory);
}

BOOL FileUtility::MakeSymbolicLink(LPCTSTR source, LPCTSTR link, BOOL isFile)
{
	DWORD dwFlags = isFile == TRUE ? 0 : SYMBOLIC_LINK_FLAG_DIRECTORY;
	dwFlags |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;

	return ::CreateSymbolicLink(link, source, dwFlags);
}

BOOL FileUtility::MakeHardLink(LPCTSTR source, LPCTSTR link)
{
	return ::CreateHardLink(link, source, nullptr);
}
