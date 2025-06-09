#include<bits/stdc++.h>
using namespace std;  

class A  
{
	private : 
		int x ; 
	public : 
		A()
		{
			cout<<"A::A()"<<endl;
			x = 1 ; 
		}
		A(int val)
		{
			cout<<"A::A(int)"<<endl;
			x = val;  
		}
		void printX()
		{
			cout<<x<<endl; 	
		}
		~A()
		{
			cout<<"~A"<<endl;
		}
}; 
class B : public  A 
{
	private : 
		int y ;  
 	public :
 		B()
 		{
 			y = 2 ; 
 			cout<<"B::B()"<<endl;
 		} 
 		B(int val):A(val)
 		{
 			y = 7 ; 
 			cout<<"B::B(int)"<<endl;
 		}
		void printY()
		{
			cout<<y<<endl;
		}
		~B()
		{
			cout<<"~B"<<endl;
		}
}; 
class C : public B
{	
	private : 
		int z ; 
	public :
		C()
		{
			cout<<"C::C()"<<endl;
			z = 3 ; 
		} 
		C(int val):B(val)
		{
			cout<<"C::C(int)"<<endl;
			z = val;
		} 
		void printZ()
		{
			cout<<z<<endl;
		}
		~C()
		{
			cout<<"~C"<<endl;
		}
}; 
int main()
{	
	C x(4); // Triggers C(int), B(int), and A(int)


}