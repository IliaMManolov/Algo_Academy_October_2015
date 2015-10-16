#include <bits/stdc++.h>
using namespace std;

const unsigned long long mod = 1000000007;
const unsigned long long mod2 = 1000000009;
const int base = 271;
//const int base2 = 263;

unsigned long long powers[131072] = {1};

unsigned short toShort(char a, char b)
{
    short c, d;
    if (a>='0' && a<='9')
        c = (int) a-'0';
    else
        c = (int) a -'a'+10;

    if (b>='0' && b<='9')
        d = (int) b-'0';
    else
        d = (int) b-'a'+10;

    cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<c*16+d<<endl;

    return c*16+d;
}

void rep(string &text, string &pattern)
{
    unsigned long long patternHash = 0;
    unsigned long long rollingHash = 0;
    vector<int> targets1;
    vector<int> targets2;

    for (int i=0;i<pattern.size();i+=2)
    {
        patternHash = (patternHash * base + toShort(pattern[i], pattern[i+1])) % mod;
    }
    cout<<patternHash<<endl;

    for (int i=0;i<pattern.size();i++)
    {
        rollingHash = (rollingHash*base + toShort(text[i], text[i+1]))%mod;
    }

    //cout<<"Pattern Hash is "<<patternHash<<' '<<rollingHash<<endl;

    if (rollingHash == patternHash)
    {
        cout<<"Found at 0"<<endl;
    }

    for (int i=pattern.size();i<=(int)text.size();i+=2)
    {
        rollingHash = (rollingHash*base + toShort(text[i], text[i+1]))%mod;
        unsigned long long subtr = (unsigned char)text[i-pattern.size()];
        subtr *= powers[pattern.size()];

        rollingHash = (mod*mod + rollingHash - subtr)%mod;


        if (rollingHash == patternHash)
        {
            targets1.push_back(i-pattern.size()+1);
        }

        //cout<<"Rolling Hash is "<<rollingHash<<endl;


    }

    for (int i=0;i<targets1.size();i++)
        for (int j=0;j<pattern.size();j++)
            text[targets1[i]+j] = '@';


}

string pat[128];

int main()
{

    //cout<<toShort('f', 'f')<<endl;
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N;
    string txt;

    cin>>N;
    for (int i=0;i<N;i++)
        cin>>pat[i];
    cin>>txt;

    for (int i=1;i<txt.size();i++)
    {
        powers[i] = (powers[i-1] * base)%mod;
    }

    for (int i=0;i<N;i++)
        rep(txt, pat[i]);

    cout<<txt<<endl;


    return 0;
}
