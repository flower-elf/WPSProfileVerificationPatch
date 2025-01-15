#include "Framework.h"
#include "ProcessUtil.h"
#include <TlHelp32.h>
#include <stdexcept>

namespace WPSHashPatch {
    uint32_t ProcessUtil::GetModuleSize(HMODULE module) {
        PIMAGE_DOS_HEADER imageDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        if (imageDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
            throw std::runtime_error("Invalid DOS header");
        }
        PIMAGE_NT_HEADERS imageNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(&reinterpret_cast<PBYTE>(module)[imageDosHeader->e_lfanew]);
        if (imageNtHeader->Signature != IMAGE_NT_SIGNATURE) {
            throw std::runtime_error("Invalid NT header");
        }
        return imageNtHeader->OptionalHeader.SizeOfImage;
    }

    //std::span<const uint8_t> ProcessUtil::GetModuleBaseData(uint32_t pid, const wchar_t* moduleName) {
    //    std::span<const uint8_t> moduleBaseData;
    //    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    //    while (snapshot == INVALID_HANDLE_VALUE || snapshot == NULL) {
    //        DWORD errorCode = GetLastError();
    //        if (errorCode == ERROR_BAD_LENGTH) {
    //            snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    //            continue;
    //        } else {
    //            if (errorCode == ERROR_PARTIAL_COPY) {
    //                return moduleBaseData;
    //            } else {
    //                throw std::runtime_error("CreateToolhelp32Snapshot failed, error code: " + std::to_string(errorCode));
    //            }
    //        }
    //    }
    //    MODULEENTRY32W moduleEntry = {
    //        .dwSize = sizeof(moduleEntry)
    //    };
    //    BOOL ret = Module32FirstW(snapshot, &moduleEntry);
    //    while (ret) {
    //        if (moduleName == NULL || std::wcsstr(moduleName, moduleEntry.szModule) || std::wcsstr(moduleEntry.szModule, moduleName)) {
    //            moduleBaseData = std::span<const uint8_t>(moduleEntry.modBaseAddr, moduleEntry.modBaseSize);
    //            break;
    //        }
    //        ret = Module32NextW(snapshot, &moduleEntry);
    //    }
    //    CloseHandle(snapshot);
    //    return moduleBaseData;
    //}
}
