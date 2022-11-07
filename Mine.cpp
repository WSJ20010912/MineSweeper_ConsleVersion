#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;
#define ROW 18
#define COL 18
#define MINENUM 40
#define TIME 10

void InitMap(char mp[ROW+2][COL+2],int a[ROW+2][COL+2]){
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			mp[i][j]='?';
		}
	}
	int cnt=0;
	bool vis[ROW+2][COL+2];
	memset(vis,0,sizeof(vis));
	while (cnt<MINENUM){
		int x=rand()%ROW+1;
		int y=rand()%COL+1;
		if (!vis[x][y]){
			cnt++;
			vis[x][y]=true;
			mp[x][y]='*';
		}
	}
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			a[i][j]=(mp[i][j]=='*');
		}
	}
}
void AnswerMap(char mp[ROW+2][COL+2],int a[ROW+2][COL+2],char answer[ROW+2][COL+2]){
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (mp[i][j]=='*'){
				answer[i][j]='*';
			}
			else{
				int num=a[i-1][j-1]+a[i-1][j]+a[i-1][j+1]+a[i][j-1]+a[i][j+1]+a[i+1][j-1]+a[i+1][j]+a[i+1][j+1];
				sprintf(&answer[i][j],"%d",num);
			}
		}
	}
}
void DFS(int x,int y,char cur[ROW+2][COL+2],char answer[ROW+2][COL+2],bool vis[ROW+2][COL+2]){
	if (cur[x][y]!='0'&&cur[x][y]!='.'){
		return;
	}
	if (x<=0||x>ROW||y<=0||y>COL||vis[x][y]){
		return;
	}
	vis[x][y]=1;
	cur[x][y]=answer[x][y];
	system("cls");
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			cout<<cur[i][j];
		}
		cout<<endl;
	}
	if (cur[x][y]=='0'){
		for (int i=-1;i<=1;i++){
			for (int j=-1;j<=1;j++){
				if (i!=0||j!=0){
					DFS(x+i,y+j,cur,answer,vis);
				}
			}
		}
	}
	Sleep(TIME);
}
bool Safe(char cur[ROW+2][COL+2],char answer[ROW+2][COL+2],bool vis[ROW+2][COL+2]){
	char mine[ROW+2][COL+2];
	for (int i=0;i<ROW+2;i++){
		for (int j=0;j<COL+2;j++){
			mine[i][j]='#';
		}
	}
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			mine[i][j]=cur[i][j];
		}
	}
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (mine[i][j]!='.'){
				int cnt=0;
				for (int x=-1;x<=1;x++){
					for (int y=-1;y<=1;y++){
						if (x!=0||y!=0){
							if (mine[i+x][j+y]=='.'||mine[i+x][j+y]=='-'){
								cnt++;
							}
						}
					}
				}
				if (cnt==mine[i][j]-'0'){
					for (int x=-1;x<=1;x++){
						for (int y=-1;y<=1;y++){
							vis[i+x][j+y]=1;
						}
					}
					for (int x=-1;x<=1;x++){
						for (int y=-1;y<=1;y++){
							if (vis[i+x][j+y]&&mine[i+x][j+y]=='.'){
								mine[i+x][j+y]='-';
							}
						}
					}
				}
			}
		}
	}
	queue<pair<int,int> > q,q1;
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (mine[i][j]!='.'&&mine[i][j]!='-'){
				int cnt=0;
				for (int x=-1;x<=1;x++){
					for (int y=-1;y<=1;y++){
						if (mine[i+x][j+y]=='-'){
							cnt++;
						}
					}
				}
				if (cnt==mine[i][j]-'0'){
					for (int x=-1;x<=1;x++){
						for (int y=-1;y<=1;y++){
							if (!vis[i+x][j+y]){
								q.push({i+x,j+y});
							}
						}
					}
				}
			}
		}
	}
	//system("pause");
	while (!q.empty()){
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		if (x<=0||y<=0){
			continue;
		}
		vis[x][y]=1;
		cur[x][y]=answer[x][y];
		system("cls");
		for (int i=1;i<=ROW;i++){
			for (int j=1;j<=COL;j++){
				cout<<cur[i][j];
			}
			cout<<endl;
		}
		Sleep(TIME);
		if (cur[x][y]=='0'){
			for (int i=-1;i<=1;i++){
				for (int j=-1;j<=1;j++){
					if (x!=0||y!=0){
						DFS(x+i,y+j,cur,answer,vis);
					}
				}
			}
		}
	}
	bool f=0;
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (mine[i][j]!='-'&&mine[i][j]!=cur[i][j]){
				f=1;
				break;
			}
		}
	}
	while (f){
		Safe(cur,answer,vis);
		break;
	}
}
int JudgeMap(char cur[ROW+2][COL+2],bool vis[ROW+2][COL+2]){
	int cc=0;
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (cur[i][j]!='.'){
				cc++;
				int cnt=0;
				for (int x=-1;x<=1;x++){
					for (int y=-1;y<=1;y++){
						if (cur[i+x][j+y]=='.'){
							cnt++;
						}
					}
				}
			}
		}
	}
	return cc;
}
bool ShowMap(char cur[ROW+2][COL+2],char answer[ROW+2][COL+2],bool vis[ROW+2][COL+2],bool flag,bool dfs,int cc){
	dfs=0;
	int x,y;
	cc=JudgeMap(cur,vis);
	while (true){
		x=rand()%ROW+1;
		y=rand()%COL+1;
		if (!vis[x][y]){
			vis[x][y]=1;
			cur[x][y]=answer[x][y];
			if (answer[x][y]=='*'){
//				if (cc<=10){
//					cur[x][y]='.';
//					continue;
//				}
				return false;
			}
			if (cur[x][y]=='0'){
				dfs=1;
			}
			break;
		}
	}
	if (dfs){
		for (int i=-1;i<=1;i++){
			for (int j=-1;j<=1;j++){
				if (i!=0||j!=0){
					DFS(x+i,y+j,cur,answer,vis);
				}
			}
		}
		Safe(cur,answer,vis);
	}
	return true;
}
void RunMap(char cur[ROW+2][COL+2],char answer[ROW+2][COL+2]){
	bool flag=true;
	bool dfs=true;
	bool safe=true;
	bool vis[ROW+2][COL+2];
	memset(vis,0,sizeof(vis));
	int x=0;
	while (flag){
		int cc=0;
		system("cls");
		flag=ShowMap(cur,answer,vis,flag,dfs,x);
		system("cls");
		for (int i=1;i<=ROW;i++){
			for (int j=1;j<=COL;j++){
				cout<<cur[i][j];
				if (cur[i][j]!='.'){
					cc++;
				}
			}
			cout<<endl;
		}
		Sleep(TIME);
		if (cc>=ROW*COL-MINENUM){
			break;
		}
	}
	int cnt=0;
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			if (cur[i][j]!='.'&&cur[i][j]!='*'){
				cnt++;
			}
		}
	}
	cout<<"当前已打开"<<cnt<<"个方格"<<endl;
	if (cnt==ROW*COL-MINENUM){
		cout<<"恭喜你扫雷成功！"<<endl;
	} 
}
void game(){
	system("cls");
	char mp[ROW+2][COL+2];
	int a[ROW+2][COL+2];
	memset(a,0,sizeof(a));
	InitMap(mp,a);
	char answer[ROW+2][COL+2];
	AnswerMap(mp,a,answer);
	char cur[ROW+2][COL+2];
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			cur[i][j]='.';
		}
	}
	RunMap(cur,answer);
	cout<<"游戏结束！"<<endl<<endl;
	cout<<"本次扫雷的正确结果是："<<endl;
	for (int i=1;i<=ROW;i++){
		for (int j=1;j<=COL;j++){
			cout<<answer[i][j];
		}
		cout<<endl;
	}
	return;
}
int main(){
	bool flag=true;
	while (flag){
		srand(time(0));
		system("cls");
		cout<<"****************************************"<<endl;
		cout<<"*               扫雷游戏               *"<<endl;
		cout<<"*                 开始                 *"<<endl;
		cout<<"*                 结束                 *"<<endl;
		cout<<"****************************************"<<endl;
		cout<<"输入start后开始自动扫雷，输入end后自动退出游戏，区分大小写！"<<endl;
		string s;
		getline(cin,s);
		if (s=="start"){
			game();
		}
		else if (s=="end"){
			flag=false;
		}
		else{
			cout<<"指令有误，请重新输入！"<<endl;
		}
		system("pause");
	}
	return 0;
}
