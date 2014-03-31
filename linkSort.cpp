#include <iostream>

struct Node{
  int data;
  Node *next;
};
typedef Node *List;


List merge(List l1, List l2){
  if(!l1)
    return l2;
  else if (!l2)
    return l1;


  //both no null
  List p = NULL;
  if(l1->data < l2->data){
    p = l1;
    p->next = merge(p->next, l2);
  }
  else {
    p = l2;
    p->next = merge(l1, p->next);
  }

  return p;
}

void mergeSortList(List &l) {// sort n  length list
  if (!l || ! l->next)//0 or 1
    return ;
   
  List l1, l2;
  List slow, fast;
  l1 = l; //first segment
  slow = l;
  fast = l->next;
  while(fast){
    fast = fast->next;
    if(fast){
      fast = fast->next;
      slow = slow->next;
    }
  }
  l2 = slow->next;
  slow->next = NULL;
  
  
  mergeSortList(l1);
  mergeSortList(l2);
  l = merge(l1, l2);
}
using namespace std;
void pl(List l){
  while(l ){
    cout << l->data <<" ";
    l=l->next;
  }
  cout << endl;
}

int main(void){
  int d, i = 0;
  List head,cur;
  cur = head = new Node;
  cur->next = NULL;
  while(cin >> d){
    cur->next = new Node;
    cur= cur->next;
    cur->next = NULL;
    cur->data = d;
    ++i;
  }
  
  //input data
  pl(head->next);
  
  //sort
  mergeSortList(head->next);
  pl(head->next);
  return 0;
}
  
  
