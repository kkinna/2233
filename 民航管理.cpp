#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <cstdlib>
#define maxname 10
using namespace std;

class Map;
class City//�����ռ�������Ϣ����
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
			cout << "���б�ţ�" << number << '\t' << "��������:" << name << '\t' << "�������꣺��" << x
			<< ',' << y << ')' << endl; 
		}
		friend Map; 
};
		
class Map//����һ�����Ա�ʾ������е��� 
{
	protected:
		City *cities;
		int curCounter,maxCounter;//cur:��ǰ��������max:�������� 
	public:
		Map(int maxc=10)
		{
			maxCounter=maxc;curCounter=0;
			if(maxc) cities=new City[maxc];
			else cities=0; 
		}
		Map(Map &m) {cities=m.cities;curCounter=m.curCounter;maxCounter=m.maxCounter;}
		~Map() {delete [] cities;}
		double Distance(int x1,int y1,int x2,int y2)//������о��� 
		{
			return sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
		}
		void Addcity(int num,char *na,int x,int y)//��ӳ��� 
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
		void DeleteCity(int num)//���ݱ��ɾ������ 
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
		void SaveCity(const char *filename)//��������Ϣд��filename 
		{
			ofstream out;
			out.open(filename);
			for(int i=0;i<curCounter;i++)
			out<<cities[i].number<<'\t'<<cities[i].name<<'\t'<<cities[i].x<<'\t'<<cities[i].y<<endl;
			out.close();
		}
		void ReadCity(const char *filename)//���ļ��еĳ�����Ϣ��ȡ��׷�ӵ��ڴ��ͼ��Ϣ�б��� //ע��� 
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
		void ImportDataBase()//�ж����ļ�database.txt���ڣ������ReadCity�������������ݶ���cities[]�С����ļ������ڣ������� 
		{
			fstream infile("database.txt",ios::in);
			if(infile) ReadCity("database.txt");
			else cout<<"database.txt������"<<endl;
			infile.close();
		}
		void UpdateCity(int i,int num,char *na,int x,int y)//�޸��±�Ϊi�ĳ�����Ϣ 
		{
			City temp(num,na,x,y);
			cities[i]=temp; 
		}
		int FindCity(int num)//�����±���Ѱ������Ϣ 
		{
			int i=0;
			for(;i<curCounter;i++)
			{
				if(num==cities[i].number) return i;
			}
			if(i==curCounter) return -1;
		}
		void ShowCities()//��ʾȫ��������Ϣ 
		{
			for(int i=0;i<curCounter;i++) cities[i].show();
		}
		void ShowCity(int i)
		{
			cout << "���б�ţ�" << cities[i].number << '\t' << "��������:" << cities[i].name << '\t' << "�������꣺��" << cities[i].x<< ',' << cities[i].y << ')' << endl;
		}
		int GetCurCounter()//��ȡ��ǰ��������
		{
			return curCounter;
		}
		int GetPsoitionX(int i)//�����±�Ϊi�ĳ�������x
		{
			return cities[i].x;
		}
		int GetPositionY(int i) //�����±�Ϊi�ĳ�������y
		{
			return cities[i].y;
		}
};

class Plane//�ɻ���Ϣ��¼
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
		void show()//��ʾ�ɻ���Ϣ 
		{
			cout << "�ɻ����:" << number << '\t' << "�ɻ��ͺ�����:" << name << '\t'
			<< "�ɻ�����:" << weight << '\t' << "�ɻ�����:��" << x << ',' << y << ')' << endl;
		}
		int Getplanenem()   //��ȡ�ɻ��ı�ţ��ݴ��ж��Ƿ��зɻ�����Ϣ
		{
			return number;
		}
		int Getx() //��ȡ�ɻ�����x
		{
				return x;
			}
		int Gety()//��ȡ�ɻ�����y
		{
			return y;
		}
		int CanBrake(double sp,double reDistance)//�ж��Ƿ����ɲ��
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

int menu_select()//�˵� 
{
	const char *m[12]={
		"1. ���ӳ�����Ϣ",
		"2. ɾ��������Ϣ",
		"3. �޸ĳ�����Ϣ",
		"4. ���������Ϣ���ļ�",
		"5. ���ļ���ȡ������Ϣ",
		"6. ��ʾ���г�����Ϣ",
		"7. ���÷ɻ���Ϣ",
		"8. ��ʾ�ɻ���Ϣ",
		"9. �ж���ɷɻ��Ƿ����ɲ��",
		"10. ��ѯ�ɻ��״�뾶�����г�����Ϣ",
		"0. �˳�"};
	int i,choice;
	do
	{
		system("cls");//����
		for(i=0;i<11;i++)
			cout<<m[i]<<endl;
		cout<<"Input 0-10:";
		cin>>choice; 
	} while(choice<0|| choice>10);
	return choice;
}

