#pragma once

#include <cstdint>
#include <filesystem>

class FileInformer
{
public:
    explicit FileInformer(const uint64_t RAM_limits, const uint64_t precision);

    void SetNumberFiles(uint32_t count_files);

    uint64_t GetRAMLimits()   const;
    uint64_t GetPrecision()   const;
    uint64_t GetNumberFiles() const;

private:
    uint64_t RAM_limits_{ 0 },
        precision_{ 0 },
        number_files_{ 0 };
};
