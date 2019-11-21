#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctype.h>
//#include <regex>

std::pair<std::string, int> getstring(const char *buffer, int i, int min, int max)
{
    std::string str;
    while (isprint(buffer[i]) || isprint(buffer[i+1]))
    {   
        if (isprint(buffer[i])){
            str += buffer[i];
        }
        i++;
    }
    if (str.size() > min && str.size() < max){
        return std::make_pair(str, i);
    }
    return std::make_pair("0", i);
}

void parsebin(char *input, char *output)
{
    std::vector<std::string> strings;
    std::ofstream out;
    out.open(output);
    std::ifstream is(input, std::ios::binary);

    // Get length of the file
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

/*
    const std::regex rgx("(.)\\1{3}");
    std::smatch match;*/

    char *buffer = new char[length];
    is.read(buffer, length);
    bool printable = false;
    for (int i = 0; i < length; i++)
    {
        if (isprint(buffer[i]))

        {
            std::pair<std::string, int> pair = getstring(buffer, i, 5, 150);
            i = pair.second;
            if (pair.first.size() > 1 /*&& !std::regex_search(pair.first, match, rgx)*/){
                strings.push_back(pair.first);
            }
        }
    }
    // Remove duplicates
    strings.erase( unique(strings.begin(), strings.end()), strings.end());

    // Write strings to output file
    std::ostream_iterator<std::string> output_iterator(out, "\n");
    std::copy(strings.begin(), strings.end(), output_iterator);
    
    std::cout << "File parsed\n";
    is.close();
    out.close();
    delete[] buffer;
}

int main()
{
    parsebin("/home/invasys.org/xroora/Desktop/platform-tools/all", "all_out");
    return 0;
}