void appendCity(Map &mapObj); //׷�ӳ��м�¼
void delCity(Map &mapObj); //ɾ�����м�¼  
void updCity(Map &mapObj);//�޸ĳ��м�¼
void SaveToFile(Map &mapObj); //���������Ϣ��д������ļ�
void ReadFromFile(Map &mapObj);//�Ӵ����ļ���ȡ������Ϣ
void ShowAllCities(Map &mapObj);   //��ʾȫ��������Ϣ
void AddPlane(Plane &planeObj);//����ɻ���Ϣ
void ShowPlane(Plane &planeObj);//��ʾ�ɻ���Ϣ
void Brake(Plane &planeObj);//�жϷɻ��Ƿ����ɲ��
void RadarSearch(Plane &planeObj, Map &mapObj);//��ʾ�൱ǰ�ɻ����״�ɨ��뾶�����еĳ�����Ϣ
char Quit(Map &mapObj); //�˳�����
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
			case 1:	appendCity(mapobj);//׷�ӳ�����Ϣ 
					system("pause");
					break;
			case 2: delCity(mapobj);//ɾ��������Ϣ 
					system("pause");
					break;
			case 3: updCity(mapobj);//�޸ĳ�����Ϣ 
					system("pause");
					break;
			case 4: SaveToFile(mapobj);//�����ļ���Ϣ����д����� 
					system("pause");
					break;
			case 5: ReadFromFile(mapobj);//�Ӵ����ļ���ȡ������Ϣ 
					system("pause");
					break;
			case 6: ShowAllCities(mapobj);//��ʾȫ��������Ϣ 
					system("pause");
					break;
			case 7: AddPlane(planeobj);//����ɻ���Ϣ 
					system("pause");
					break;
			case 8: ShowPlane(planeobj);//��ʾ�ɻ���Ϣ 
					system("pause");
					break;
			case 9: Brake(planeobj);//�ж��Ƿ����ɲ�� 
					system("pause");
					break;
			case 10: RadarSearch(planeobj,mapobj);//��ʾ�뾶�ڳ�����Ϣ 
					system("pause");
					break;
			case 0: //�˳����� 
		if(Quit(mapobj)!='y')  continue;
		}
		if(sel==0) break;
	}
	return 0;
}
void appendCity(Map &mapobj)
{
	int num,x1,y1;char na[maxname];
	cout<<"�������µĳ�����Ϣ����š����ơ����꣩"<<endl;
	cin>>num>>na>>x1>>y1;
	mapobj.Addcity(num,na,x1,y1);
}
void delCity(Map &mapobj)
{
	int a(0);
	cout<<"��������Ҫɾ�����еĳ��б�ţ�"<<endl;
	cin>>a;
	
	if(mapobj.FindCity(a))
		{
			mapobj.DeleteCity(a);cout<<"��ɾ��"<<endl;
		}
	else cout<<"δɾ��"<<endl;	 
}
void updCity(Map &mapobj)
{
	int a(0);
	cout<<"������Ҫ�޸ĵĳ��еĳ��б��:"<<endl;
	cin>>a;
	if(mapobj.FindCity(a))
	{
		int temp=mapobj.FindCity(a);
		int num,x1,y1;char *na;
		cout<<"�������µĳ�����Ϣ����š����ơ����꣩��"<<endl;
		cin>>num>>na>>x1>>y1;
		mapobj.UpdateCity(temp,num,na,x1,y1);	
	}
}
void SaveToFile(Map &mapobj)
{
	char a[100];
	cout<<"������Ҫ���̵��ļ�����.txt��β����"<<endl;
	cin>>a;
	ifstream in(a);
	if(in)
	{
		in.close();
		mapobj.ReadCity(a);
	}
	else cout<<"�ļ���������"<<endl;
 }
void ReadFromFile(Map &mapObj)
{
	char na[100]="\0";
	cout << "������׷�ӳ�����Ϣ�ļ�����";
	cin>>na;cout << endl;
	mapObj.ReadCity(na);
}
void ShowAllCities(Map &mapobj)
{
	if(mapobj.GetCurCounter()) mapobj.ShowCities();
	else cout<<"��ǰ�����ڳ�����Ϣ��"<<endl; 
 } 
void AddPlane(Plane &planeobj)
{
	int num,x1,y1;char na[100];double we;
	cout<<"�밴˳������ɻ���š����ơ����������꣺"<<endl;
	cin>>num>>na>>we>>x1>>y1;
	planeobj.setPlane(num,na,we,x1,y1);
}
void ShowPlane(Plane &planeobj)
{
	if(planeobj.Getplanenem()) planeobj.show();
	else cout<<"û�зɻ���Ϣ��"<<endl;
 }
void Brake(Plane &planeobj)
{
	double speed,m;
	cout<<"�����뵱ǰʱ�٣�km/h)��"<<endl;
	cin>>speed;
	cout<<"������ʣ���ܵ����ȣ�m��:"<<endl; cin>>m;
	if(planeobj.Getplanenem())
	{
		if(planeobj.CanBrake(speed,m)) cout<<"����ɲ����"<<endl;
		else cout<<"������ɲ����"<<endl;
	}
 }
void RadarSearch(Plane &planeobj, Map &mapobj)
{
	double r;
	cout<<"�������״�뾶�������"<<endl;
	cin>>r;
	if(planeobj.Getplanenem())
	{
		planeobj.RadaFind(r,mapobj); 
	 } 
 }
char Quit(Map &mapobj)
{
	char a;
	cout<<"�Ƿ��˳�(y/n)��"<<endl;
	cin>>a;
	if(a=='y') mapobj.SaveCity("database");
	return a;
 } 
