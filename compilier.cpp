#include<iostream>
#include <stdio.h>
#include <string>
#include <process.h>
#include<fstream>
#include<iomanip>
#include<stack>
#include<queue>
#include<string.h>

using namespace std;


#define MAX 100
#define MAXLEX 100
#define N -2
char *keyword[32]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register", "return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"}; //关键字数组
char *oprsym[19]={"+","-","*","/","=","+=","-=","*=","/=","<<",">>","<","<=",">",">=","==","!=","&&","||"};
char *boundsym[10]={"{","}","[","]",";",",",".","(",")",":"};

FILE *in,*out;//定义两个文件指针
char arr[MAX];//arr数组存放单词符号
char currentchar;//currentchar存放当前输入字符
int i=0;//arr数组的一个指针
int IsKey(char *strToken);//判断是否为关键字
int IsLetter(char ch);//判断是字母
int IsDigit(char ch);//判断是数字
void scan();//词法扫描程序

//词法分析
struct lexnode
{
	int type;         //单词的类别码
	int dValue;      //数字的value
	string sValue;   //字符的value	
};
lexnode lex[MAXLEX]; //用于存放词法分析的结果，然后作为语法分析的输入

int locate = 0;//指示单词的位置
//

//词法分析
int IsKey(char *strToken)//判断是否为关键字
 {
	 for (int i=0;i<38;i++)
	 {
		 if(strcmp(strToken,keyword[i])==0)//strcmp比较 
			 return 1;
	 }
	 return 0;
 }

int IsLetter(char ch)//判断是字母
 {
	 if  (('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z'))
		 return 1;
	 else 
		 return  0;
 }

 int IsDigit(char ch)//判断是数字
 {
	 if(ch>='0'&&ch<='9')
		 return 1;
	 else 
		 return 0;
 }

