#include "Framework.h"
#include "Version.h"
#include "KRSAVerifyFileHook.h"
using namespace WPSHashPatch;

BOOL APIENTRY DllMain(HMODULE module, DWORD reasonForCall, LPVOID reserved) {
    switch (reasonForCall) {
        case DLL_PROCESS_ATTACH:
            Version::Load();
            KRSAVerifyFileHook::Install(module);
            break;
        case DLL_PROCESS_DETACH:
            Version::Unload();
            KRSAVerifyFileHook::Uninstall();
            break;
    }
    return TRUE;
}
