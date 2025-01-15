#include "PatternUtil.h"
#include <stdexcept>
#include <optional>
#include <vector>

namespace WPSHashPatch {
    std::vector<const uint8_t*> PatternUtil::FindPattern(std::span<const uint8_t> data,
                                                         std::span<const uint16_t> pattern,
                                                         size_t index,
                                                         bool reverse,
                                                         size_t maxMatches) {
        if (data.empty())
            throw std::invalid_argument("Data cannot be empty");
        if (pattern.empty())
            throw std::invalid_argument("Pattern cannot be empty");
        if (index > data.size())
            throw std::invalid_argument("Index out of range");
        if (maxMatches == 0)
            throw std::invalid_argument("Max matches cannot be zero");

        std::vector<const uint8_t*> matches;
        for (size_t i = reverse ? std::min(data.size() - pattern.size(), index) : std::max(static_cast<size_t>(0), index);
             reverse ? i >= 0 : i <= data.size() - pattern.size();
             reverse ? --i : ++i) {
            bool match = true;
            for (size_t j = 0; j < pattern.size(); ++j) {
                if (pattern[j] <= 0xFF && pattern[j] != data[i + j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(data.data() + i);
                if (matches.size() >= maxMatches)
                    break;
            }
        }
        return matches;
    }
}
