#include "Version.h"
#include <stdexcept>
#include <string>

namespace WPSHashPatch {
    HMODULE Version::handle = nullptr;

    BOOL(WINAPI* Version::getFileVersionInfoA)
    (LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) = nullptr;
    BOOL(WINAPI* Version::getFileVersionInfoByHandle)
    (DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen) = nullptr;
    BOOL(WINAPI* Version::getFileVersionInfoExA)
    (DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) = nullptr;
    BOOL(WINAPI* Version::getFileVersionInfoExW)
    (DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) = nullptr;
    DWORD(WINAPI* Version::getFileVersionInfoSizeA)
    (LPCSTR lptstrFilename, LPDWORD lpdwHandle) = nullptr;
    DWORD(WINAPI* Version::getFileVersionInfoSizeExA)
    (DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle) = nullptr;
    DWORD(WINAPI* Version::getFileVersionInfoSizeExW)
    (DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle) = nullptr;
    DWORD(WINAPI* Version::getFileVersionInfoSizeW)
    (LPCWSTR lptstrFilename, LPDWORD lpdwHandle) = nullptr;
    BOOL(WINAPI* Version::getFileVersionInfoW)
    (LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) = nullptr;
    DWORD(WINAPI* Version::verFindFileA)
    (DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen) = nullptr;
    DWORD(WINAPI* Version::verFindFileW)
    (DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir, PUINT lpuDestDirLen) = nullptr;
    DWORD(WINAPI* Version::verInstallFileA)
    (DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen) = nullptr;
    DWORD(WINAPI* Version::verInstallFileW)
    (DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen) = nullptr;
    DWORD(WINAPI* Version::verLanguageNameA)
    (DWORD wLang, LPSTR szLang, DWORD cchLang) = nullptr;
    DWORD(WINAPI* Version::verLanguageNameW)
    (DWORD wLang, LPWSTR szLang, DWORD cchLang) = nullptr;
    BOOL(WINAPI* Version::verQueryValueA)
    (LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) = nullptr;
    BOOL(WINAPI* Version::verQueryValueW)
    (LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) = nullptr;

    void Version::LoadProcAddress(FARPROC* proc, LPCSTR name) {
        FARPROC address = GetProcAddress(handle, name);
        if (address == NULL) {
            std::string error = "Unable to find proc ";
            if (HIWORD(name) == 0) {
                throw std::runtime_error(error + std::to_string(reinterpret_cast<ULONG_PTR>(name)));
            } else {
                throw std::runtime_error(error + name);
            }
        }
        *proc = address;
    }

    void Version::Load() {
        if (handle) {
            return;
        }
        CHAR path[MAX_PATH];
        UINT size = GetSystemDirectoryA(path, MAX_PATH);
        std::memcpy(path + size, "\\version.dll", 13);
        handle = LoadLibraryA(path);
        if (handle == NULL) {
            throw std::runtime_error(std::string("Failed to load ") + path);
        }
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoByHandle), "GetFileVersionInfoByHandle");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoExA), "GetFileVersionInfoExA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoExW), "GetFileVersionInfoExW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoSizeA), "GetFileVersionInfoSizeA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoSizeExA), "GetFileVersionInfoSizeExA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoSizeExW), "GetFileVersionInfoSizeExW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoSizeW), "GetFileVersionInfoSizeW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&getFileVersionInfoW), "GetFileVersionInfoW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verFindFileA), "VerFindFileA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verFindFileW), "VerFindFileW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verInstallFileA), "VerInstallFileA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verInstallFileW), "VerInstallFileW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verLanguageNameA), "VerLanguageNameA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verLanguageNameW), "VerLanguageNameW");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verQueryValueA), "VerQueryValueA");
        LoadProcAddress(reinterpret_cast<FARPROC*>(&verQueryValueW), "VerQueryValueW");
    }

    void Version::Unload() {
        if (handle) {
            FreeLibrary(handle);
            handle = nullptr;
        }
    }
}
