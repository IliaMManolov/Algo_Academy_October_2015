#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

const unsigned long long mod[3] = {1000000007, 1000000009, 1000000031};
const unsigned int base[3] = {271, 277, 281};

unsigned long long powers[3][100000] = {{1}, {1}, {1}};


bool check(const string& a, const string& b, int len, int type)
{
    unordered_set<unsigned long long> setA;
    unsigned long long hashA = 0, hashB = 0;

    for (int i=0;i<len;i++)
        hashA = (hashA*base[type] + a[i])%mod[type];
    setA.insert(hashA);

    for (int i=len;i<a.size();i++)
    {
        hashA = (hashA*base[type] + (unsigned char) a[i])%mod[type];
        unsigned long long subtr = (unsigned char)a[i-len];
        subtr *= powers[type][len];

        hashA = (mod[type]*mod[type] + hashA - subtr)%mod[type];
        setA.insert(hashA);
    }

    //for (auto it = setA.begin();it!=setA.end();it++)
    //    cout<<*it<<' ';
    //cout<<endl;

    for (int i=0;i<len;i++)
        hashB = (hashB*base[type] + b[i])%mod[type];
    if (setA.find(hashB) != setA.end())
        return true;

    for (int i=len;i<b.size();i++)
    {
        //cout<<hashB<<' ';
        hashB = (hashB*base[type] + (unsigned char) b[i])%mod[type];
        unsigned long long subtr = (unsigned char)b[i-len];
        subtr *= powers[type][len];

        hashB = (mod[type]*mod[type] + hashB - subtr)%mod[type];

        if (setA.find(hashB)!=setA.end())
        {
            return true;
        }
    }
    //cout<<hashB<<endl;


    //for (auto it = setA.begin();it!=setA.end();it++)
    //    if (setB.find(*it))
    //        return true;
    return false;

}

int bins(const string& A, const string& B, int type)
{
    int L = 0, R = B.size();
    int M;

    while (L<R)
    {
        M = (L+R)/2;
        //cout<<M<<endl;
        if (check(A, B, M, type) == true)
        {
            L = M+1;
        }
        else
        {
            R = M;
        }
    }
    return L-1;
}



int main()
{
    cin.tie();
    ios::sync_with_stdio(false);

    string hue, hua;

    getline(cin, hua);
    getline(cin, hue);

    if (hua.size()<hue.size())
    {
        swap(hua, hue);
    }
    for (int j=0;j<3;j++)
        for (int i=1;i<hua.size();i++)
            powers[j][i] = (powers[j][i-1]*base[j])%mod[j];

    cout<<min(min(bins(hua, hue, 0), bins(hua, hue, 1)), bins(hua, hue, 2))<<endl;

    return 0;
}
