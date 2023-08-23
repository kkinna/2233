#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <cstdlib>
#define maxname 10
using namespace std;

class Map;
class City//定义收集城市信息的类
{	
	protected:
		int  number;char name[maxname];
		int x,y;
	public:
		City(int num=1001,char na[]="",int x1=50,int y1=60)
		{
			number=num;strcpy(name,na);x=x1;y=y1;
		 } 
		void setNumber(int num){number=num;}
		void setName(char *na){strcpy(name,na);}
		void setPosition(int xpos,int ypos){x=xpos;y=ypos;}
		void gerName(char *na){strcpy(na,name);}
		int getNum() {return number;}
		int getX() {return x;}
		int getY() {return y;}
		void show()
		{
			cout << "城市编号：" << number << '\t' << "城市名称:" << name << '\t' << "城市坐标：（" << x
			<< ',' << y << ')' << endl; 
		}
		friend Map; 
};
		
class Map//定义一个可以表示多个城市的类 
{
	protected:
		City *cities;
		int curCounter,maxCounter;//cur:当前城市数，max:最大城市数 
	public:
		Map(int maxc=10)
		{
			maxCounter=maxc;curCounter=0;
			if(maxc) cities=new City[maxc];
			else cities=0; 
		}
		Map(Map &m) {cities=m.cities;curCounter=m.curCounter;maxCounter=m.maxCounter;}
		~Map() {delete [] cities;}
		double Distance(int x1,int y1,int x2,int y2)//计算城市距离 
		{
			return sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
		}
		void Addcity(int num,char *na,int x,int y)//添加城市 
		{
			City a(num,na,x,y);
			if(curCounter==maxCounter)
			{
				City *newcity;
				newcity=new City[maxCounter+10];
				for(int i=0;i<maxCounter;i++)
					newcity[i]=cities[i];
				maxCounter+=10;
				cities=newcity;
			}
			cities[curCounter++]=a;
		}
		void DeleteCity(int num)//根据编号删除城市 
		{
			int i=0;
			for(;i<curCounter;i++)
			{
				if(cities[i].number==num) break;	
			}
			for(int p=i;p<curCounter;p++)
			{
				cities[p]=cities[p+1];
			}
			curCounter--;
		}
		void SaveCity(const char *filename)//将城市信息写入filename 
		{
			ofstream out;
			out.open(filename);
			for(int i=0;i<curCounter;i++)
			out<<cities[i].number<<'\t'<<cities[i].name<<'\t'<<cities[i].x<<'\t'<<cities[i].y<<endl;
			out.close();
		}
		void ReadCity(const char *filename)//将文件中的城市信息读取并追加到内存地图信息列表中 //注意点 
		{City *m;int i=0;m=new City[100];
	 	for(;i<curCounter;i++)
		 	m[i]=cities[i];
	 	fstream infile(filename,ios::in);
	 	while(infile>>m[i].number>>m[i].name>>m[i].x>>m[i].y)
	 		i++;
	 	for(int j=0;j<i;j++)
		 	cities[j]=m[j];
		 curCounter=i;
		 infile.close();
		 }
		void ImportDataBase()//判断若文件database.txt存在，则调用ReadCity（）函数将内容读入cities[]中。若文件不存在，不报错。 
		{
			fstream infile("database.txt",ios::in);
			if(infile) ReadCity("database.txt");
			else cout<<"database.txt不存在"<<endl;
			infile.close();
		}
		void UpdateCity(int i,int num,char *na,int x,int y)//修改下标为i的城市信息 
		{
			City temp(num,na,x,y);
			cities[i]=temp; 
		}
		int FindCity(int num)//利用下标找寻城市信息 
		{
			int i=0;
			for(;i<curCounter;i++)
			{
				if(num==cities[i].number) return i;
			}
			if(i==curCounter) return -1;
		}
		void ShowCities()//显示全部城市信息 
		{
			for(int i=0;i<curCounter;i++) cities[i].show();
		}
		void ShowCity(int i)
		{
			cout << "城市编号：" << cities[i].number << '\t' << "城市名称:" << cities[i].name << '\t' << "城市坐标：（" << cities[i].x<< ',' << cities[i].y << ')' << endl;
		}
		int GetCurCounter()//读取当前城市数量
		{
			return curCounter;
		}
		int GetPsoitionX(int i)//返回下标为i的城市坐标x
		{
			return cities[i].x;
		}
		int GetPositionY(int i) //返回下标为i的城市坐标y
		{
			return cities[i].y;
		}
};

