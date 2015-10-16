#include <bits/stdc++.h>
using namespace std;

const unsigned long long mod[2] = {1000000087, 1000000093};
const int base[2] = {271, 277};

unsigned long long powers[2][131072] = {{1}, {1}};


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


void hashify(const vector<int>& target, const vector<int>& source, vector<int>& result, bool mode = false)
{
    unsigned long long rollingHash = 0;
    unsigned long long sourceHash = 0;

    for (int i=0;i<source.size();i++)
    {
        rollingHash = (rollingHash * base[mode] + target[i]) % mod[mode];
        sourceHash = (sourceHash * base[mode] + source[i]) % mod[mode];
    }

    if (sourceHash == rollingHash)
    {
        result.push_back(0);
    }

    for (int i=source.size();i<target.size();i++)
    {
        rollingHash = (rollingHash * base[mode] + target[i]) % mod[mode];
        unsigned long long subtr = target[i-source.size()];
        subtr*= powers[mode][source.size()];
        rollingHash = (mod[mode]*mod[mode] + rollingHash - subtr) % mod[mode];

        if (rollingHash == sourceHash)
        {
            result.push_back(i-source.size()+1);
        }
    }


}



string pat[128];
vector<int> pat_int[128];


int main()
{
    string text;
    vector<int> text_int;
    vector<int> target;
    vector<int> target2;
    int N;

    cin>>N;

    for (int i=0;i<N;i++)
    {
        cin>>pat[i];
        toDec(pat[i], pat_int[i]);
    }

    cin>>text;
    toDec(text, text_int);

    for (int i=1;i<text.size();i++)
    {
        powers[0][i] = (powers[0][i-1] * base[0])%mod[0];
        powers[1][i] = (powers[1][i-1] * base[1])%mod[1];
    }

    for (int i=0;i<N;i++)
    {
        hashify(text_int, pat_int[i], target, false);
        hashify(text_int, pat_int[i], target2, true);

        for (int j=0;j<target.size();j++)
        {
            if (find(target2.begin(), target2.end(), target[j]) != target2.end())
            {
                for (int k=0;k<pat[i].size();k++)
                    text[target[j]*2+k] = '@';
            }

        }

        /*for (int j=0;j<target.size();j++)
            cout<<target[j]<<' ';
        cout<<endl;
        for (int j=0;j<target2.size();j++)
            cout<<target2[j]<<' ';
        cout<<endl;

        for (int j=0;j<target.size();j++)
            for (int k=0;k<pat[i].size();k++)
                text[target[j]*2+k] = '@';*/
        target.clear();
        target2.clear();
    }

    cout<<text<<endl;

    return 0;


}
