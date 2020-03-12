#include<iostream>
#include<queue>
using namespace std;
//��ȱ�����Ѱ���Թ������·��
//��Ҫ����һ������ļ�¼·�������飬�Ա��˷·������Ϊһֱ�ڶ�ͷ���ӣ��������߹���·����Ϣ�᲻�϶�ʧ
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
			for (int j = 0; j < a - 1; j++)//����right
			{
				if (ar[i][j + 1] == 0)
					squar[i][j].setright(0);
			}
		}
		for (int i = 0; i < a; i++)//�������
		{
			for (int j = 1; j < a; j++)
			{
				if (ar[i][j - 1] == 0)
				{
					squar[i][j].setleft(0);
				}
			}
		}
		for (int i = 1; i < a; i++)//����up
		{
			for (int j = 0; j < a; j++)
			{
				if (ar[i - 1][j] == 0)
				{
					squar[i][j].setup(0);
				}
			}
		}
		for (int i = 0; i < a - 1; i++)//����down
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
	void start(int a)//��Ȼ����������
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
					squar[x][y + 1].setleft(1);//��ʱ 
					int flag = 9;
					flag=checkque(squar[x][y + 1], 1);//����Ƿ�Ҫ��ӵĵ��Ѿ��ڶ���ڵĻ����÷��򣬲��ڵ�ûִ����䡣
					que.push(squar[x][y + 1]);
					int val = (x * a) + y + 1;
					road[val] = squar[x][y];//�ѵ�ǰ�ڵ�ŵ���һ���ڵ�һλ����λ���ϣ��Ա��ڻ�˷��ȡ������һ���ڵ����߽��м���ͻ���һά�����Ӧ����ǰ�ڵ㣬ȡ������ǰ�ڵ��������м���ͻ��Ӧ����һ���ڵ���һά�����е�λ��
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
					flag=checkque(squar[x+1][y], 2);//����Ƿ�Ҫ��ӵĵ��Ѿ��ڶ���ڵĻ����÷��򣬲��ڵ�ûִ����䡣
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
					flag=checkque(squar[x][y - 1], 3);//����Ƿ�Ҫ��ӵĵ��Ѿ��ڶ���ڵĻ����÷��򣬲��ڵ�ûִ����䡣
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
					flag=checkque(squar[x-1][y], 4);//����Ƿ�Ҫ��ӵĵ��Ѿ��ڶ���ڵĻ����÷��򣬲��ڵ�ûִ����䡣
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
		//x*a+y�±��´�ŵ�����һ���ڵ㣬��Ϊ�ǰ�·���ϵ���һ���ڵ��ŵ���һ���ڵ������Ӧ���±���  �磺��3.4������һ�ڵ��ǣ�3��5�������ǣ�4��5��
		//�Ͱѣ�3��4���ŵ�road[3*a+4]�£���3��5���ŵ�road[4*a+5]�£���˷��ȡ��road[4*a+5]��ľ��ҵ��ˣ�3��5����ȡ��road[3*a+4]���ҵ��ˣ�3��4��
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
	bool checkque(Node &node,int dir)//����Ƿ����Ѿ��ڶ���
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
	bool check( Node &node,int a)//����Ƿ��ǳ���
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
	//road���÷����ѵ�ǰ�ڵ�ŵ���һ���ڵ�row*col����Ӧ��һά�����±��£����������ڶ����ڵ�ͷ������˶�Ӧһά�±��£����һ��Ԫ�أ����ڣ�
	//��Ĭ���������¼��������˷ʱ������߼��㵽һλ�����±��£����ҵ��˵����ڶ����ڵ㣬�����ڶ����ڵ��������Ͷ�Ӧ���˵����������ڵ�����һλ������±�
};

