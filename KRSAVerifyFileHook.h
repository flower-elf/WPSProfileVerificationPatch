#pragma once
#include <string>

namespace WPSHashPatch {
    class KRSAVerifyFileHook {
    private:
        KRSAVerifyFileHook() = delete;

    private:
        static bool (*kRSAVerifyFile)(const std::string& publicKey, const std::string& fileHash, const std::string& fileSignature);
        static bool KRSAVerifyFile(const std::string& publicKey, const std::string& fileHash, const std::string& fileSignature);
        static void UpdateKRSAVerifyFileAddress();

    public:
        static void Install();
        static void Uninstall();
    };
}
