#include<iostream>
#include<queue>
using namespace std;
//广度遍历，寻找迷宫的最短路径
//需要定义一个额外的记录路径的数组，以便回朔路径，因为一直在队头出队，所以所走过的路径信息会不断丢失
class Node
{
public:
	Node(int u = 1, int d = 1, int l = 1, int r = 1, int a = 0, int b = 0, int da = 0)
		:x(a), y(b), left(l), right(r), up(u), down(d), data(da)
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
	void show() { cout << data << " " << left << " " << right << " " << up << " " << down << " " << endl; }
	void showrount() { cout << data << " "; }
private:
	int x, y, data;
	int left, right, up, down;
};
class maze
{
public:
	maze(int a = 5, int** ar = nullptr)
	{
		squar = new Node*[a];
		road = new Node[a*a];
		for (int i = 0; i < a; i++)
		{
			squar[i] = new Node[a];
		}
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a - 1; j++)//设置right
			{
				if (ar[i][j + 1] == 0)
					squar[i][j].setright(0);
			}
		}
		for (int i = 0; i < a; i++)//设置左边
		{
			for (int j = 1; j < a; j++)
			{
				if (ar[i][j - 1] == 0)
				{
					squar[i][j].setleft(0);
				}
			}
		}
		for (int i = 1; i < a; i++)//设置up
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i - 1][j] == 0)
				{
					squar[i][j].setup(0);
				}
			}
		}
		for (int i = 0; i < a - 1; i++)//设置down
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i + 1][j] == 0)
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
	void start(int a)//依然是右下左上
	{
			int x = 0, y = 0;
			que.push(squar[0][0]);
			while (!que.empty())
			{
				 x = que.front().X();
				 y = que.front().Y();
				if (que.front().Right() == 0)
				{
					squar[x][y].setright(1);
					squar[x][y + 1].setleft(1);//及时 
					int flag = 9;
					flag=checkque(squar[x][y + 1], 1);//检查是否将要入队的点已经在队里，在的话设置方向，不在当没执行这句。
					que.push(squar[x][y + 1]);
					int val = (x * a) + y + 1;
					road[val] = squar[x][y];//把当前节点放到下一个节点一位数组位置上，以便于回朔。取出来下一个节点的左边进行计算就会在一维数组对应到当前节点，取出来当前节点的坐标进行计算就会对应到上一个节点在一维数组中的位置
					if (check(squar[x][y + 1],a))
					{
						break;
					}
				}
				if (que.front().Down() == 0)
				{
					squar[x][y].setdown(1);
					squar[x + 1][y].setup(1);
					int flag = 9;
					flag=checkque(squar[x+1][y], 2);//检查是否将要入队的点已经在队里，在的话设置方向，不在当没执行这句。
					que.push(squar[x + 1][y]);
					int val = (x + 1) * a + y;
					road[val] = squar[x][y];
					if (check(squar[x + 1][y],a))
					{
						break;
					}
				}
				if (que.front().Left() == 0)
				{
					squar[x][y].setleft(1);
					squar[x][y-1].setright(1);
					int flag = 9;
					flag=checkque(squar[x][y - 1], 3);//检查是否将要入队的点已经在队里，在的话设置方向，不在当没执行这句。
					que.push(squar[x][y-1]);
					int val = x * a + y - 1;
					road[val] = squar[x][y];
					if (check(squar[x ][y-1],a))
					{
						break;
					}
				}
				if (que.front().Up() == 0)
				{
					squar[x][y].setup(1);
					squar[x-1][y].setdown(1);
					int flag = 9;
					flag=checkque(squar[x-1][y], 4);//检查是否将要入队的点已经在队里，在的话设置方向，不在当没执行这句。
					que.push(squar[x-1][y]);
					int val = (x - 1)*a + y;
					road[val] = squar[x][y];
					if (check(squar[x-1][y],a))
					{
						break;
					}
				}
				cout << "a";
				que.pop();
			}
			if (que.empty())
			{
				cout << "no road" << endl;
			}
			else
			{
				setroad(a);
				showroad(a);
			}
	}
	void setroad(int a)
	{
		int x = a - 1, y = a - 1;
		//x*a+y下标下存放的是上一个节点，因为是把路径上的上一个节点存放到下一个节点坐标对应的下标下  如：（3.4）的下一节点是（3，5），下是（4，5）
		//就把（3，4）放到road[3*a+4]下，（3，5）放到road[4*a+5]下，回朔是取出road[4*a+5]里的就找到了（3，5），取出road[3*a+4]就找到了（3，4）
		while (x != 0 || y != 0)
		{
			int val = x * a + y;
			squar[x][y].setdata(2);
			x = road[val].X();
			y = road[val].Y();
			cout << x << "," << y << "   ";
		}
		squar[x][y].setdata(2);
	}
	bool checkque(Node &node,int dir)//检查是否是已经在队里
	{
		if (que.size() == 1)
		{
			return 0;
		}
		Node tmp = que.front();
		Node stp = tmp;
		que.pop();
		que.push(tmp);
		tmp = que.front();
		int flag = 0;
		while (tmp.X() != stp.X() || tmp.Y() != stp.Y())
		{
			if (tmp.X() == node.X() && tmp.Y() == node.Y())
			{
				switch (dir)
				{
				case 1:tmp.setleft(1); break;
				case 2:tmp.setup(1); break;
				case 3:tmp.setright(1); break;
				case 4:tmp.setdown(1); break;
				}
				flag = 1;
			}
			que.pop();
			que.push(tmp);
			tmp = que.front();
		}
		return flag;
	}
	bool check( Node &node,int a)//检查是否是出口
	{
		if (node.X() == a - 1 && node.Y() == a - 1)
		{
			return true;
		}
		return false;
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
private:
	Node** squar;
	queue<Node> que;
	Node* road;
	//road的用法：把当前节点放到下一个节点row*col所对应的一维数组下标下，这样倒数第二个节点就放在在了对应一维下标下，最后一个元素（出口）
	//就默认用坐标记录，这样回朔时出口左边计算到一位数组下标下，就找到了倒数第二个节点，倒数第二个节点坐标计算就对应到了倒数第三个节点所在一位数组的下标
};

