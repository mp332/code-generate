#include<iostream>
//引入STL栈，用于转二进制时存放除余结果
#include <stack>
//引入STL字符串，用于存放二进制结果(数值类型可能溢出)
#include <string>
//用于数值转换字符串
#include <sstream>
//浮点小数部分乘2取整floor方法
#include <math.h>
using namespace std;
//十进制整数转换二进制字符串
string getReal(int num){
	if (num<0)
	{
		num=128+num;
	}
	stack<int> st;
	while (num>0)
	{
		st.push(num%2);	
		num=num>>1;
		if (num<2 && num!=0)
		{
			st.push(num);
			num=num>>1;
		}
	

	}
	int n=st.size();
	string sum="";
	stringstream s;
	for (int i=0;i<n;i++)
	{
		s<<st.top();
		sum+=s.str();
		s.str("");
		st.pop();
		
	}
	return sum;
	
}
//十进制浮点转换IE754二进制
string getFloat(double num){
	string result;
	if (num>0)
	{
		result="0 ";
	}else{
		result="1 ";
		num=-num;
	}
	int Real=(int)num;
	double decimals=num-Real;
	
	string real=getReal(Real);
	//Step Code
	string StepCode=getReal(real.size()+127-1)+" ";//IE754格式化尾数隐含位1，故需指数-1
	if (StepCode.size()<=8)
	{
		StepCode="0"+StepCode;
	}
	//组合符号和阶码
	result+=StepCode;
	//运算小数部分
	string dec="";
	double n=0;
	stringstream s2;
	for(int i=0;i<24-real.size();i++)
	{
		int k;
		n = decimals * 2;
		k =floor(n);
		s2<<k;
		dec += s2.str();
		s2.str("");
		decimals = n - k;
	}
	real+=dec;
	result+=real;
	return result;

}
int main(){
	
	double num=0;
	cout<<"请输入一个数: ";
	cin>>num;
	int Real=(int)(num>0?num:-num);
	if ((num>0?num:-num)-Real>0)
	{
		cout<<"输入为浮点数,以IE754表示为：";
		cout<<"10->2:"<<getFloat(num)<<endl;

	}else{
		
		cout<<"输入为整数，以补码（模128）形式表示：";
		cout<<"10->2: "<<(num>0?"":"s(1)")<<getReal(num)<<endl;
	}

	return 0;
}


