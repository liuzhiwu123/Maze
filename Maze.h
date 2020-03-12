#include<iostream>
#include<stack>
using namespace std;
                                          //普通迷宫，深度遍历，用栈

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
public://maze网格里都是对象
	maze(int a=5,int** ar=nullptr)
	{
		squar = new Node*[a];
		for (int i = 0; i < a; i++)
		{
			squar[i] = new Node[a];
		}
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a-1; j++)//设置right
			{
				if (ar[i][j + 1] == 0)
					squar[i][j].setright(0);
			}
		}
		for (int i = 0; i < a; i++)//设置左边
		{
			for (int j = 1; j < a; j++)
			{
				if (ar[i][j-1] == 0)
				{
					squar[i][j].setleft(0);
				}
			}
		}
		for (int i = 1; i < a; i++)//设置up
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i-1][j] == 0)
				{
					squar[i][j].setup(0);
				}
			}
		}
		for (int i = 0; i < a-1; i++)//设置down
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
	//能走就入栈并把相向方向置为1，否则退一步就是出栈，
	//（入栈后观察设置后的四个方向，若全是1就出栈，出栈后再取栈顶元素观察四周，向0的方向走，若有一个0就向0的方向走）
	//设置方向为了不走重复路，防止左走到右边，回来又从左边到右边的死循环
	void start(int a)//路径是右，下，左，上   
	{
		int i = 0, j = 0;
		stk.push(squar[i][j]);
		while (stk.top().X()!=a-1 || stk.top().Y()!=a-1)
		{
			i = stk.top().X();
			j = stk.top().Y();
			if (stk.top().Right() == 0)//向右边走
			{
				stk.top().setright(1);
				stk.push(squar[i][j + 1]);
				stk.top().setleft(1);
				squar[i][j].setright(1);  //不用设置maze上的方向限制，因为每次都是看栈里的元素的方向限制。当回到某点时方向限制已经改变了
				squar[i][j + 1].setleft(1);
				/*
				解决死循环就需要设置maze上的方向限制，（相当与做了记号，当下次来到同一点时，会把为修改的maze里的node入栈
	            栈顶元素又会按照右下左上走，导致死循环。但是设置了maze里后，当遇到同一个点入栈后，
				取栈顶（也就是同一点）后会发现上次走过的方向被限制，于是只能出栈）
			    直到栈顶元素有一个方向能走为止
				*/
			}
			else if(stk.top().Down()==0)//向下边走
			{
				stk.top().setdown(1);
				stk.push(squar[i+1][j]);
				stk.top().setup(1);
				squar[i][j].setdown(1);
				squar[i+1][j].setup(1);
			}
			else if (stk.top().Left() == 0)//向左边走
			{
				stk.top().setleft(1);
				stk.push(squar[i][j-1]);
				stk.top().setright(1);
				squar[i][j].setleft(1);
				squar[i][j-1].setright(1);
			}
			else if (stk.top().Up() == 0)//向上走
			{
				stk.top().setup(1);
				stk.push(squar[i-1][j]);
				stk.top().setdown(1);
			    squar[i][j].setup(1);
				squar[i - 1][j].setdown(1);
			}
			else  //四周都走不了
			{
				stk.pop();
			}
			cout << "error";
		}
		cout << stk.size() << endl;
		setstk();//因为栈里的和maze里的不是同一个，栈里的是maze构造的，所以要设置下maze里的
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
