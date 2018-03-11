#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <locale>
using namespace std;

map<char, int> symbolFrequency(const string&);
map<string, int> biagramFrequency(const string&);
double symbolEntropy(const vector<double>&);
double biagramEntropy(const vector<double>&);

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF8");
    std::ifstream input1("text1.txt", std::ios::binary);
    std::string a((std::istreambuf_iterator<char>(input1)),
                         {});
    map <char, int>symbolFrequencyTable = symbolFrequency(a);
    vector<double> sym_vec = {};

    for(auto const &it: symbolFrequencyTable)
    {
        double frequency = double(it.second) / a.length();
        cout << it.first << " - " << frequency << endl;
        sym_vec.push_back(frequency);

    }

    cout << "H1= " << symbolEntropy(sym_vec) << endl;

    map <string, int>biagramFrequencyTable = biagramFrequency(a);
    vector<double> bia_vec = {};
    for(auto const &it: biagramFrequencyTable)
    {
        double frequency = double(it.second) / biagramFrequencyTable.size();
        cout << it.first << " - " << it.second << endl;
        bia_vec.push_back(frequency);
    }

    cout << "H2= " << biagramEntropy(bia_vec) << endl;
}

map<char, int> symbolFrequency(const string& text)
{
    map<char, int> frequencyTable = {};
    for(string::const_iterator symbol = text.begin(); symbol != text.end(); ++symbol)
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

map<string, int> biagramFrequency(const string& text)
{
    map<string, int> frequencyTable = {};
    for(string::const_iterator symbol = text.begin(); symbol != text.end(); ++symbol)
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

double symbolEntropy(const vector<double>& freq)
{
    double result = 0.0;
    for (const auto i: freq)
    {
        result += (i*log2(i));
    }
    return result*(-1);
}

double biagramEntropy(const vector<double>& freq)
{
    double result = 0.0;
    for (const auto i: freq)
    {
        result += (i*log2(i));
    }
    return result*(-1)/2;
}
