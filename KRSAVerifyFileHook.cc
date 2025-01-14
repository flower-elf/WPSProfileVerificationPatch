#include "Framework.h"
#include "Detours/Detours.h"
#include "KRSAVerifyFileHook.h"
#include "ProcessUtil.h"
#include "PatternUtil.h"
#include <stdexcept>
#include <array>

namespace WPSHashPatch {
    bool (*KRSAVerifyFileHook::kRSAVerifyFile)(const std::string& publicKey, const std::string& fileHash, const std::string& fileSignature) = nullptr;

    bool KRSAVerifyFileHook::KRSAVerifyFile(const std::string& publicKey, const std::string& fileHash, const std::string& fileSignature) {
        for (std::string::size_type i = 0; i < fileSignature.size(); i++) {
            if (fileSignature[i] != '0') {
                return kRSAVerifyFile(publicKey, fileHash, fileSignature);
            }
        }
        return true;
    }

    void KRSAVerifyFileHook::UpdateKRSAVerifyFileAddress(HMODULE module) {
#if defined DETOURS_X64
        const std::array<uint16_t, 19> pattern = { 0x40, 0x53, 0x56, 0x57, 0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 0x48, 0x81, 0xEC, 0xD0, 0x02, 0x00, 0x00 };
#elif defined DETOURS_X86
        const std::array<uint16_t, 33> pattern = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x100, 0x100, 0x100, 0x100, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x81, 0xEC, 0x1C, 0x01, 0x00, 0x00, 0xA1, 0x100, 0x100, 0x100, 0x100, 0x33, 0xC5, 0x89, 0x45, 0xEC };
#else
#error "Unsupported architecture"
#endif
        CHAR path[MAX_PATH];
        UINT size = GetModuleFileNameA(module, path, MAX_PATH);
        if (size == 0 || size >= MAX_PATH) {
            throw std::runtime_error("Failed to get module file name");
        }
        LPSTR fileName = PathFindFileNameA(path);
        std::memcpy(fileName, "krt.dll", 8);
        HMODULE krt = LoadLibraryA(path); // load krt.dll of the same directory
        if (!krt) {
            return; // krt.dll not found, not hooking KRSAVerifyFile
        }
        std::span<const uint8_t> krtData(reinterpret_cast<const uint8_t*>(krt), ProcessUtil::GetModuleSize(krt));
        const std::vector<const uint8_t*> matches = PatternUtil::FindPattern(krtData, pattern, 0, false, 1);
        if (matches.size() > 0) {
            kRSAVerifyFile = reinterpret_cast<decltype(kRSAVerifyFile)>(matches[0]);
        }
    }

    void KRSAVerifyFileHook::Install(HMODULE module) {
        if (kRSAVerifyFile != nullptr) {
            return;
        }
        UpdateKRSAVerifyFileAddress(module);
        if (kRSAVerifyFile == nullptr) {
            return;
        }
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&reinterpret_cast<PVOID&>(kRSAVerifyFile), KRSAVerifyFileHook::KRSAVerifyFile);
        LONG code = DetourTransactionCommit();
        if (code != NO_ERROR) {
            throw std::runtime_error("Failed to hook KRSAVerifyFile, error code: " + std::to_string(code));
        }
    }

    void KRSAVerifyFileHook::Uninstall() {
        if (kRSAVerifyFile == nullptr) {
            return;
        }
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(reinterpret_cast<PVOID*>(kRSAVerifyFile), KRSAVerifyFileHook::KRSAVerifyFile);
        DetourTransactionCommit();
    }
}
