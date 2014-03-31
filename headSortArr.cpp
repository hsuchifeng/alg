#include <iostream>

using namespace std;

inline void swap( int &n1, int &n2){
  int temp = n1;
  n1 = n2;
  n2 = temp;
}

//a[0] to a[n-1] is a max piority heap
void upElement(int *a, int n){
  if(n<=0) //root
    return ;
  int parent = (n-1)/2;
  if(a[n] > a[parent]){
    swap( a[n], a[parent]);
    upElement(a,parent);
  }
}

//a[0] just added, a[1] to a[n] need a root
void downElement(int *a, int n){
  if(n<=0)//leaf
    return;
  int firstChild =1;
  int maxIndex = 0;
  if(a[maxIndex] < a[firstChild])
    maxIndex  = firstChild;
  if(firstChild +1 <= n && a[maxIndex] < a[firstChild + 1])
    maxIndex = firstChild + 1;
  
  if(!maxIndex)//keep
    return;
  else{
    swap(a[0],a[maxIndex]);
    downElement(a+maxIndex, n - maxIndex);
  }
}//down


//init
void initMaxHeap(int *a, int n){
  if(n <= 1)
    return ;
  int i;
  for(i = 1; i < n; ++i)
    upElement(a,i);
}

//heap sort
void heapSort(int *a, int n){
  initMaxHeap(a,n);
  int i;
  while(--n){
    swap(a[0],a[n]);
    downElement(a,n-1);
    //    initMaxHeap(a,n);
  }
}//heap sort end

void print(int *a, int n){
  for(int i = 0; i < n; ++i)
    cout <<a[i] << " ";
  cout<< endl;
}

int main(){
  int a[10001];
  int n = 0;
  while(cin >> a[n]) ++n;
  
  print(a,n);
  
  heapSort(a,n);
  print(a,n);
  return 0;
}//main

 
