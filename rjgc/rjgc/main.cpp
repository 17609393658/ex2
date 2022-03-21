#include <iostream>

#include <queue>
#include <algorithm>
#include<fstream>
#include<iostream>


using namespace std;

#define MAXN 50

//�����ʾ
int n=3,W=30;
vector<int> w;//={0,16,15,15};		//�������±�0����
vector<int> v;//={0,45,25,25};  	//��ֵ���±�0����
//�������ʾ
int maxv=-9999;				//�������ֵ,��ʼΪ��Сֵ
int bestx[MAXN];			//������Ž�,ȫ�ֱ���
int total=1;				//��ռ��н�����ۼ�,ȫ�ֱ���


/*  ����
 *  ->��ʼ�����ڵ�
 *  ->������ڵ��Ͻ缰����
 *  ->ѭ���������У�����Ϊ�ǿգ���һ���ڵ�,
       �������ӽڵ��֦��������������Ӽ����Ͻ缰���ӣ�
       �����Һ��ӽڵ��Ͻ磬�����Ͻ��������Һ��ӽ��ӣ�
	   ������������ȥ������Ҫ������ӣ������Ͻ�������ȥ������Ҫ����Һ��ӣ�
 *
*/
void bfs();
//  ����----����Ҷ�ӽڵ��ֱ�ӽ��ӣ���Ҷ�ӽڵ����ж��Ƿ���Ž⣬�ǵĻ���������Ž�


// # ���ݷ�
//  ʹ��n,W,w[],v[],maxv,bestv[]
//  main�������ã�������ʼ��rw��op���Լ�dfs_back�����
void bfs_back_main();

void dfs_back(int i,int tw,int tv,int rw,int op[]);

struct NodeType_Knap
{
	double w;
	double v;
	double p;					//p=v/w
	bool operator<(const NodeType_Knap &s) const
	{
		return p>s.p;			//��p�ݼ�����
	}
};
vector<NodeType_Knap> A;		        //  ������������ݺ�����������
double V = 0;					//  ��ֵ��֮ǰ��int�ͣ�������Ϊdouble
double x[MAXN];					//  ���Ž�double���ͣ�����ѡ�񲿷֣���һ���ı���
/*
 * ��λ�����ļ�ֵ->�����Զ���ĸ�ʽ����->���� Knap
*/
void knap_m();
/*
 * �������̰��ѭ��ѡ�����ʣ��������������ɵ�ǰ�ģ���Ž�ȥ�����ܵĻ�����ѭ����ѡ�񲿷ַ���
*/
void Knap();
// !# ̰�ķ�

// # 쳲���������
int countf = 1;
int Fib(int n);
int dp_fib[MAXN];				//����Ԫ�س�ʼ��Ϊ0
int Fib1(int n);
// !# 쳲���������


int dp[MAXN][MAXN];

void dp_Knap();
/*
 * ��̬�滮�����Ѿ������ϣ������Ƴ����Ž�
   ����״̬ת�Ʒ����е��������ж�ÿ����Ʒ�Ƿ�ѡ��
*/
void buildx();
// !# ��̬�滮��

int main()
{
	//  �����ʽ
	/*
		3      n����Ʒ����Ϊ3
		16 45  ��һ����Ʒ�������ͼ�ֵ
		15 25  �ڶ�����Ʒ�������ͼ�ֵ
		15 25  ��������Ʒ�������ͼ�ֵ
		30	   ��������W
	*/
	using namespace std;

	fstream f;
	//�ļ���ȡ����ԭ����ios::out�ĳ�ios::in
	f.open("data.txt",ios::in);
	string s;
	//һֱ�����ļ�ĩβ
	while(f>>s)
	cout<<s<<endl; //��ʾ��ȡ����
	f.close();


	//cin >> n;
	int m,l;
	//  �±�0���ã����0
	w.push_back(0);
	v.push_back(0);
	int j;
	for (j = 1; j <= n;j++)
	{
		cin >> m >> l;
		w.push_back(m);
		v.push_back(l);
	}
	cin >> W;


	dp_Knap();
	buildx();
	// !# ��̬�滮��

	cout << "���Ž⣺";
	for (int i = 1;i <= n;i++)
	{
		if (V > 0)
		{// ̰�ķ�   �������double����
			cout << x[i] << " ";
		}else
		{//  ���ݷ��������int��
			cout << bestx[i] << " ";
		}

	}
	if (V > 0)
	{// ̰�ķ�   �������double����
		cout << endl << "����ֵΪ��" << V << endl;
	}else
	{//  ���ݷ��������int��
		cout << endl << "����ֵΪ��" << maxv << endl;
	}

	return 0;
}
//

