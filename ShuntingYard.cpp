/****************************************
调度场算法，将中缀表达式转换为后缀表达式
数据结构
1.储存操作数的栈
2.储存结果的队列
可用操作符（同行优先级相同，不同行优先级递减）
*,/,右结合   2
+,-,右结合   1
(            0

算法描述
1.从左到右扫描字符串
2.若扫描到的标识符是
（1）操作数，入队列
（2）左括号，入栈
（3）右括号，将栈顶元素pop到队列，直到遇到左括号
（4）操作符，若操作符是右结合的，则将栈顶元素pop到队列直到当前操作符的优先级最大
         若操作符是左结合的，则将栈顶元素pop到队列直到当前操作符的优先级大于或等于栈顶元素优先级
3.重复1，2直到字符串为空
4.将栈里剩余的元素pop到队列,算法结束

实现不考虑右结合的运算
Last Modify 20140413
****************************************/


#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

enum TokenType {OPR,OPN,LP,RP,NONE};
struct Token{ //操作符或操作数结构
  TokenType type;
  float  val;
};


//获取下一个标识
//成功返回0
int getToken(const char * &s,Token &token){
  std::stringstream sst;
  //跳过空格
  while(*s == ' ' || *s == '\t')
    ++s;
  if(!s || *s == '\0')
    return 1;
  switch(*s){
  case '(':
    token.type = LP;
    token.val  = *s;
    ++s;
    return 0;
  case ')':
    token.type = RP;
    token.val  = *s;
    ++s;
    return 0;
  case '+':
  case '-':
  case '*':
  case '/':
    token.type = OPR;
    token.val =  *s;
    ++s;
    return 0;
  default:
    break;
  }
  if(isdigit(*s)){
    sst << s; 
    sst >> token.val;
    token.type = OPN;
  }else //error
 throw std::invalid_argument("unknow charactor " );
  while(isdigit(*s) && *s)
    ++s;
  if(*s == '.')
    while(isdigit(*++s) && *s)
      ;
  return 0;
}

//返回操作符的优先级
int piority(int i){
  switch(i){
  case '(':
    return 0;
  case '+': case '-':
    return 1;
  case '/': case '*':
    return 2;
  }
}
    
void revPolish(const char *s, std::queue<Token> &res)
{
  std::stack<Token> opr; //操作符
  Token cur,tmp;
  res = std::queue<Token>();
  while(!getToken(s,cur)){ //获取下一个标识符
    switch(cur.type){
    case OPN:
      res.push(cur);
      break;
    case LP:
      opr.push(cur);
      break;
    case RP: //右括号
      while(!opr.empty() && (tmp=opr.top(),tmp.type != LP) )
	opr.pop(),res.push(tmp);
      if(!opr.empty())
	opr.pop(); //左括号出栈
      break;
    case OPR:
      while(!opr.empty() && (tmp=opr.top(),piority(tmp.val) >= piority(cur.val)) )//右结合
	opr.pop(), res.push(tmp);
      opr.push(cur); //入栈
      break;
    default:
      break;
    }
  }
  
  //清楚剩余元素
  while(!opr.empty()){
    tmp = opr.top();
    res.push(tmp);
    opr.pop();
  }
}//revPolish
	
	
#ifdef MAIN

using namespace std;      
int main(){
  string s;
  Token t;
  float opn1, opn2;
  std::stack<float> res;
  std::queue<Token> rp; //结果
  getline(cin,s);
  try{
    revPolish(s.c_str(),rp);
    cout << "result size = " << rp.size() << endl;
    //计算结果
    while(!rp.empty()){
      t = rp.front();
      rp.pop();
      switch(t.type){
      case OPN:
	res.push(t.val);
	cout << t.val <<" " ;
	break;
      case OPR:
	opn2 = res.top();
	res.pop();
	opn1 = res.top();
	res.pop();
	switch((int)t.val){
	case '-':
	  res.push(opn1 - opn2);
	  cout <<"- ";
	  break;
	case '+':
	  res.push(opn1 + opn2);
	  cout <<"+ ";
	  break;
	case '*':
	  res.push(opn1 * opn2);
	  cout << "* ";
	  break;
	case '/':
	  res.push(opn1 / opn2);
	  cout << "/ ";
	  break;
	default:
	  break;
	}
	break;
      default:
	break;
      }//switch
    }//while
    cout << "\nresult = " << res.top() << endl;
  }
  catch (exception &e){
    cerr <<e.what();
  }	
  return 0;
}
#endif
  