void scan()//词法扫描程序
{

	int value;
	int ch;
	ifstream fin("D:\\Desktop\\input.txt");//以读方式打开输入文件

	if((in=fopen("D:\\Desktop\\input.txt","r"))==NULL)//in为文件指针
	{
		printf("文件未打开\n");
		exit(0);
	}

	ofstream fout("D:\\Desktop\\output.txt");//以写方式打开输出文件

	if((out=fopen("D:\\Desktop\\output.txt","w"))==NULL)
	{
		printf("cannout open outfile\n");
		exit(1);//exit函数包含在process.h中
	}
	fout<<"单词词法分析程序运行结果如下："<<endl;
	fout<<setw(10)<<"word"<<setw(20)<<"type"<<setw(20)<<"value"<<endl;
	cout<<setw(10)<<"word"<<setw(20)<<"type"<<setw(20)<<"value"<<endl;


	currentchar=fgetc(in);//从in所指文件的当前指针位置读取一个字符,存放在currentchar中

	while(currentchar == ' ')//继续读下一个字符
	{ 
		currentchar=fgetc(in);//fgetc函数包含在stdio.h头文件中
	}

	while(currentchar!='#')//'#'为结束符
	{  
		if(IsDigit(currentchar)||IsLetter(currentchar)||currentchar=='{'||currentchar=='}'||currentchar=='['||currentchar==']'||currentchar=='('||currentchar==')'||currentchar=='+'||currentchar=='-'||currentchar=='*'||currentchar=='/'||currentchar=='='||currentchar==';')      
		{

			i=0;//清空arr字符数组

			if(IsDigit(currentchar))//常数部分判断
			{

				int temp=0;	
				arr[i++]=currentchar;
				temp=temp*10+(int(currentchar)-48);

				currentchar=fgetc(in);//再读入下一个字符		
				
				while(IsDigit(currentchar))
				{
					arr[i++]=currentchar;
					temp=temp*10+(int(currentchar)-48);
					currentchar=fgetc(in);
					
				}

				arr[i++]='\0';//赋给字符串结束标志	
				lex[locate].type=14;
				lex[locate].dValue =temp;
				fout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].dValue<<endl;//用字符数组名arr输出字符串
			    cout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].dValue<<endl;
				locate++;
			}

			while(currentchar==' ')
			{ 
				currentchar=fgetc(in);
			}
			//判断标识符和关键字部分
			if(IsLetter(currentchar))//以字母开头
			{
				i=0;//清空arr字符数组
				while(IsLetter(currentchar)||IsDigit(currentchar))//读字符并将其存放在arr数组中
				{
					arr[i++]=currentchar;
					currentchar=fgetc(in);
				}
				//把字符数组arr和关键字表比较，判断单词串是关键字还是标识符
				arr[i++]='\0';//'\0'为结束符
				value=IsKey(arr);//判断arr数组中存放的值是否为关键字
				if(strcmp(arr,"for") == 0)
				{
					lex[locate].type=8;      //关键字for
					fout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<arr<<endl;
					cout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<arr<<endl;
					locate++; 
				}
				else
				{
					lex[locate].type=20;      //其他标识符
					lex[locate].sValue =arr;
					fout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].sValue<<endl;
					cout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].sValue<<endl;
					locate++;
				}		
			}
			while(currentchar==' ')
			{ 
				currentchar=fgetc(in);
			}
			//判断运算符
			if(currentchar=='+'||currentchar=='-'||currentchar=='*'||currentchar=='/'||currentchar=='='||currentchar=='<'||currentchar=='>')
			{
					
				switch(currentchar)
				{
						
					case '=':
						{
							lex[locate].type=13;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case '+':
						{
							lex[locate].type=17;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case '-':
						{
							lex[locate].type=18;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case '>':
						{
							lex[locate].type=16;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case '<':
						{
							lex[locate].type=15;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}

				}
				currentchar=fgetc(in);
			}
			while(currentchar==' ')
			{ 
				currentchar=fgetc(in);
			}
			//判断界限符
			if(currentchar=='{'||currentchar=='}'||currentchar=='['||currentchar==']'||currentchar=='('||currentchar==')'||currentchar==';')
			{
				switch(currentchar)
				{
					case '(':
						{
							lex[locate].type=9;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case ')':
						{
							lex[locate].type=10;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case '{':
						{
							lex[locate].type=11;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;								
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;locate++;
							break;
						}
					case '}':
						{
							lex[locate].type=12;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;
							locate++;
							break;
						}
					case ';':
						{
							lex[locate].type=19;
							fout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;								
							cout<<setw(10)<<currentchar<<setw(20)<<lex[locate].type<<setw(20)<<currentchar<<endl;locate++;
							break;
						}
				}
				
				currentchar=fgetc(in);
			}
			while(currentchar==' ')
			{ 
				currentchar=fgetc(in);
			}
			//换行符的处理
			if((ch=currentchar)=='\n')//换行符
			{
				currentchar=fgetc(in);
			}
			while(currentchar==' ')//读入下一个字符
			{
				currentchar=fgetc(in);
			}
		}
		else//与开始的if相对应
		{
			fout<<setw(10)<<currentchar<<setw(20)<<"error"<<setw(20)<<currentchar<<endl;
			cout<<setw(10)<<currentchar<<setw(20)<<"error"<<setw(20)<<currentchar<<endl;
			currentchar=fgetc(in);
		}
		while(currentchar==' ')//currentchar为空时读入下一个字符
		{
			currentchar=fgetc(in);
		}
	}


	fclose(in);//关闭文件
	fclose(out);
	
}

//语法分析
stack<int> analyzeStack;	//定义一个整型的分析栈
int pri;  //记录优先关系
int pri_1;//临时记录优先关系,用于临时栈中规约的比较 

//语法分析函数 
void GramAnalyze();

int position=0; //标记输入串中当前输入的符号位置 

//简单优先关系 
int matrix[21][21]={     
//SA B D G E FFor( ) { } = c < > + - ; i #
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,1},//S
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N},//A
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N},//B
{N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N,N,N,N,N},//D
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N},//G
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N},//E
{N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N,N,N,N,N},//F
{N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N,N,N,N,N,N},//For
{N,0,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,-1,N},//(
{N,N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N,N,N,N},//)
{N,N,N,N,0,N,N,N,N,N,N,N,N,N,N,N,N,N,N,-1,N},//{
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,1},//}
{N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,0,N},//=
{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,1,N,N},//c
{N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N},//<
{N,N,N,N,N,N,N,N,N,N,N,N,N,0,N,N,N,N,N,N,N},//>
{N,N,N,N,N,N,N,N,N,1,N,N,N,0,N,N,0,N,N,0,N},//+
{N,N,N,N,N,N,N,N,N,1,N,N,N,N,N,N,N,0,N,N,N},//-
{N,N,0,0,N,0,0,N,N,N,N,0,N,N,N,N,N,N,N,-1,N},//;
{N,N,N,N,N,N,N,N,N,N,N,N,0,N,0,0,0,0,1,N,N},//i
{-1,N,N,N,N,N,N,-1,N,1,N,N,N,0,N,N,0,N,N,N,0},//#
};

//比较优先关系 
int Compare(int stackNum,int inputNum)  
{
	return matrix[stackNum-1][inputNum-1];
}

int type_1;      //定义另一个单词的标识，判断是+，- 
string Value_1;  //定义具体单词 


