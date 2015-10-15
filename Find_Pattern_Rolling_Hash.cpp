#include <bits/stdc++.h>
using namespace std;

const unsigned long long mod = 1000000007;
const int base = 271;

unsigned long long powers[1048576] = {1};

int main()
{
    string text, pattern;
    getline(cin, text);
    cin>>pattern;

    for (int i=1;i<text.size();i++)
    {
        powers[i] = (powers[i-1] * base)%mod;
    }

    unsigned long long patternHash = 0;
    unsigned long long rollingHash = 0;

    for (int i=0;i<pattern.size();i++)
    {
        patternHash = (patternHash * base + (unsigned char)pattern[i]) % mod;
    }

    for (int i=0;i<pattern.size();i++)
    {
        rollingHash = (rollingHash*base + (unsigned char)text[i])%mod;
    }

    //cout<<"Pattern Hash is "<<patternHash<<' '<<rollingHash<<endl;

    if (rollingHash == patternHash)
    {
        cout<<"Found at 0"<<endl;
    }

    for (int i=pattern.size();i<=(int)text.size();i++)
    {
        rollingHash = (rollingHash*base + (unsigned char) text[i])%mod;
        unsigned long long subtr = (unsigned char)text[i-pattern.size()];
        subtr *= powers[pattern.size()];

        rollingHash = (mod*mod + rollingHash - subtr)%mod;


        if (rollingHash == patternHash)
        {
            cout<<"Found at "<<i-pattern.size()+1<<endl;
        }

        //cout<<"Rolling Hash is "<<rollingHash<<endl;


    }



    return 0;
}
