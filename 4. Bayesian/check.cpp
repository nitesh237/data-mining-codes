#include <stdio.h>
#define ll long long int

ll find_com(ll n) {
	ll ans = n;
	ans*=(n - 1);
	ans/=2;
	return ans;
}
int main(void) {
	int t;
	ll m[1010];
	scanf("%d",&t);
	while(t--) {
	    ll n,i,j;
	    scanf("%lld",&n);
	    ll A[n],c=0,key;
	    for(i=0;i<n;i++)
	    {
	       scanf("%lld",&A[i]);
	  
	  	}
	    
        for ( i=0; i<=1005; i++)
         {
             m[i]=0;
         }
	
	        
        for ( i=1; i<=n; i++)
         m[A[i-1]]++;
        
	    
	   for(i=1;i<=1005;i++)
	   {
	   	c+=find_com(m[i]);
	   	for(j=i;j<=1005;j++)
	   	{
	       if((i+j)%2==0 && m[i]>0 && m[j]>0)
	       {
	           key=(i+j)/2;
	           if(m[key]>0)
	           {
	           
	               c=c+m[i]*m[j]
	           }
	       }
	   }
	       
	   }
	    prllf("%lld\n",c);
	}
	return 0;
}
