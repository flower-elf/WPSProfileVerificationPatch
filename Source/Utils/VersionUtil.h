#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <memory>
#include <span>

namespace WPSProfileVerificationPatch {
    class VersionUtil {
    private:
        VersionUtil() = delete;

    public:
        static std::unique_ptr<const uint8_t[]> GetVersionInfoData(const std::string& filePath);
        static std::optional<std::span<const uint8_t>> QueryVersionInfoValue(const std::unique_ptr<const uint8_t[]>& versionInfoData, const std::string& subBlock);
    };
}
