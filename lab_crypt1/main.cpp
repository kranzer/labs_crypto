#include <iostream>
#include <map>
using namespace std;

map<char, int> symbolFrequency(const char *);
map<string, int> biagramFrequency(const char *);

int main()
{
    const char *a = "afasfasfasf";
    map <char, int>symbolFrequencyTable = symbolFrequency(a);
    for(auto const &it: symbolFrequencyTable)
    {
        cout << it.first << " - " << double(it.second) / strlen(a) << endl;
    }
    map <string, int>biagramFrequencyTable = biagramFrequency(a);
    for(auto const &it: biagramFrequencyTable)
    {
        cout << it.first << " - " << double(it.second) / biagramFrequencyTable.size() << endl;
    }

}

map<char, int> symbolFrequency(const char *text)
{
    map<char, int> frequencyTable = {};
    for(const char *symbol = text; *symbol; ++symbol)
    {
        if(frequencyTable.find(*symbol) != frequencyTable.end())
        {
            // Found
            frequencyTable[*symbol] += 1;
        } else {
            // Not found
            frequencyTable.insert(pair<char,int>(*symbol, 1));
        }
    }
    return frequencyTable;
}

map<string, int> biagramFrequency(const char *text)
{
    map<string, int> frequencyTable = {};
    for(const char *symbol = text; *symbol; ++symbol)
    {
        string buffer = "";
        buffer.push_back(*symbol);
        buffer.push_back(*(symbol+1));
        if(frequencyTable.find(buffer) != frequencyTable.end())
        {
            //Found
            frequencyTable[buffer] += 1;
        } else {
            //Not found
            if(buffer.length() > 1 && buffer[1] != '\0')
                frequencyTable.insert(pair<string,int>(buffer, 1));
        }
    }
    return frequencyTable;
}


