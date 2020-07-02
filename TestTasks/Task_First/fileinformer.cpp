#include "fileinformer.h"

FileInformer::FileInformer(const uint64_t RAM_limits, const uint64_t precision)
    : precision_(precision)
{
    RAM_limits_ = RAM_limits * 1024 * 1024;
}

void FileInformer::SetNumberFiles(uint32_t count_files)
{
    number_files_ = count_files;
}

uint64_t FileInformer::GetRAMLimits() const
{
    return RAM_limits_;
}

uint64_t FileInformer::GetPrecision() const
{
    return precision_;
}

uint64_t FileInformer::GetNumberFiles() const
{
    return number_files_;
}
