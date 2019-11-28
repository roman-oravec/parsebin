#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctype.h>
#include <string>

std::pair<std::string, int> getstring(const char *buffer, int i, const int min, const int max)
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

void parsebin(const char *input, const char *output, const int min, const int max)
{
    std::vector<std::string> strings;
    std::ofstream out;
    out.open(output);
    std::ifstream is(input, std::ios::binary);

    // Get length of the file
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char[length];
    is.read(buffer, length);
    bool printable = false;
    for (int i = 0; i < length; i++)
    {
        if (isprint(buffer[i]))

        {
            std::pair<std::string, int> pair = getstring(buffer, i, min, max);
            i = pair.second;
            if (pair.first.size() > 1){
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

int main(int argc,/*input output min max */ char * argv[])
{
    int min, max;
    sscanf(argv[3], "%d", &min);
    sscanf(argv[4], "%d", &max);
    parsebin(argv[1], argv[2], min, max);
    return 0;
}