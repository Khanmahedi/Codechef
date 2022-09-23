#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define ll      long long
#define pb      push_back
#define TT ll time;        cin >> time; while(time--)
#define FastIo  ios_base::sync_with_stdio(false);cin.tie(NULL) ;
const ll int INF = 5e18 , nmax = 2501 , block = 350 , N = 2e6 +10;
#ifndef ONLINE_JUDGE
#include "algodebug.h"
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define MAX_N 2000100                        
int RA[MAX_N], tempRA[MAX_N] , RANK[MAX_N];                 
int SA[MAX_N], tempSA[MAX_N], LCP[MAX_N];                 
int c[MAX_N];
struct SUffix_Array{
      string T ;
      int n ;
    SUffix_Array(string s){
           T = s ;
           n = s.size() ;

    }                                  
void countingSort(int k) {                      
            int i, sum, maxi = max(300, n);                
            memset(c, 0, sizeof c);  
            for (i = 0; i < n; i++)   
            c[i + k < n ? RA[i + k] : 0]++;
            for (i = sum = 0; i < maxi; i++){
              int t = c[i]; c[i] = sum; sum += t; 
            }
            for (i = 0; i < n; i++)  
              tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
            for (i = 0; i < n; i++)     
            SA[i] = tempSA[i];
}
void BuildSA() {    
        int i, k, r;
        for (i = 0; i < n; i++) RA[i] = T[i];          
        for (i = 0; i < n; i++) SA[i] = i;           
        for (k = 1; k < n; k <<= 1) {                 
        countingSort(k);                              
        countingSort(0);                               
        tempRA[SA[0]] = r = 0;                        
        for (i = 1; i < n; i++)                       
        tempRA[SA[i]] =                              
        (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)                        
        RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;                 
} }
 //kasai ALgorithm for LCP Array
void Get_Lcp(){  // 0 indexed based
  for(ll i = 0 ; i < n ; i++) RANK[SA[i]] = i ;
  ll k = 0 ;
  for( ll i = 0 ; i < n ; i++){
      ll ind1 = RANK[i] , ind2 = ind1 - 1 ;
      if(ind1 != 0){
         while(T[SA[ind1]+k] == T[SA[ind2]+k] and ind1+k < n and ind2+k<n) k++ ;
         LCP[RANK[i]] = k ;if(k > 0) k-- ;
      }}
    }
  void print(){
    for( ll i = 0 ; i < n ; i++){
      ll start = SA[i] ;
      for( ll j = start ; j < n ; j++) cout << T[j] ;
        cout << endl ;
    }
  }

};



int main()
{
   

   string tem , s = "";
   cin >> tem ;
   ll nn , temp = 0 ;
   s+=tem ;
   nn = s.size() ;
   s+='$' ;
   cin >> tem ;
   s+=tem ;
   SUffix_Array sa(s) ;
   sa.BuildSA() ;
   sa.Get_Lcp() ;
  //  sa.print() ;
  //  // for(ll i = 0; i < s.size() ; i++){
  //  //   cout << LCP[i] << " " ;
  //  // }
  //  // cout << endl ;
  //    cout << "SA : " << endl ;
  // for( ll i = 0 ; i < s.size() ; i++) cout << SA[i] << " " ;
  // cout << endl ;
  // cout << "LCP : " << endl ;
  // for( ll i =  0; i < s.size() ; i++) cout << LCP[i] << " " ;
  //   cout << endl ;
  int max_lcp = 0 , cur_lcp , start_ind;
  bool on = false ;
  for (int i = 0; i < s.size() - 1; i++) {
    if (SA[i] < nn && SA[i + 1] > nn) {
      on = true;
      cur_lcp = LCP[i+1];
      if (cur_lcp > max_lcp) {
        max_lcp = cur_lcp;
        start_ind = SA[i + 1];
      } else if (cur_lcp == max_lcp) {
        start_ind = min(start_ind, SA[i + 1]);
      }
    } else if (on && SA[i] > nn && SA[i + 1] > nn) {
      cur_lcp = min(cur_lcp, LCP[i+1]);
      if (cur_lcp == max_lcp) {
        start_ind = min(start_ind, SA[i + 1]);
      }
    } else {
      on = false;
    }
  }
  on = false;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (SA[i] > nn && SA[i + 1] < nn) {
      on = true;
      cur_lcp = LCP[i+1];
      if (cur_lcp > max_lcp) {
        max_lcp = cur_lcp;
        start_ind = SA[i];
      } else if (cur_lcp == max_lcp) {
        start_ind = min(start_ind, SA[i]);
      }
    } else if (on && SA[i] > nn && SA[i + 1] > nn) {
      cur_lcp = min(cur_lcp, LCP[i+1]);
      if (cur_lcp == max_lcp) {
        start_ind = min(start_ind, SA[i]);
      }
    } else {
      on = false;
    }
  }

   string ans = "" ;
   for( ll i = start_ind ; i < start_ind + max_lcp ; i++) ans+=s[i] ;
   if(!ans.empty()) cout << ans << endl ;
   cout << ans.size() << endl ;
  

}
