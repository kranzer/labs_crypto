#include <iostream>
#include <map>
#include <string.h>
#include <vector>
#include <cmath>

using namespace std;

map<char, int> symbolFrequency(const char *);
map<string, int> biagramFrequency(const char *);
double symbolEntropy(const vector<double>&);
double biagramEntropy(const vector<double>&);

int main()
{
    setlocale (LC_CTYPE,"rus");
    FILE * in;
    in=fopen("text.txt","r");
    char c;
    char *a=new char[5000000];
    int n;
    n=0;
    while (fscanf(in,"%c",&c) != EOF)
    {
        a[n++] = c;
        if ((c==' ' || c=='\t' || c=='\n') && a[n-1]!=' ')
        {
            a[n++]=' ';
        }
    }
    cout << a;
    fclose(in);
    map <char, int>symbolFrequencyTable = symbolFrequency(a);
    vector<double> sym_vec = {};

    for(auto const &it: symbolFrequencyTable)
    {
        double frequency = double(it.second) / strlen(a);
        cout << it.first << " - " << frequency << endl;
        sym_vec.push_back(frequency);

    }

    cout << "H1= " << symbolEntropy(sym_vec) << endl;

    map <string, int>biagramFrequencyTable = biagramFrequency(a);
    vector<double> bia_vec = {};
    for(auto const &it: biagramFrequencyTable)
    {
        double frequency = double(it.second) / biagramFrequencyTable.size();
        cout << it.first << " - " << frequency << endl;
        bia_vec.push_back(frequency);
    }

    cout << "H2= " << biagramEntropy(bia_vec) << endl;
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

