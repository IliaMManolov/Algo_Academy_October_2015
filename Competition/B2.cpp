#include <bits/stdc++.h>

using namespace std;

/*const unsigned long long mod = 1000000007;
const unsigned long long mod2 = 1000000009;
const int base = 271;
const int base2 = 263;*/

unsigned long long powers[2][131072] = {1};

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
    return c*16+d;

}

void hashify(const string& text, const string& pattern, vector<int>& target, const int base, const unsigned long long mod, bool which)
{
    unsigned long long patternHash = 0;
    unsigned long long rollingHash = 0;

    for (int i=0;i<pattern.size();i+=2)
    {
        patternHash = (patternHash * base + toShort(pattern[i], pattern[i+1])) % mod;
    }

    for (int i=0;i<pattern.size();i+=2)
    {
        rollingHash = (rollingHash*base + toShort(text[i], text[i+1]))%mod;
    }

    //cout<<"Pattern Hash is "<<patternHash<<' '<<rollingHash<<endl;

    if (rollingHash == patternHash)
    {
        target.push_back(0);
    }

    for (int i=pattern.size();i<=(int)text.size();i+=2)
    {
        rollingHash = (rollingHash*base + toShort(text[i], text[i+1]))%mod;
        unsigned long long subtr = toShort(text[i-pattern.size()], text[i-pattern.size()+1]);
        subtr *= powers[which][pattern.size()/2];

        rollingHash = (mod*mod + rollingHash - subtr)%mod;


        if (rollingHash == patternHash)
        {
            target.push_back(i-pattern.size()+1);
        }

        //cout<<"Rolling Hash is "<<rollingHash<<endl;


    }
}


void rep(string& text, string& pattern)
{
    vector<int> target1, target2;

    hashify(text, pattern, target1, 271, 1000000007, false);
    //hashify(text, pattern, target2, 263, 1000000009, true);

    int j=0;
    //cout<<target2[0]<<endl;

    for (int i=0;i<target1.size();i++)
    {
        cout<<target1[i]<<endl;

        /*for (int hue = j;hue<target2.size();hue++)
            if (target2[hue] == target1[i])
            {
                break;
                j = hue;
            }
*/
        //if (j<target2.size())
        //{
            for (int k=0;k<pattern.size();k++)
                text[k+target1[i]+1] = '@';
        //}

    }
}

string pat[128];

int main()
{
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
        powers[0][i] = (powers[0][i-1] * 271)%1000000007;
        powers[1][i] = (powers[1][i-1] * 263)%1000000009;
    }



    for (int i=0;i<N;i++)
        rep(txt, pat[i]);

    cout<<txt<<endl;



    return 0;
}
