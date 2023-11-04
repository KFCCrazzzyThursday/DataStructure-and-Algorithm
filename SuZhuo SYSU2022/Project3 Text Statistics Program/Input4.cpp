#include<iostream>
using namespace std;
struct test{
	int a,b;
	test(void):a(0),b(0){}
	test(int a_,int b_):a(a_),b(b_){}
};

int main(){
	int a,b;
	float c;
	const float d=0;
	scanf("%d%d%f",&a,&b,&c);
	cout<<a<<b<<c;
	
	test d(a,b);
}