class Plane//飞机信息记录
{
	protected:
		int number;char name[maxname];double weight;
		int x;int y;
	public:
		Plane(int num=0,char *na="",double we=0,int x1=0,int y1=0)
		{
			number=num;strcpy(name,na);weight=we;x=x1;y=y1;
		 } 
		void setPlane(int num,char *na,double w,int xpos,int ypos)
		{
			number=num;strcpy(name,na);weight=w;x=xpos;y=ypos;
		}
		void show()//显示飞机信息 
		{
			cout << "飞机编号:" << number << '\t' << "飞机型号名称:" << name << '\t'
			<< "飞机重量:" << weight << '\t' << "飞机坐标:（" << x << ',' << y << ')' << endl;
		}
		int Getplanenem()   //读取飞机的编号，据此判断是否有飞机的信息
		{
			return number;
		}
		int Getx() //读取飞机坐标x
		{
				return x;
			}
		int Gety()//读取飞机坐标y
		{
			return y;
		}
		int CanBrake(double sp,double reDistance)//判断是否可以刹车
		{
			if(!number) return -1;
			double temp=weight*sp/5;
			if(temp<reDistance) return 1;
			else return 0;
		 } 
		void RadaFind(double radarRadius,Map mapobj)
		{
			int i=0,a=mapobj.GetCurCounter();
			for(;i<a;i++)
			{
				int x1=mapobj.GetPsoitionX(i);
				int y1=mapobj.GetPositionY(i);
				if(sqrt((double)((x1-x)*(x1-x)+(y1-y)*(y1-y)))<radarRadius)
					mapobj.ShowCity(i);
			}
			
		}
};

int menu_select()//菜单 
{
	const char *m[12]={
		"1. 增加城市信息",
		"2. 删除城市信息",
		"3. 修改城市信息",
		"4. 保存城市信息至文件",
		"5. 从文件读取城市信息",
		"6. 显示所有城市信息",
		"7. 设置飞机信息",
		"8. 显示飞机信息",
		"9. 判断起飞飞机是否可以刹车",
		"10. 查询飞机雷达半径内所有城市信息",
		"0. 退出"};
	int i,choice;
	do
	{
		system("cls");//清屏
		for(i=0;i<11;i++)
			cout<<m[i]<<endl;
		cout<<"Input 0-10:";
		cin>>choice; 
	} while(choice<0|| choice>10);
	return choice;
}

