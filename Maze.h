#include<iostream>
#include<stack>
using namespace std;
                                          //��ͨ�Թ�����ȱ�������ջ

class Node
{
public:
	Node( int u=1, int d=1, int l=1, int r=1, int a = 0, int b = 0,int da=0)
		:x(a), y(b), left(l), right(r), up(u), down(d) ,data(da)
	{}
	void setleft(int val) { left = val; }
    void setright(int val) { right = val; }
	void setup(int val) { up = val; }
	void setdown(int val) { down = val; }
	void setlocal(int a, int b, int da) { x = a; y = b; data = da; }
	void setdata(int val) { data = val; }
	int Right() { return right; }
	int Left() { return left; }
	int Up() { return up; }
	int Down() { return down; }
	int point() { return (x * 10) + y; }
	int X() { return x; }
	int Y() { return y; }
	void show() { cout << data << " "<<left<<" " << right << " "<<up <<" "<< down<<" " << endl; }
	void showrount() { cout << data << " "; }
private:
	int x, y,data;
	int left, right, up, down;
};
class maze
{
public://maze�����ﶼ�Ƕ���
	maze(int a=5,int** ar=nullptr)
	{
		squar = new Node*[a];
		for (int i = 0; i < a; i++)
		{
			squar[i] = new Node[a];
		}
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a-1; j++)//����right
			{
				if (ar[i][j + 1] == 0)
					squar[i][j].setright(0);
			}
		}
		for (int i = 0; i < a; i++)//�������
		{
			for (int j = 1; j < a; j++)
			{
				if (ar[i][j-1] == 0)
				{
					squar[i][j].setleft(0);
				}
			}
		}
		for (int i = 1; i < a; i++)//����up
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i-1][j] == 0)
				{
					squar[i][j].setup(0);
				}
			}
		}
		for (int i = 0; i < a-1; i++)//����down
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i+1][j] == 0)
				{
					squar[i][j].setdown(0);
				}
			}
		}
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a; j++)
			{
				squar[i][j].setlocal(i, j, ar[i][j]);
				//squar[i][j].show();
			}
		}
	}
	//���߾���ջ������������Ϊ1��������һ�����ǳ�ջ��
	//����ջ��۲����ú���ĸ�������ȫ��1�ͳ�ջ����ջ����ȡջ��Ԫ�ع۲����ܣ���0�ķ����ߣ�����һ��0����0�ķ����ߣ�
	//���÷���Ϊ�˲����ظ�·����ֹ���ߵ��ұߣ������ִ���ߵ��ұߵ���ѭ��
	void start(int a)//·�����ң��£�����   
	{
		int i = 0, j = 0;
		stk.push(squar[i][j]);
		while (stk.top().X()!=a-1 || stk.top().Y()!=a-1)
		{
			i = stk.top().X();
			j = stk.top().Y();
			if (stk.top().Right() == 0)//���ұ���
			{
				stk.top().setright(1);
				stk.push(squar[i][j + 1]);
				stk.top().setleft(1);
				squar[i][j].setright(1);  //��������maze�ϵķ������ƣ���Ϊÿ�ζ��ǿ�ջ���Ԫ�صķ������ơ����ص�ĳ��ʱ���������Ѿ��ı���
				squar[i][j + 1].setleft(1);
				/*
				�����ѭ������Ҫ����maze�ϵķ������ƣ����൱�����˼Ǻţ����´�����ͬһ��ʱ�����Ϊ�޸ĵ�maze���node��ջ
	            ջ��Ԫ���ֻᰴ�����������ߣ�������ѭ��������������maze��󣬵�����ͬһ������ջ��
				ȡջ����Ҳ����ͬһ�㣩��ᷢ���ϴ��߹��ķ������ƣ�����ֻ�ܳ�ջ��
			    ֱ��ջ��Ԫ����һ����������Ϊֹ
				*/
			}
			else if(stk.top().Down()==0)//���±���
			{
				stk.top().setdown(1);
				stk.push(squar[i+1][j]);
				stk.top().setup(1);
				squar[i][j].setdown(1);
				squar[i+1][j].setup(1);
			}
			else if (stk.top().Left() == 0)//�������
			{
				stk.top().setleft(1);
				stk.push(squar[i][j-1]);
				stk.top().setright(1);
				squar[i][j].setleft(1);
				squar[i][j-1].setright(1);
			}
			else if (stk.top().Up() == 0)//������
			{
				stk.top().setup(1);
				stk.push(squar[i-1][j]);
				stk.top().setdown(1);
			    squar[i][j].setup(1);
				squar[i - 1][j].setdown(1);
			}
			else  //���ܶ��߲���
			{
				stk.pop();
			}
			cout << "error";
		}
		cout << stk.size() << endl;
		setstk();//��Ϊջ��ĺ�maze��Ĳ���ͬһ����ջ�����maze����ģ�����Ҫ������maze���
		showroad(a);
	}
	void showroad(int a)
	{
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a; j++)
			{
				squar[i][j].showrount();
			}
			cout << endl;
		}
	}
	void setstk()
	{
		while (!stk.empty())
		{
			int x = stk.top().X();
			int y = stk.top().Y();
			squar[x][y].setdata(2);
			stk.pop();
		}
	}
private:
	Node** squar;
	stack<Node> stk;
};
