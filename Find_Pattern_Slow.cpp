#include <bits/stdc++.h>
using namespace std;
int main()
{
    string text, pattern;

    getline(cin, text);
    cin>>pattern;

    for (int i=0;i<=int (text.size())-int (pattern.size());i++)                  //.size() return an unsigned value
    {
        bool found = true;
        for (int j=0;j<pattern.size();j++)
            if (pattern[j] != text[i+j])
            {
                found = false;
                break;
            }
        if (found == true)
        {
            cout<<"Pattern found at "<<i<<"."<<endl;
        }
    }


    return 0;
}