void appendCity(Map &mapObj); //追加城市记录
void delCity(Map &mapObj); //删除城市记录  
void updCity(Map &mapObj);//修改城市记录
void SaveToFile(Map &mapObj); //保存城市信息，写入磁盘文件
void ReadFromFile(Map &mapObj);//从磁盘文件读取城市信息
void ShowAllCities(Map &mapObj);   //显示全部城市信息
void AddPlane(Plane &planeObj);//输入飞机信息
void ShowPlane(Plane &planeObj);//显示飞机信息
void Brake(Plane &planeObj);//判断飞机是否可以刹车
void RadarSearch(Plane &planeObj, Map &mapObj);//显示距当前飞机在雷达扫描半径内所有的城市信息
char Quit(Map &mapObj); //退出处理
int main()
{
	Map mapobj;
	Plane planeobj;
	int sel;
	mapobj.ImportDataBase();
	for( ; ; )
	{
		switch(sel=menu_select())
		{
			case 1:	appendCity(mapobj);//追加城市信息 
					system("pause");
					break;
			case 2: delCity(mapobj);//删除城市信息 
					system("pause");
					break;
			case 3: updCity(mapobj);//修改城市信息 
					system("pause");
					break;
			case 4: SaveToFile(mapobj);//保存文件信息，并写入磁盘 
					system("pause");
					break;
			case 5: ReadFromFile(mapobj);//从磁盘文件读取城市信息 
					system("pause");
					break;
			case 6: ShowAllCities(mapobj);//显示全部城市信息 
					system("pause");
					break;
			case 7: AddPlane(planeobj);//输入飞机信息 
					system("pause");
					break;
			case 8: ShowPlane(planeobj);//显示飞机信息 
					system("pause");
					break;
			case 9: Brake(planeobj);//判断是否可以刹车 
					system("pause");
					break;
			case 10: RadarSearch(planeobj,mapobj);//显示半径内城市信息 
					system("pause");
					break;
			case 0: //退出处理 
		if(Quit(mapobj)!='y')  continue;
		}
		if(sel==0) break;
	}
	return 0;
}
void appendCity(Map &mapobj)
{
	int num,x1,y1;char na[maxname];
	cout<<"请输入新的城市信息（编号、名称、坐标）"<<endl;
	cin>>num>>na>>x1>>y1;
	mapobj.Addcity(num,na,x1,y1);
}
void delCity(Map &mapobj)
{
	int a(0);
	cout<<"请输入想要删除城市的城市编号："<<endl;
	cin>>a;
	
	if(mapobj.FindCity(a))
		{
			mapobj.DeleteCity(a);cout<<"已删除"<<endl;
		}
	else cout<<"未删除"<<endl;	 
}
void updCity(Map &mapobj)
{
	int a(0);
	cout<<"请输入要修改的城市的城市编号:"<<endl;
	cin>>a;
	if(mapobj.FindCity(a))
	{
		int temp=mapobj.FindCity(a);
		int num,x1,y1;char *na;
		cout<<"请输入新的城市信息（编号、名称、坐标）："<<endl;
		cin>>num>>na>>x1>>y1;
		mapobj.UpdateCity(temp,num,na,x1,y1);	
	}
}
void SaveToFile(Map &mapobj)
{
	char a[100];
	cout<<"请输入要存盘的文件名（.txt结尾）："<<endl;
	cin>>a;
	ifstream in(a);
	if(in)
	{
		in.close();
		mapobj.ReadCity(a);
	}
	else cout<<"文件名不存在"<<endl;
 }
void ReadFromFile(Map &mapObj)
{
	char na[100]="\0";
	cout << "请输入追加城市信息文件名：";
	cin>>na;cout << endl;
	mapObj.ReadCity(na);
}
void ShowAllCities(Map &mapobj)
{
	if(mapobj.GetCurCounter()) mapobj.ShowCities();
	else cout<<"当前不存在城市信息。"<<endl; 
 } 
void AddPlane(Plane &planeobj)
{
	int num,x1,y1;char na[100];double we;
	cout<<"请按顺序输入飞机编号、名称、重量、坐标："<<endl;
	cin>>num>>na>>we>>x1>>y1;
	planeobj.setPlane(num,na,we,x1,y1);
}
void ShowPlane(Plane &planeobj)
{
	if(planeobj.Getplanenem()) planeobj.show();
	else cout<<"没有飞机信息。"<<endl;
 }
void Brake(Plane &planeobj)
{
	double speed,m;
	cout<<"请输入当前时速（km/h)："<<endl;
	cin>>speed;
	cout<<"请输入剩余跑道长度（m）:"<<endl; cin>>m;
	if(planeobj.Getplanenem())
	{
		if(planeobj.CanBrake(speed,m)) cout<<"可以刹车。"<<endl;
		else cout<<"不可以刹车。"<<endl;
	}
 }
void RadarSearch(Plane &planeobj, Map &mapobj)
{
	double r;
	cout<<"请输入雷达半径（公里）："<<endl;
	cin>>r;
	if(planeobj.Getplanenem())
	{
		planeobj.RadaFind(r,mapobj); 
	 } 
 }
char Quit(Map &mapobj)
{
	char a;
	cout<<"是否退出(y/n)："<<endl;
	cin>>a;
	if(a=='y') mapobj.SaveCity("database");
	return a;
 } 