//语法语义分析
void GramAnalyze()  
{
	
    pri=Compare(analyzeStack.top(),lex[position].type);

	if(N==pri)
	{
		cout<<"出错，位置可能在:"<<position+1<<endl;
		return ;
	}
	else if(1==analyzeStack.top())//接受状态
	{
        analyzeStack.pop();
		if(21==analyzeStack.top()&&21==lex[position].type)
		{
			cout<<"分析成功"<<endl;
		}
		else
		{
			cout<<"出错，位置可能在:"<<position+1<<endl;
		}
	}
	else if(-1==pri)           //如果栈中符号优先级小于或等于将要输入符号的优先级 移入
	{
		analyzeStack.push(lex[position].type);
		position++;  
		GramAnalyze(); 
	}
	else if(0==pri)       //移入
	{
		analyzeStack.push(lex[position].type);
		position++;
		GramAnalyze(); 
	}
	else if(1==pri)           //如果栈中符号优先级大于将要输入符号的优先级 规约
	{
		stack<int> semStack;//定义一个临时的栈
	    do
		{
			semStack.push(analyzeStack.top());//将栈顶元素push到临时符号栈
			analyzeStack.pop();
			pri_1=Compare(analyzeStack.top(),semStack.top()); 
			if(N==pri_1)
			{
				cout<<"出错，位置可能在:"<<position+1<<endl;
			}
		}while(pri_1!=-1); //找句柄,将句柄放到临时栈中

		if(semStack.size()==12)  //S的产生式         
		{
			analyzeStack.push(1); //将s压栈
			if(type_1==17)   // 为+
			cout<<"(5)  "<<Value_1<<":="<<Value_1<<"+"<<1<<endl;
			else if(type_1==18)   //为 -
			cout<<"(5)  "<<Value_1<<":="<<Value_1<<"-"<<1<<endl;
			cout<<"(6)  goto (2)"<<endl;
			cout<<"(7)  over:"<<endl;
		}
		else if(semStack.size()==5)//   G的产生式
		{
			analyzeStack.push(5);//将G入栈，规约
			cout<<"(3)  "<<"t:=";     

			if(lex[position-3].type==20)       //标识符
			cout<<lex[position-3].sValue<<"+";

			else if(lex[position-3].type==14)  //常数
			cout<<lex[position-3].dValue<<"+";

			if(lex[position-1].type==20)         
			cout<<lex[position-1].sValue<<endl;

			else if(lex[position-1].type==14)
			cout<<lex[position-1].dValue<<endl;
            cout<<"(4)  "<<lex[position-5].sValue<<":="<<"t"<<endl;
		}
		else  //A ,B,E.D,F的产生式
		{
			semStack.pop();
			if(semStack.top()==13)  //A的产生式
			{
				cout<<"(1)  "<<lex[position-3].sValue<<":="<<lex[position-1].dValue<<endl;
				analyzeStack.push(2);  //A入栈
			}
			else if(semStack.top()==15)//<
			{
				cout<<"(2)  if "<<lex[position-3].sValue;
				if(lex[position-2].type==15)  // <
					cout<<">=";
				else if(lex[position-2].type==16)// >
					cout<<"<=";
				cout<<lex[position-1].dValue<<" goto over"<<endl;
				analyzeStack.push(3);//B入栈 
			}
			else if(semStack.top()==16)//>
			{
				cout<<"(2) if "<<lex[position-3].sValue;
				if(lex[position-2].type==15)
					cout<<">=";
				else if(lex[position-2].type==16)
					cout<<"<=";
				cout<<lex[position-1].dValue<<" goto over"<<endl; 
				analyzeStack.push(6); //E入栈 
			}
			else if(semStack.top()==17)//临时栈顶为加号
			{
				analyzeStack.push(4);//D-> i + +
				type_1=17;
				Value_1=lex[position-3].sValue;
			}
			else if(semStack.top()==18)//-
			{
				analyzeStack.push(7);
				type_1=18;
				Value_1=lex[position-3].sValue; 
			}
		}
		int tempsize=semStack.size();
		for(int t=0;t<tempsize;t++)
			semStack.pop();
		GramAnalyze(); 
	}
}


int main()
{
	
	cout<<"        for循环语句的翻译程序设计（简单优先法、输出三地址表示)  "<<endl;
    cout<<"词法分析程序的结果如下：                                        "<<endl;
	scan();    
	cout<<"----------------------------------------------------------------"<<endl;
	cout<<"三地址码结果如下:"<<endl;
    lex[locate].type=21;
    
	locate++;	 //保存句子括号#入输入流d
	analyzeStack.push(21);//保存句子括号#入分析栈
	GramAnalyze();
	return 0;
}
