#pragma once
#include "Framework.h"

namespace WPSHashPatch {
    class Version {
    private:
        Version() = delete;

    public:
        static HMODULE handle;

    public:
        static BOOL(WINAPI* getFileVersionInfoA)(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
        static BOOL(WINAPI* getFileVersionInfoByHandle)(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen);
        static BOOL(WINAPI* getFileVersionInfoExA)(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
        static BOOL(WINAPI* getFileVersionInfoExW)(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
        static DWORD(WINAPI* getFileVersionInfoSizeA)(LPCSTR lptstrFilename, LPDWORD lpdwHandle);
        static DWORD(WINAPI* getFileVersionInfoSizeExA)(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle);
        static DWORD(WINAPI* getFileVersionInfoSizeExW)(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle);
        static DWORD(WINAPI* getFileVersionInfoSizeW)(LPCWSTR lptstrFilename, LPDWORD lpdwHandle);
        static BOOL(WINAPI* getFileVersionInfoW)(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
        static DWORD(WINAPI* verFindFileA)(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen);
        static DWORD(WINAPI* verFindFileW)(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir, PUINT lpuDestDirLen);
        static DWORD(WINAPI* verInstallFileA)(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen);
        static DWORD(WINAPI* verInstallFileW)(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen);
        static DWORD(WINAPI* verLanguageNameA)(DWORD wLang, LPSTR szLang, DWORD cchLang);
        static DWORD(WINAPI* verLanguageNameW)(DWORD wLang, LPWSTR szLang, DWORD cchLang);
        static BOOL(WINAPI* verQueryValueA)(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen);
        static BOOL(WINAPI* verQueryValueW)(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen);

    private:
        static void LoadProcAddress(FARPROC* proc, LPCSTR name);

    public:
        static void Load();
        static void Unload();
    };
}
