#include <Windows.h>
#include "ProxyLibrary.h"
#include "KRSAVerifyFileHook.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reasonForCall, LPVOID reserved) {
    switch (reasonForCall) {
        case DLL_PROCESS_ATTACH:
            ProxyLibrary_Load();
            WPSProfileVerificationPatch::KRSAVerifyFileHook::Install();
            break;
        case DLL_PROCESS_DETACH:
            WPSProfileVerificationPatch::KRSAVerifyFileHook::Uninstall();
            ProxyLibrary_Unload();
            break;
    }
    return TRUE;
}
