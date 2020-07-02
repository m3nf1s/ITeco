#include "profiler.h"
#include "fileinformer.h"

#include <fstream>
#include <random>
#include <iomanip>
#include <filesystem>
#include <algorithm>

template<typename T>
void CreateFile(FileInformer& file_informer)
{
    std::default_random_engine engine;
    const std::uniform_real_distribution<T> distributor(0.0, 1.0);

    const std::string filename = "output.txt";
    std::ofstream ofs(filename);

    for (uint64_t i = 0; i < std::numeric_limits<uint32_t>::max() / 75u; ++i)
    {
        ofs << std::setprecision(file_informer.GetPrecision()) << distributor(engine) << '\n';
    }
}

template<typename T>
void SplitFile(FileInformer& file_informer)
{
    std::ifstream ifs("output.txt");
    std::ofstream ofs;

    uint32_t counter = 0;

    const uint64_t limits = file_informer.GetRAMLimits() / sizeof(T);
    uint64_t index = 0;

    while (ifs)
    {
        ofs.open("temp" + std::to_string(counter) + ".txt");

        while (ifs && index <= limits)
        {
            T value;
            if (ifs >> value)
            {
                ofs << std::setprecision(file_informer.GetPrecision()) << value << '\n';
            }
            ++index;
        }

        index = 0;
        ++counter;
        ofs.close();
    }

    file_informer.SetNumberFiles(counter);
}

template<typename T>
void SortTempFiles(const FileInformer& file_informer)
{
    uint64_t counter = 0;

    std::ifstream  ifs;
    std::ofstream  ofs;
    std::vector<T> array;

    while (counter < file_informer.GetNumberFiles())
    {
        ifs.open("temp" + std::to_string(counter) + ".txt");
        T value;

        size_t size = 0;

        while (ifs >> value)
        {
            ++size;
        }

        ifs.close();
        ifs.open("temp" + std::to_string(counter) + ".txt");

        array.reserve(size);

        while (ifs >> value)
        {
            array.push_back(value);
        }

        std::sort(array.begin(), array.end());

        ofs.open("temp" + std::to_string(counter) + ".txt");
        for (const double& number : array)
        {
            ofs << std::setprecision(file_informer.GetPrecision()) << number << '\n';
        }

        array.clear();
        ++counter;
        ifs.close();
        ofs.close();
    }
}

template<typename T>
void MergeFiles(const FileInformer& file_informer)
{
    std::vector<std::ifstream> array(file_informer.GetNumberFiles());
    std::vector<T> values(file_informer.GetNumberFiles());

    for (size_t i = 0; i < array.size(); ++i)
    {
        array[i].open("temp" + std::to_string(i) + ".txt");
        array[i] >> values[i];
    }

    std::ofstream ofs("out.txt");

    while (!array.empty())
    {
        T min = values[0];
        size_t index = 0;

        for (size_t i = 0; i < values.size(); ++i)
        {
            if (min - values[i] > 0)
            {
                min = values[i];
                index = i;
            }
        }

        ofs << std::setprecision(file_informer.GetPrecision()) << min << '\n';
        array[index] >> values[index];

        if (array[index].eof() || values[index] == 0)
        {
            array.erase(array.begin() + index);
            values.erase(values.begin());
        }
    }
}

void DeleteTempFiles(const FileInformer file_informer)
{
    uint32_t deleted_files = 0;
    for (uint64_t i = 0; i < file_informer.GetNumberFiles(); ++i)
    {
        std::filesystem::remove("temp" + std::to_string(i) + ".txt");
        ++deleted_files;
    }

    std::cout << "Deleted " << deleted_files << " files" << '\n';
}

int main()
{
    std::cout << "Enter RAM limits in megabytes: ";
    uint64_t file_limits;
    std::cin >> file_limits;

    std::cout << "Enter double precision: ";
    uint64_t precision;
    std::cin >> precision;

    FileInformer file_informer(file_limits, precision);

    {
        LOG_DURATION("Total");

        {
            LOG_DURATION("Create");
            CreateFile<double>(file_informer);
        }

        {
            LOG_DURATION("Split");
            SplitFile<double>(file_informer);
        }

        {
            LOG_DURATION("Sort");
            SortTempFiles<double>(file_informer);
        }

        {
            LOG_DURATION("Merge");
            MergeFiles<double>(file_informer);
        }

        {
            LOG_DURATION("Delete");
            DeleteTempFiles(file_informer);
        }
    }
}