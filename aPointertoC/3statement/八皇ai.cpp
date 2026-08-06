#include <stdio.h>
#include <math.h>

int q[8];   // q[行] = 列
int cnt;
// 放第n行
void dfs(int n)
{
    if(n == 8) { cnt++; return; }  // 8行全放完，找到解

    for(int c=0;c<8;c++)
    {
        int ok=1;
        // 和前面所有行比较
        for(int i=0;i<n;i++)
            if(c==q[i] || abs(n-i)==abs(c-q[i])) { ok=0; break; }
        
        if(ok) { q[n]=c; dfs(n+1); }
    }
}

int main()
{
    dfs(0);
    printf("总解数：%d\n",cnt);
    return 0;
}
