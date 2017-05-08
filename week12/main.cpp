#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <fstream>
using namespace std;
set<string> openDictionary()
{
    ifstream dic;
    while(true)
    {
        cout<<"Dictionary file name?";
        string name;
        cin>>name;
        dic.open(name.c_str());
        if(dic) {break;}
        else {cout<<"Unable to open that file.  Try again."<<endl;}
    }
    string word;
    set<string> dictionary;
    while(dic >> word)
    {
        dictionary.insert(word);
    }
    return dictionary;
}
int cmp(const pair<string,int> &x, const pair<string,int>&y)
{
    return x.second>y.second;
}
void sortWord_map(map<string,vector<string>>& word_map, vector<pair<string,int>>& word_vector)
{
    for(map<string,vector<string>>::iterator iter = word_map.begin();iter != word_map.end();++iter)
    {
        vector<string> words = iter -> second;
        int numOfWords = words.size();
        string suffix = iter -> first;
        word_vector.push_back(make_pair(suffix,numOfWords));
    }
    sort(word_vector.begin(),word_vector.end(),cmp);
}
void coutVector(vector<string> words)
{
    for (vector<string>::reverse_iterator it = words.rbegin();it != words.rend();++it)
    {
        cout << *it << " ";
    }
}
int main()
{
    set<string> dictionary = openDictionary();
    cout<<"please input number:";
    unsigned long number = 0;
    cin>>number;
    map<string,vector<string>> word_map;
    set<string>::iterator iter = dictionary.begin();
    while(iter != dictionary.end())
    {
        string s = *iter;
        if(s.length() < number){++iter;}
        else
        {
            string suffix = s.substr(s.length()-number,number);
            if(word_map.count(suffix) == 0)
            {
                vector<string> wordsOfSuffix;
                wordsOfSuffix.push_back(s);
                word_map.insert(map<string,vector<string>>::value_type(suffix,wordsOfSuffix));
            }
            else
            {
                vector<string> wordsOfSuffix = word_map[suffix];
                wordsOfSuffix.push_back(s);
                word_map[suffix] = wordsOfSuffix;
            }
            ++iter;
        }
    }
    vector<pair<string,int>>word_vector;
    sortWord_map(word_map,word_vector);
    for(int i = 0; i < 10;++i)
    {
        cout<<word_vector[i].first<<":";
        coutVector(word_map[word_vector[i].first]);
        cout<<endl;
    }
    cout<<"please input suffix"<<endl;
    string findSuffix;
    cin>>findSuffix;
    coutVector(word_map[findSuffix]);
}