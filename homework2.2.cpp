//此代码仅考虑没有向下请求的情况 
#include<stdio.h>
void sort(int c[3][5])//此函数用于将请求以时间顺序排序，若时间相同按楼层由高到低排序。 
{
	int i,j,c0,c1,c2;
	for(i=0;i<4;i++)
	{
		for(j=i+1;j<5;j++)
		{
			if(c[i][0]>c[j][0])
			{	
				c0=c[j][0];
				c1=c[j][1];
				c2=c[j][2];
				c[j][0]=c[i][0];
				c[j][1]=c[i][1];
				c[j][2]=c[i][2];
				c[i][0]=c0;
				c[i][1]=c1;
				c[i][2]=c2; 
			}
			else if(c[i][0]==c[j][0]&&c[i][1]>c[j][1])
			{
				c0=c[j][0];
				c1=c[j][1];
				c2=c[j][2];
				c[j][0]=c[i][0];
				c[j][1]=c[i][1];
				c[j][2]=c[i][2];
				c[i][0]=c0;
				c[i][1]=c1;
				c[i][2]=c2;
			} 
		}
	}
}
int main()
{
	int t[5]={0},a[3][5],sum1=0,sum2=0,sum,t1,t2,floor=1,i,j,T=0;//t[]用于记录等待时间（不包含电梯运行时间） 
	int n=0,m=0,k=0;//n为电梯内人数，m为已下电梯人数,k为被搁置请求的人数。
	int b[3][5];//b[][]用于暂存被搁置的请求。 
	for(i=0;i<5;i++)
	{
		scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);//输入五组请求。 
	}
	for(i=0;i<5;i++)
	{
		sum1=sum1+10-a[i][1]+1;//运行时间。 
	}
	sort(a);//将各请求按时间顺序排序。
	for(i=0;;)
	{
		if(T==a[i][0])//电梯在T时刻收到请求，根据请求情况讨论。 
		{
			if(floor==a[i][1])
			{
				if(T==a[i+1][0]&&floor==a[i+1][1])//若电梯在同一时刻，同一楼层还有请求，则暂不运行。由于题目设定，时间不加一。 
				{
					n++;//电梯内人数加一.
					printf("%d时,停靠在%d楼\n",T,floor);
					i++;//完成一请求，继续下一请求。 
				}
				else if(T!=a[i+1][0])
				{
					printf("%d时,停靠在%d楼\n",T,floor);
					T++;//电梯在请求楼层停靠。 
					for(j=0;j<=i;j++)
					{
						t[j]++;//电梯内的人等候。 
					} 
					n++;//电梯内人数加一。 
					floor++;
					i++;//完成一请求，继续下一请求。 
				}
				else
				{
					printf("%d时,停靠在%d楼\n",T,floor); 
					for(j=0;j<=i;j++)
					{
						t[j]++;//电梯内的人等候。 
					} 
					n++;//电梯内人数加一。
					for(j=i+1;j<5;j++) 
					{
						if(a[j][0]==T)
						{
							a[j][0]++;//如果此时刻还有请求，请求延续到下一时刻。 
						}
					}
					T++;//电梯在请求楼层停靠。
					floor++;
					i++;//完成一请求，继续下一请求。
				}
			}
			else if(floor<a[i][1])
			{
				t[i]++;
				T++;
				a[i][0]++;
				floor++;//电梯未到达请求楼层，请求的人等待,请求延续到下一时刻。 
			}
			else//电梯超过请求楼层，考虑是否返回。 
			{
				 t1=(n+1)*(floor-a[i][1])+n*(floor-a[i][1]+1);//电梯返回等待时间总和  
				 t2=(k+1)*(10-floor)*2+(k+1)+1;//电梯跳过请求，电梯外的人等待的时间。 
				 if(t1<t2)
				 {
				 	for(j=0;j<=i;j++)
				 	{
				 		t[j]=t[j]+2;//所有人等待。 
					}
					T++;
					a[i][0]++;
					floor--;//电梯回到下一楼层，请求持续到下一时刻。 
				 }
				 else
				 {
				 	T++;
					floor++;
					b[k][1]=a[i][1];
					b[k][2]=a[i][2];//电梯跳过请求,请求的人状态变为等候。
					i++;//电梯继续下一请求。 
					k++;//等待人数加一。 
				 } 
			}
		}
		else//电梯在T时刻未接收到请求，继续运行。 
		{
			T++;
			floor++; 
		} 
		if(floor==10&&(m+n)==5)
		{
			T++; 
			break;//所有人到达目的地，电梯停靠，停止运行。 
		}
		else if(floor==10)
		{
			T++;
			m=m+n;
			n=0;//电梯到达10楼，乘客下电梯。
		    for(j=0;j<5;j++)
			{
				sum2=sum2+t[j];//累计本轮等待时间。
				t[j]=0;//重置等待时间。 
			}
			if(k>0)
			{
				i=0;
				for(j=0;;j++)
				{
					sort(b);
				    floor=b[0][1];
					T=T+10-b[0][1];//电梯回到最低层。
					a[j][0]=T;//请求持续到T时刻。 
					a[j][1]=b[j][1];
					a[j][2]=b[j][2];//将被搁置的请求重新放入待执行列表。
					t[j]=T-b[j][0];//等待时间为到达十楼时间减发出请求时间加时间。
					if(j==k)
					{
					 k=0;break;	
					}
				}
			}
		}
	}
	sum=sum1+sum2; 
	printf("%d",sum);
	return 0;
}
