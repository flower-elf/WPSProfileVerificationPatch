#pragma once
#include <cstdint>
#include <string>
#include <span>

namespace WPSHashPatch {
    class ProcessUtil {
    private:
        ProcessUtil() = delete;

    public:
        static uint32_t GetModuleSize(HMODULE module);
        // static std::span<const uint8_t> GetModuleBaseData(uint32_t pid, const wchar_t* moduleName);
    };
}
