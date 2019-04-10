#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    for(int k=1; k<=n; k++)
    {
        int m;
        scanf("%d",&m);
        int a[m];
        for(int i=0; i<m; i++)
        {
            scanf("%d",&a[i]);
        }
        int b[m];
        b[0]=a[0];
        int maxValue=a[0],x=0,y;
        for(int i=1; i<m; i++)
        {

            b[i]=max(a[i],b[i-1]+a[i]);
            if(b[i]>maxValue)
            {
                maxValue=b[i];
                y=i;
            }
        }
        int value;
        for(int i=0; i<=y; i++)
        {
            value=0;
            for(int j=i; j<=y; j++)
            {
                value+=a[j];
            }
            if(value==maxValue)
            {
                x=i;
                break;

            }
        }
        printf("Case #%d:\n",k);
        printf("%d %d %d\n\n",maxValue,x+1,y+1);
    }
    return 0;
}
