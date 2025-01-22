#include <Windows.h>
#include <stdexcept>
#include "VersionUtil.h"

namespace WPSProfileVerificationPatch {
    std::unique_ptr<const uint8_t[]> VersionUtil::GetVersionInfoData(const std::string& filePath) {
        DWORD handle = 0;
        DWORD size = GetFileVersionInfoSizeA(filePath.data(), &handle);
        if (size != 0) {
            std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(size);
            if (GetFileVersionInfoA(filePath.data(), 0, size, data.get())) {
                return data;
            }
        }
        throw std::runtime_error("Failed to get version info data");
    }

    std::optional<std::span<const uint8_t>> VersionUtil::QueryVersionInfoValue(const std::unique_ptr<const uint8_t[]>& versionInfoData, const std::string& subBlock) {
        UINT dataSize = 0;
        uint8_t* data = nullptr;
        if (VerQueryValueA(versionInfoData.get(), subBlock.data(), reinterpret_cast<LPVOID*>(&data), &dataSize)) {
            return std::span<const uint8_t>(data, dataSize);
        }
        return std::nullopt;
    }
}
