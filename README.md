# 金明的预算 依赖型背包问题
NOIP2006 金明的预算，信息技术奥赛课本: 背包问题，依懒型背包问题；

方法：这个问题，可以把依懒关系构建成一个森林（若干个n岔树），进一步，我们可以认为设置一个根节点，把这个森林变成一颗n岔树。然后我们使用dfs和dp相结合的方法，可以设计出一个正确的算法。
注意：这个算法非常耗时，一个层级的嵌套，大致时间复杂度是O(n^3)，如果是多个层级的嵌套（尤其是3个及以上），耗时将非常长，可能少则数小时。我提供的例子，是2个层级的。
备注：这个算法，我分成了dfs和dp彻底分离的结构，以及dp不显示写出，而是嵌入在dfs中，成为dfs代码的一部分的2种写法。前者文件名：depending_bagging_2.c++；后者文件名：depending_bagging.c++。

原问题链接：
https://blog.csdn.net/m0_64109657/article/details/124950013

原文：
P1064 [NOIP2006 提高组] 金明的预算方案
题意
[NOIP2006 提高组] 金明的预算方案
题目描述
金明今天很开心，家里购置的新房就要领钥匙了，新房里有一间金明自己专用的很宽敞的房间。更让他高兴的是，妈妈昨天对他说：“你的房间需要购买哪些物品，怎么布置，你说了算，只要不超过 n nn 元钱就行”。今天一早，金明就开始做预算了，他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：

主件	附件
电脑	打印机，扫描仪
书柜	图书
书桌	台灯，文具
工作椅	无
如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 0 00 个、1 11 个或 2 22 个附件。每个附件对应一个主件，附件不再有从属于自己的附件。金明想买的东西很多，肯定会超过妈妈限定的 n nn 元。于是，他把每件物品规定了一个重要度，分为 5 55 等：用整数 1 ∼ 5 1 \sim 51∼5 表示，第 5 55 等最重要。他还从因特网上查到了每件物品的价格（都是 10 1010 元的整数倍）。他希望在不超过 n nn 元的前提下，使每件物品的价格与重要度的乘积的总和最大。

设第 j jj 件物品的价格为 v j v_jv 
j
​
 ，重要度为w j w_jw 
j
​
 ，共选中了 k kk 件物品，编号依次为 j 1 , j 2 , … , j k j_1,j_2,\dots,j_kj 
1
​
 ,j 
2
​
 ,…,j 
k
​
 ，则所求的总和为：

v j 1 × w j 1 + v j 2 × w j 2 + ⋯ + v j k × w j k v_{j_1} \times w_{j_1}+v_{j_2} \times w_{j_2}+ \dots +v_{j_k} \times w_{j_k}v 
j 
1
​
 
​
 ×w 
j 
1
​
 
​
 +v 
j 
2
​
 
​
 ×w 
j 
2
​
 
​
 +⋯+v 
j 
k
​
 
​
 ×w 
j 
k
​
 
​
 。

请你帮助金明设计一个满足要求的购物单。

输入格式
第一行有两个整数，分别表示总钱数 n nn 和希望购买的物品个数 m mm。

第 2 22 到第 ( m + 1 ) (m + 1)(m+1) 行，每行三个整数，第 ( i + 1 ) (i + 1)(i+1) 行的整数 v i v_iv 
i
​
 ，p i p_ip 
i
​
 ，q i q_iq 
i
​
  分别表示第 i ii 件物品的价格、重要度以及它对应的的主件。如果 q i = 0 q_i=0q 
i
​
 =0，表示该物品本身是主件。

输出格式
输出一行一个整数表示答案。

样例 #1
样例输入 #1
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
1
2
3
4
5
6
样例输出 #1
2200
1
提示
数据规模与约定
对于全部的测试点，保证 1 ≤ n ≤ 3.2 × 1 0 4 1 \leq n \leq 3.2 \times 10^41≤n≤3.2×10 
4
 ，1 ≤ m ≤ 60 1 \leq m \leq 601≤m≤60，0 ≤ v i ≤ 1 0 4 0 \leq v_i \leq 10^40≤v 
i
​
 ≤10 
4
 ，1 ≤ p i ≤ 5 1 \leq p_i \leq 51≤p 
i
​
 ≤5，0 ≤ q i ≤ m 0 \leq q_i \leq m0≤q 
i
​
 ≤m，答案不超过 2 × 1 0 5 2 \times 10^52×10 
5
 。

tags
有依赖的背包

思路
对于每个主件，我们可以有一下选择

只选主件
选主件与附件1
选主件与附件2
这种思想和多重背包有点像，把主件与附件看成一个背包

联立组件和附件与组合背包方式一样(二维数组)，不过在枚举物品的时候全部枚举（对于不是主件的物品由于没赋值对结果没有影响）

AC代码
#include<bits/stdc++.h>
using namespace std;

const int maxn=4e4,maxm=70;
int n,m;
int zm[maxm],zv[maxm],fm[maxm][maxm],fv[maxm][maxm],num[maxm];
int dp[maxn];

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        if(!z){
            zv[i]=x;
            zm[i]=y*x;
        }
        else{
            num[z]++;
            fv[z][num[z]]=x;
            fm[z][num[z]]=y*x;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=n;j>=zv[i];j--){
            dp[j]=max(dp[j],dp[j-zv[i]]+zm[i]);
            if(j>=zv[i]+fv[i][1])dp[j]=max(dp[j],dp[j-zv[i]-fv[i][1]]+fm[i][1]+zm[i]);
            if(j>=zv[i]+fv[i][2])dp[j]=max(dp[j],dp[j-zv[i]-fv[i][2]]+fm[i][2]+zm[i]);
            if(j>=zv[i]+fv[i][2]+fv[i][1])dp[j]=max(dp[j],dp[j-zv[i]-fv[i][1]-fv[i][2]]+fm[i][1]+fm[i][2]+zm[i]);
        }
    }
    cout<<dp[n]<<endl;
}
————————————————
版权声明：本文为CSDN博主「meet snow happy」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/m0_64109657/article/details/124950013
