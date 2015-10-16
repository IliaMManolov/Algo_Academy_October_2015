#include <bits/stdc++.h>
using namespace std;

bool cmp(char a, char b)
{
    if (a<='9')
    {
        if (b<='9')
        {
            if (a=='0')
                a+=10;
            if (b=='0')
                b+=10;
            return a<b;
        }
        return false;
    }
    else if (a<='Z')
    {
        if (b<='9')
        {
            return true;
        }
        else if (b<='Z')
        {
            return a<b;
        }
        return a<=(b-'a')+'A';
    }

    if (b<='9')
        return true;
    else if (b<='Z')
        return a<(b-'A')+'a';
    return a<b;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    string hua;
    int N;
    cin>>N;
    for (int i=0;i<N;i++)
    {
        int tmp;
        char hue;
        cin>>tmp;
        hue = (char) tmp;

        if (((hue>='0'&&hue<='9') || (hue>='a'&&hue<='z') || (hue>='A' && hue<='Z')) && hue!='x')
            hua +=hue;
    }
    sort(hua.begin(), hua.end(), cmp);


    cout<<hua<<endl;
    return 0;
}
