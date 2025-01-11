#include "Framework.h"
#include "Version.h"
using namespace WPSHashPatch;

EXTERN_C BOOL WINAPI MGetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    return Version::getFileVersionInfoA(lptstrFilename, dwHandle, dwLen, lpData);
}

EXTERN_C BOOL WINAPI MGetFileVersionInfoByHandle(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen) {
    return Version::getFileVersionInfoByHandle(dwFlags, hFile, lplpData, pdwLen);
}

EXTERN_C BOOL WINAPI MGetFileVersionInfoExA(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    return Version::getFileVersionInfoExA(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

EXTERN_C BOOL WINAPI MGetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    return Version::getFileVersionInfoExW(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

EXTERN_C DWORD WINAPI MGetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle) {
    return Version::getFileVersionInfoSizeA(lptstrFilename, lpdwHandle);
}

EXTERN_C DWORD WINAPI MGetFileVersionInfoSizeExA(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle) {
    return Version::getFileVersionInfoSizeExA(dwFlags, lpwstrFilename, lpdwHandle);
}

EXTERN_C DWORD WINAPI MGetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle) {
    return Version::getFileVersionInfoSizeExW(dwFlags, lpwstrFilename, lpdwHandle);
}

EXTERN_C DWORD WINAPI MGetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle) {
    return Version::getFileVersionInfoSizeW(lptstrFilename, lpdwHandle);
}

EXTERN_C EXTERN_C BOOL WINAPI MGetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    return Version::getFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData);
}

EXTERN_C DWORD WINAPI MVerFindFileA(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen) {
    return Version::verFindFileA(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen, szDestDir, lpuDestDirLen);
}

EXTERN_C DWORD WINAPI MVerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir, PUINT lpuDestDirLen) {
    return Version::verFindFileW(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen, szDestDir, lpuDestDirLen);
}

EXTERN_C DWORD WINAPI MVerInstallFileA(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen) {
    return Version::verInstallFileA(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, lpuTmpFileLen);
}

EXTERN_C DWORD WINAPI MVerInstallFileW(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen) {
    return Version::verInstallFileW(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, lpuTmpFileLen);
}

EXTERN_C DWORD WINAPI MVerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD cchLang) {
    return Version::verLanguageNameA(wLang, szLang, cchLang);
}

EXTERN_C DWORD WINAPI MVerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD cchLang) {
    return Version::verLanguageNameW(wLang, szLang, cchLang);
}

EXTERN_C BOOL WINAPI MVerQueryValueA(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
    return Version::verQueryValueA(pBlock, lpSubBlock, lplpBuffer, puLen);
}

EXTERN_C BOOL WINAPI MVerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
    return Version::verQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen);
}
