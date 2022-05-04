// Project2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include<string>
using namespace std;
struct edge{
    string start;
    string change;
    string end;
};
struct chan {
    string Itab;
    string jihe[100];
};
string NODE;    //状态集合
string Change;  //输入字符集合
int N;          //NFA的边数


void sort(string& a)
{
    int i, j;
    char b;
    for(j=0;j<a.length();j++)
        for (i = 0; i < a.length(); i++) {
            if (NODE.find(a[i])> NODE.find(a[i + 1])) {
                b = a[i];
                a[i] = a[i + 1];
                a[i + 1] = b;
            }
        }
}
void eclouse(char c, string& newState, edge b[])
{
    int k;
    for (k = 0; k < N; k++)
    {
        if (c == b[k].start[0])
        {
            if (b[k].change == "*")
            {
                if (newState.find(b[k].end) > newState.length())
                    newState += b[k].end;
                eclouse(b[k].end[0], newState, b);
            }
        }
    }
}
void move(chan& newState, int m, edge b[])
{
    int i, j, k, l;
    k = newState.Itab.length();
    l = newState.jihe[m].length();
    for (i = 0; i < k; i++)
        for (j = 0; j < N; j++)
            if ((Change[m] == b[j].change[0]) && (newState.Itab[i] == b[j].start[0]))
                if (newState.jihe[m].find(b[j].end[0]) > newState.jihe[m].length())
                    newState.jihe[m] += b[j].end[0];
    for (i = 0; i < l; i++)
        for (j = 0; j < N; j++)
            if ((Change[m] == b[j].change[0]) && (newState.jihe[m][i] == b[j].start[0]))
                if (newState.jihe[m].find(b[j].end[0]) > newState.jihe[m].length())
                    newState.jihe[m] += b[j].end[0];
}
void output(int len, int h, chan* t)
{
    int i, j, m;
    cout << "\t";
    for (i = 0; i < len; i++)
        cout << Change[i] << "\t";
    cout<< "\n-----------------------" << endl;
    for (i = 0; i < h; i++)
    {
        cout <<' ' << t[i].Itab;
        for (j = 0; j < len; j++) 
        {
            cout << " \t";
            cout << t[i].jihe[j];
        }
        cout << endl;
    }
}
void main()
{
    edge* b = new edge[100];
    int i, j, k, m, n, h, x, y, len;
    bool flag;
    string jihe[100], endNode, newEndNode, sta;
    cout << "请输入NFA各条边的信息（起点 输入【空为*】 终点，最后以#结束）:" << endl;
    for (i = 0; i < 100; i++)
    {
        cin >> b[i].start;
        if (b[i].start == "#")
            break;
        cin >> b[i].change >> b[i].end;
    }
    N = i;

    for (j = 0; j < N; j++)
        cout << b[j].start << b[j].change << b[j].end << endl;
    for (i = 0; i < N; i++)
    {
        if (NODE.find(b[i].start) > NODE.length())
        {
            NODE += b[i].start;
        }
        if (NODE.find(b[i].end) > NODE.length())
        {
            NODE += b[i].end;
        }
        if ((Change.find(b[i].change) > Change.length()) && (b[i].change!="*"))
            Change += b[i].change;
    }
    len = Change.length();
    cout << "节点中属于终态是：" << endl;
    cin >> endNode;
    for (i = 0; i < endNode.length(); i++) 
    {
        if (NODE.find(endNode[i]) > NODE.length())
        {
            cout << "所属终态不在集合中，错误！" << endl;
            return;
        }
    }
    chan* t = new chan[100];
    t[0].Itab = b[0].start;
    h = 1;
    eclouse(b[0].start[0], t[0].Itab, b);
    for (i = 0; i < h; i++)
    {
        for (k = 0; k < len; k++) 
        {
            move(t[i], k, b);
            for (j = 0; j < t[i].jihe[k].length(); j++)
                eclouse(t[i].jihe[k][j], t[i].jihe[k], b);
        }
        for (j = 0; j < len; j++)
        {
            sort(t[i].jihe[j]);
            for (k = 0; k < h; k++) 
            {
                flag = operator==(t[k].Itab, t[i].jihe[j]);
                if (flag)
                    break;
            }
            if (!flag && t[i].jihe[j].length())
                t[h++].Itab = t[i].jihe[j];
        }
    }
    cout << endl << "状态转换矩阵如下:" << endl;
    output(len, h, t);

    string* d = new string[h];
    NODE.erase();
    cout << endl << "重命名：" << endl;
    for (i = 0; i < h; i++)
    {
        sta = t[i].Itab;
        t[i].Itab.erase();
        t[i].Itab = 'A' + i;
        NODE += t[i].Itab;
        cout << "{" << sta << "}=" << t[i].Itab << endl;
        for (j = 0; j < endNode.length(); j++)
        {
            if(sta.find(endNode[j])<sta.length()) //如果在新生成的结点中发现终态
                newEndNode += t[i].Itab;
        }
        for (k = 0; k < h; k++)
            for (m = 0; m < len; m++)
                if(sta == t[k].jihe[m])
                    t[k].jihe[m] = t[i].Itab;
    }
    endNode = newEndNode;
    cout << "\nDFA如下：" << endl;
    output(len, h, t);

    cout << "其最终态为：" << endNode << endl;
}