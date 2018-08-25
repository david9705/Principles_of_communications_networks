#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<cmath>
#define LAMBDA 0.5
#define TIME 0.5
using namespace std;

int main()
{
	srand(time(NULL));
	double poiss;
	poiss=pow(LAMBDA*TIME,1)*exp((-1)*LAMBDA*TIME);
	int sample;
	cout<<"Enter the samples: ";
	cin>>sample;
	int count[30],total=0,a=0;
	for(int i=0;i<30;i++)	count[i]=0;
	for(int i=0;i<sample;i++)
	{
		a++;
		double t=(double)rand()/(RAND_MAX+1.0);
		if(t<poiss)
		{
			if(a<30)	count[a]++;
			total++;
			a=0;
		}		
	}
	for(int i=0;i<30;i++)
	{
		cout<<(double)i*0.5<<"      "<< (double)(count[i])/total<<endl;
	}
	system("pause");
	return 0;
} 
