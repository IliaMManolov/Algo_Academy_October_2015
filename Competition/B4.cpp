#include <bits/stdc++.h>
using namespace std;

vector<int> fl(131072);

void KMP(const vector<int> &text, const vector<int>& pattern, vector<int>& target)
{
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
            //cout<<"Found at "<<i-j+1<<endl;
            target.push_back(i-j+1);
        }

    }
}


unsigned short toShort(char a, char b)
{
    unsigned short c, d;
    if (a<='9')
        c = a-'0';
    else
        c = a-'a'+10;

    if (b<='9')
        d = b-'0';
    else
        d = b-'a'+10;
    //cout<<c<<' '<<d<<endl;
    return c*16+d;

}

void toDec(const string& source, vector<int> &target)
{
    for (int i=0;i<source.size();i+=2)
        target.push_back(toShort(source[i], source[i+1]));

    //for (int i=0;i<target.size();i++)
    //    cout<<target[i]<<' ';
    //cout<<endl;
}


string pat[128];
vector<int> pat_int[128];


int main()
{
    string text;
    vector<int> text_int;
    vector<int> target;
    int N;

    cin>>N;

    for (int i=0;i<N;i++)
    {
        cin>>pat[i];
        toDec(pat[i], pat_int[i]);
    }

    cin>>text;
    toDec(text, text_int);

    for (int i=0;i<N;i++)
    {
        fl.clear();
        fl[0] = -1;
        fl[1] = 0;

        KMP(text_int, pat_int[i], target);

        for (int j=0;j<target.size();j++)
            for (int k=0;k<pat[i].size();k++)
                text[target[j]*2+k] = '@';

        target.clear();

    }

    cout<<text<<endl;

    return 0;


}
