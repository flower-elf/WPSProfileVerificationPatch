#pragma once
#include <optional>
#include <cstdint>
#include <string>

namespace WPSProfileVerificationPatch {
    class ModuleUtil {
    private:
        ModuleUtil() = delete;

    public:
        static HMODULE GetHandle(const std::optional<const std::string>& moduleName = std::nullopt);
        static HMODULE GetSelfHandle();
        static uint32_t GetSizeOfMemory(HMODULE module = nullptr);
        static std::string GetFileName(HMODULE module = nullptr);
        static std::string GetBasePath(HMODULE module = nullptr);
    };
}
