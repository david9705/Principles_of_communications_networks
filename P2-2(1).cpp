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
	double block=0.0,a=0.0,s=0.0,rand_a,rand_s;
	vector<cell> cc;
	cc.resize(12);
	cc[0].a[0]=&cc[1];
	cc[0].a[1]=&cc[2];
	cc[0].a[2]=&cc[7];
	cc[1].a[0]=&cc[0];
	cc[1].a[1]=&cc[2];
	cc[1].a[2]=&cc[9];
	cc[2].a[0]=&cc[0];
	cc[2].a[1]=&cc[1];
	cc[2].a[2]=&cc[3];
	cc[2].a[3]=&cc[4];
	cc[2].a[4]=&cc[7];
	cc[2].a[5]=&cc[9];
	cc[3].a[0]=&cc[2];
	cc[3].a[1]=&cc[4];
	cc[3].a[2]=&cc[5];
	cc[3].a[3]=&cc[7];
	cc[3].a[4]=&cc[8];
	cc[4].a[0]=&cc[2];
	cc[4].a[1]=&cc[3];
	cc[4].a[2]=&cc[5];
	cc[4].a[3]=&cc[9];
	cc[4].a[4]=&cc[11];
	cc[5].a[0]=&cc[3];
	cc[5].a[1]=&cc[4];
	cc[6].a[0]=&cc[7];
	cc[6].a[1]=&cc[8];
	cc[7].a[0]=&cc[0];
	cc[7].a[1]=&cc[2];
	cc[7].a[2]=&cc[3];
	cc[7].a[3]=&cc[6];
	cc[7].a[4]=&cc[8];
	cc[8].a[0]=&cc[4];
	cc[8].a[1]=&cc[6];
	cc[8].a[2]=&cc[7];
	cc[9].a[0]=&cc[1];
	cc[9].a[1]=&cc[2];
	cc[9].a[2]=&cc[4];
	cc[9].a[3]=&cc[10];
	cc[9].a[4]=&cc[11];
	cc[10].a[0]=&cc[9];
	cc[10].a[1]=&cc[11];
	cc[11].a[0]=&cc[4];
	cc[11].a[1]=&cc[9];
	cc[11].a[2]=&cc[10];
	for(int i=0;i<12;i++)
	{
	    cc[i].num=i;
	}
	for(int i=0;i<12;i++)
	{
	    cc[i].cd=i%3;
	}
	for(int i=0;i<TIME;i++)
	{
		for(int j=0;j<12;j++)
		{
			a=((i%4)+1)*LAMBDA;
			s=((i%4)+1)*MU;
			rand_a=(double)rand()/(RAND_MAX+1.0);
			int k=0;
			if(rand_a>pow(EXP,(-1)*a))
			{
				total++;
				if((cc[j].all>cc[j].used)||(cc[j].find()==1))	cc[j].used++;
                else    block++;	
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
