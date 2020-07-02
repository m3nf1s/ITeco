#include <regex>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream ifs("input.txt");
    std::ofstream ofs("output.txt");
    std::string pattern, line;

    std::getline(std::cin, pattern);

    const std::regex regex(pattern);

    while (ifs.is_open())
    {
        std::getline(ifs, line);
        if (std::regex_search(line, regex))
        {
            ofs << line << '\n';
        }
        

        if (ifs.eof())
        {
            ifs.close();
            ofs.close();
        }
    }
	
    return 0;
}
