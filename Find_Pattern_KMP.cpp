#include <bits/stdc++.h>

using namespace std;


int fl[1024] = {-1, 0};
int main()
{
    string text, pattern;
    getline(cin, text);
    cin>>pattern;

    for (int i=1;i<(int)pattern.size();i++)
    {
        int j = fl[i];
        while (j>=0 && pattern[i] != pattern[j])
        {
            j = fl[j];
        }
        fl[i+1] = j + 1;
    }

    int j = 0;

    for (int i=0;i<text.size();i++)
    {
        while (j>=0 && text[i] != pattern[j])
        {
            j = fl[j];
        }

        j++;

        if (j == (int) pattern.size())
        {
            cout<<"Found at "<<i-j+1<<endl;
        }

    }

    return 0;
}
