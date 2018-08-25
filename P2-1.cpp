#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <time.h>
#define LAMBDA 0.0167
#define EXP 2.718281828
#define TIME 6000
#define MU 0.0033
using namespace std;

class cell{
	public:
	int num,used,all,cd;	
	vector<int> receiver;
	vector<cell*> donater;
	cell(){
	    num=0;
        used=0;
    	all=5;   	
		a[0]=NULL;
        a[1]=NULL;
        a[2]=NULL;
        a[3]=NULL;
        a[4]=NULL;
        a[5]=NULL;
        cd=0;
		}
    ~cell(){};
    cell* a[6];
	int find();
	void give_back();
};

int cell::find()
{
	cell* rich;
	rich=a[0];
	int rich_s=rich->all-rich->used;
	for(int i=0;i<5;i++)
	{		
		if(a[i]!=0&&rich_s>(a[i]->all-a[i]->used))
		{
			rich=a[i];
			rich_s=rich->all-rich->used;
		}   
	}	
	if(rich_s>0)
	{			
		receiver.push_back(5*(rich->cd)+all-1);
		donater.push_back(rich);
		rich->all--;			
		return 1;
	}
	else return 0;
}

void cell::give_back()
{	
	receiver.pop_back();	
	donater[donater.size()-1]->all++;	
	if(donater[donater.size()-1]->used>donater[donater.size()-1]->all)	donater[donater.size()-1]->give_back();	
	donater.pop_back();
}


int main()
{
	srand(time(NULL));
	int total=0;
	double block=0.0,a,s,rand_a,rand_s;
	vector<cell> cc;
	cc.resize(12);
	for(int i=0;i<12;i++)
	{
	    cc[i].num =i;
	}
	for(int i=0;i<TIME;i++)
	{
		for(int j=0;j<12;j++)
		{
			rand_a=(double)rand()/(RAND_MAX+1.0);			
			a=((i%4)+1)*LAMBDA;
			s=((i%4)+1)*MU;
			int k=0;
			if(rand_a>pow(EXP,(-1)*a))
			{
				total++;
				if(cc[j].all>cc[j].used)	cc[j].used++;
                else if(cc[j].all<=cc[j].used)	block++;
			}
			while(k<cc[j].used)
			{
				rand_s=(double)rand()/(RAND_MAX+1.0);
				if(rand_s<(1-pow(EXP,(-1)*s)))
				{					
					if(cc[j].all<cc[j].used)	cc[j].give_back();
					cc[j].used--;	
				}	
				k++;				
			}		
		}
	}
	cout << "blocking probability: "<<block/total;
	system("PAUSE");
	return 0;
}
