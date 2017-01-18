#include <iostream>
#include <fstream>
#include <string>
#include "node.h"
#include "trie.h"
using namespace std;

int * check_test_case(string test, Trie * t, int len);
int find_start_index(int * indicator, int current);
void test_case(int i, Trie * t, int len);
void print_original_text(int * indicator, string test1);

int main()
{
    Trie * t = new Trie();                      // trie tree
    ifstream inFile("wordlist.txt", ios::in);   // fstream for file
    if(inFile.fail())
    {
        cerr << "cannot open file\n";
        return 0;
    }
    char tmp[255];
    int max_length = 0;                         // the max length in the wordlist, so that don't have to do useless check
    int tmp_length = 0;
    while(!inFile.eof())                        // open the file and read line by line
    {
        inFile.getline(tmp, 255);
        string line(tmp);                       // line buffer
        tmp_length = line.length() - 1;
        t->addWord(line.substr(0, tmp_length));      // add to the trie
        if(tmp_length > max_length)
            max_length = tmp_length;            // always hold the max length
    }
    inFile.close();

    for(int i = 1; i <= 5; i++)
        test_case(i, t, max_length);            // test the given files

    return 0;
}

// test if the given file is convertable. If yes, then print the split words out
void test_case(int i, Trie * t, int len)
{
    cout << "\n ===============================test" << i <<"===============================\n";
    string filename = "test";
    filename += to_string(i);
    filename += ".txt";
    ifstream inFile(filename, ios::in);         // open test case
    if(inFile.fail())
    {
        cerr << "cannot open file\n";
        return;
    }
    string test((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));    // take in the content
    int * indicator = check_test_case(test, t, len);        // an array of indicator of whether the string can be converted to words at that position or not
    if(indicator != NULL)       // if the text is convertable
        print_original_text(indicator, test);
    inFile.close();
}

// check if the string is convertable
int * check_test_case(string test, Trie * t, int len)
{
    int n = test.length();
    int * indicator = new int[n];
    for(int i = 0; i < n; i++)
        indicator[i] = 0;
    string tmp;
    int j;
    bool go_next = false;           // don't stuck at zero
    for(int i = 0; i < n; i++)
    {
        tmp = "";                   // tmp holder for the word to be checked
        j = find_start_index(indicator, i);
        while(j >= 0 && !go_next)
        {
            if(j == 0)
                go_next = true;     // only stuck at zero once
            tmp = test.substr(j, i - j + 1);
            if(tmp.length() > len)      // the "word" to be searched in the trie is even longer than the longest word in the dict, so no need to call the search function, just go to the next one
            {
                indicator[i] = 0;
                break;
            }
            indicator[i] = t->searchWord(tmp);
            if(indicator[i] != 0)
                break;              // great, string could be cut here
            else
                j = find_start_index(indicator, j - 1);     // find the next possible position to cut
        }
        go_next = false;
        // if(indicator[i])
            // cout << tmp << " indicator: " << indicator[i] << endl;
    }
    if(indicator[n - 1] != 0)
        return indicator;
    else
        return NULL;
}

// find a legitimate position to start (previous element is a legitimate end)
int find_start_index(int * indicator, int current)
{
    if(current == 0)
        return 0;
    int index = current;
    while(index > 0)
    {
        if(indicator[index - 1])        // find the position whose previous position is a legit end of a word
            return index;
        index--;
    }
    return index;
}

// print out the original test (in forward and reverse order)
void print_original_text(int * indicator, string test)
{
    int i = test.length() - 1;
    string tmp_string;
    vector<string> tmp_list;
    while(i >= 0)               // print the words in reversed order
    {
        if(indicator[i] != 0)
        {
            tmp_string = test.substr(i - indicator[i] + 1, indicator[i]) + '\0';
            i = i - indicator[i];
            cout << tmp_string << ' ';
            tmp_list.push_back(tmp_string);         // add it to the vector for printing it out in the right order
        }
    }
    cout << "\n ========== right order ========== \n";
    for(int i = tmp_list.size() - 1; i >= 0; i--)   // print the words in the right order
        cout << tmp_list[i] << ' ';
    cout << endl;
}