//  ���ݷ�
void bfs_back_main()
{
	int *op  = new int[n];
	for (int j = 0;j < n;j++)
	{//  ��ʼ��Ϊȫ0
		op[j] = 0;
	}
	//  ������Ʒ��������
	int rw = 0;
	for (int j = 0;j < n;j++)
	{
		rw += w[j];
	}
	dfs_back(1,0,0,rw,op);
}
//���0/1��������
void dfs_back(int i,int tw,int tv,int rw,int op[])
{  //��ʼ����ʱrwΪ������Ʒ������
	int j;
	if (i>n)				        //�ҵ�һ��Ҷ�ӽ��
	{
		if (tw==W && tv>maxv) 		        //�ҵ�һ�����������ĸ��Ž�,����
		{
			maxv=tv;
			for (j=1;j<=n;j++)		//�������Ž�
				bestx[j]=op[j];
		}
	}else
	{				                //��δ����������Ʒ
		if (tw+w[i]<=W)			        //���ӽ���֦
		{
			op[i]=1;			//ѡȡ��i����Ʒ
			dfs_back(i+1,tw+w[i],tv+v[i],rw-w[i],op);
		}
		op[i]=0;				//��ѡȡ��i����Ʒ,����
		if (tw+rw>W)			        //�Һ��ӽ���֦
			dfs_back(i+1,tw,tv,rw-w[i],op);
	}
}
//
//  ̰�ķ�
void knap_m()
{

	for (int i=0;i<=n;i++)
	{
		NodeType_Knap k;
		k.w = w[i];
		k.v = v[i];
		A.push_back(k);
	}

	for (int i=1;i<=n;i++)		//��v/w
		A[i].p=A[i].v/A[i].w;

	sort(++A.begin(),A.end());			//A[1..n]����

	Knap();

}
//  ��ⱳ�����Ⲣ�����ܼ�ֵ
void Knap()
{
	V=0;						//V��ʼ��Ϊ0
	double weight=W;				//��������װ�����������

	int i=1;
	while (A[i].w < weight)			        //��Ʒi�ܹ�ȫ��װ��ʱѭ��
	{
		x[i]=1;					//װ����Ʒi
		weight -= A[i].w;			//���ٱ�������װ�����������
		V += A[i].v;				//�ۼ��ܼ�ֵ
		i++;					//����ѭ��
	}
	if (weight > 0)					//��������������0
	{
		x[i] = weight / A[i].w;		        //����Ʒi��һ����װ��
		V += x[i] * A[i].v;			//�ۼ��ܼ�ֵ
	}

}
//
//  쳲���������
int Fib(int n)
{
	printf("(%d)���Fib(%d)\n",countf++,n);
	if (n==1 || n==2)
	{
		printf("   �����Fib(%d)=%d\n",n,1);
		return 1;
	}
	else
	{
		int x = Fib(n-1);
		int y = Fib(n-2);
		printf("   �����Fib(%d)=Fib(%d)+Fib(%d)=%d\n",
		n,n-1,n-2,x+y);
		return x+y;
	}

}
//  ��̬�滮���쳲���������
int Fib1(int n)			//�㷨1
{
	dp_fib[1]=dp_fib[2]=1;
	printf("(%d)�����Fib(1)=1\n",countf++);
	printf("(%d)�����Fib(2)=1\n",countf++);
	for (int i=3;i<=n;i++)
	{
		dp_fib[i]=dp_fib[i-1]+dp_fib[i-2];
		printf("(%d)�����Fib(%d)=%d\n",countf++,i,dp_fib[i]);
	}
	return dp_fib[n];
}

//
//  ��̬�滮��
void dp_Knap()
{
	int i,r;
	for(i = 0;i <= n;i++)		//�ñ߽�����dp[i][0]=0
		dp[i][0] = 0;
	for (r = 0;r <= W;r++)		//�ñ߽�����dp[0][r]=0
		dp[0][r] = 0;
	for (i = 1;i <= n;i++)
	{
		for (r = 1;r <= W;r++)
			if (r < w[i])
				dp[i][r] = dp[i-1][r];
			else
				dp[i][r] = max(dp[i-1][r],dp[i-1][r-w[i]]+v[i]);
	}

}
void buildx()
{
	int i=n,r=W;
	maxv=0;
	while (i>=0)				//�ж�ÿ����Ʒ
	{
		if (dp[i][r] != dp[i-1][r])
		{
			bestx[i] = 1;		//ѡȡ��Ʒi
			maxv += v[i];		//�ۼ��ܼ�ֵ
			r = r - w[i];
		}
		else
			bestx[i]=0;		//��ѡȡ��Ʒi
		i--;
	}

}
