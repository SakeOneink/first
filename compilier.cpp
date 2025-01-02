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
char *keyword[32]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register", "return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"}; //�ؼ�������
char *oprsym[19]={"+","-","*","/","=","+=","-=","*=","/=","<<",">>","<","<=",">",">=","==","!=","&&","||"};
char *boundsym[10]={"{","}","[","]",";",",",".","(",")",":"};

FILE *in,*out;//���������ļ�ָ��
char arr[MAX];//arr�����ŵ��ʷ���
char currentchar;//currentchar��ŵ�ǰ�����ַ�
int i=0;//arr�����һ��ָ��
int IsKey(char *strToken);//�ж��Ƿ�Ϊ�ؼ���
int IsLetter(char ch);//�ж�����ĸ
int IsDigit(char ch);//�ж�������
void scan();//�ʷ�ɨ�����

//�ʷ�����
struct lexnode
{
	int type;         //���ʵ������
	int dValue;      //���ֵ�value
	string sValue;   //�ַ���value	
};
lexnode lex[MAXLEX]; //���ڴ�Ŵʷ������Ľ����Ȼ����Ϊ�﷨����������

int locate = 0;//ָʾ���ʵ�λ��
//

//�ʷ�����
int IsKey(char *strToken)//�ж��Ƿ�Ϊ�ؼ���
 {
	 for (int i=0;i<38;i++)
	 {
		 if(strcmp(strToken,keyword[i])==0)//strcmp�Ƚ� 
			 return 1;
	 }
	 return 0;
 }

int IsLetter(char ch)//�ж�����ĸ
 {
	 if  (('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z'))
		 return 1;
	 else 
		 return  0;
 }

 int IsDigit(char ch)//�ж�������
 {
	 if(ch>='0'&&ch<='9')
		 return 1;
	 else 
		 return 0;
 }

void scan()//�ʷ�ɨ�����
{

	int value;
	int ch;
	ifstream fin("D:\\Desktop\\input.txt");//�Զ���ʽ�������ļ�

	if((in=fopen("D:\\Desktop\\input.txt","r"))==NULL)//inΪ�ļ�ָ��
	{
		printf("�ļ�δ��\n");
		exit(0);
	}

	ofstream fout("D:\\Desktop\\output.txt");//��д��ʽ������ļ�

	if((out=fopen("D:\\Desktop\\output.txt","w"))==NULL)
	{
		printf("cannout open outfile\n");
		exit(1);//exit����������process.h��
	}
	fout<<"���ʴʷ������������н�����£�"<<endl;
	fout<<setw(10)<<"word"<<setw(20)<<"type"<<setw(20)<<"value"<<endl;
	cout<<setw(10)<<"word"<<setw(20)<<"type"<<setw(20)<<"value"<<endl;


	currentchar=fgetc(in);//��in��ָ�ļ��ĵ�ǰָ��λ�ö�ȡһ���ַ�,�����currentchar��

	while(currentchar == ' ')//��������һ���ַ�
	{ 
		currentchar=fgetc(in);//fgetc����������stdio.hͷ�ļ���
	}

	while(currentchar!='#')//'#'Ϊ������
	{  
		if(IsDigit(currentchar)||IsLetter(currentchar)||currentchar=='{'||currentchar=='}'||currentchar=='['||currentchar==']'||currentchar=='('||currentchar==')'||currentchar=='+'||currentchar=='-'||currentchar=='*'||currentchar=='/'||currentchar=='='||currentchar==';')      
		{

			i=0;//���arr�ַ�����

			if(IsDigit(currentchar))//���������ж�
			{

				int temp=0;	
				arr[i++]=currentchar;
				temp=temp*10+(int(currentchar)-48);

				currentchar=fgetc(in);//�ٶ�����һ���ַ�		
				
				while(IsDigit(currentchar))
				{
					arr[i++]=currentchar;
					temp=temp*10+(int(currentchar)-48);
					currentchar=fgetc(in);
					
				}

				arr[i++]='\0';//�����ַ���������־	
				lex[locate].type=14;
				lex[locate].dValue =temp;
				fout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].dValue<<endl;//���ַ�������arr����ַ���
			    cout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<lex[locate].dValue<<endl;
				locate++;
			}

			while(currentchar==' ')
			{ 
				currentchar=fgetc(in);
			}
			//�жϱ�ʶ���͹ؼ��ֲ���
			if(IsLetter(currentchar))//����ĸ��ͷ
			{
				i=0;//���arr�ַ�����
				while(IsLetter(currentchar)||IsDigit(currentchar))//���ַ�����������arr������
				{
					arr[i++]=currentchar;
					currentchar=fgetc(in);
				}
				//���ַ�����arr�͹ؼ��ֱ�Ƚϣ��жϵ��ʴ��ǹؼ��ֻ��Ǳ�ʶ��
				arr[i++]='\0';//'\0'Ϊ������
				value=IsKey(arr);//�ж�arr�����д�ŵ�ֵ�Ƿ�Ϊ�ؼ���
				if(strcmp(arr,"for") == 0)
				{
					lex[locate].type=8;      //�ؼ���for
					fout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<arr<<endl;
					cout<<setw(10)<<arr<<setw(20)<<lex[locate].type<<setw(20)<<arr<<endl;
					locate++; 
				}
				else
				{
					lex[locate].type=20;      //������ʶ��
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
			//�ж������
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
			//�жϽ��޷�
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
			//���з��Ĵ���
			if((ch=currentchar)=='\n')//���з�
			{
				currentchar=fgetc(in);
			}
			while(currentchar==' ')//������һ���ַ�
			{
				currentchar=fgetc(in);
			}
		}
		else//�뿪ʼ��if���Ӧ
		{
			fout<<setw(10)<<currentchar<<setw(20)<<"error"<<setw(20)<<currentchar<<endl;
			cout<<setw(10)<<currentchar<<setw(20)<<"error"<<setw(20)<<currentchar<<endl;
			currentchar=fgetc(in);
		}
		while(currentchar==' ')//currentcharΪ��ʱ������һ���ַ�
		{
			currentchar=fgetc(in);
		}
	}


	fclose(in);//�ر��ļ�
	fclose(out);
	
}

//�﷨����
stack<int> analyzeStack;	//����һ�����͵ķ���ջ
int pri;  //��¼���ȹ�ϵ
int pri_1;//��ʱ��¼���ȹ�ϵ,������ʱջ�й�Լ�ıȽ� 

//�﷨�������� 
void GramAnalyze();

int position=0; //������봮�е�ǰ����ķ���λ�� 

//�����ȹ�ϵ 
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

//�Ƚ����ȹ�ϵ 
int Compare(int stackNum,int inputNum)  
{
	return matrix[stackNum-1][inputNum-1];
}

int type_1;      //������һ�����ʵı�ʶ���ж���+��- 
string Value_1;  //������嵥�� 


//�﷨�������
void GramAnalyze()  
{
	
    pri=Compare(analyzeStack.top(),lex[position].type);

	if(N==pri)
	{
		cout<<"����λ�ÿ�����:"<<position+1<<endl;
		return ;
	}
	else if(1==analyzeStack.top())//����״̬
	{
        analyzeStack.pop();
		if(21==analyzeStack.top()&&21==lex[position].type)
		{
			cout<<"�����ɹ�"<<endl;
		}
		else
		{
			cout<<"����λ�ÿ�����:"<<position+1<<endl;
		}
	}
	else if(-1==pri)           //���ջ�з������ȼ�С�ڻ���ڽ�Ҫ������ŵ����ȼ� ����
	{
		analyzeStack.push(lex[position].type);
		position++;  
		GramAnalyze(); 
	}
	else if(0==pri)       //����
	{
		analyzeStack.push(lex[position].type);
		position++;
		GramAnalyze(); 
	}
	else if(1==pri)           //���ջ�з������ȼ����ڽ�Ҫ������ŵ����ȼ� ��Լ
	{
		stack<int> semStack;//����һ����ʱ��ջ
	    do
		{
			semStack.push(analyzeStack.top());//��ջ��Ԫ��push����ʱ����ջ
			analyzeStack.pop();
			pri_1=Compare(analyzeStack.top(),semStack.top()); 
			if(N==pri_1)
			{
				cout<<"����λ�ÿ�����:"<<position+1<<endl;
			}
		}while(pri_1!=-1); //�Ҿ��,������ŵ���ʱջ��

		if(semStack.size()==12)  //S�Ĳ���ʽ         
		{
			analyzeStack.push(1); //��sѹջ
			if(type_1==17)   // Ϊ+
			cout<<"(5)  "<<Value_1<<":="<<Value_1<<"+"<<1<<endl;
			else if(type_1==18)   //Ϊ -
			cout<<"(5)  "<<Value_1<<":="<<Value_1<<"-"<<1<<endl;
			cout<<"(6)  goto (2)"<<endl;
			cout<<"(7)  over:"<<endl;
		}
		else if(semStack.size()==5)//   G�Ĳ���ʽ
		{
			analyzeStack.push(5);//��G��ջ����Լ
			cout<<"(3)  "<<"t:=";     

			if(lex[position-3].type==20)       //��ʶ��
			cout<<lex[position-3].sValue<<"+";

			else if(lex[position-3].type==14)  //����
			cout<<lex[position-3].dValue<<"+";

			if(lex[position-1].type==20)         
			cout<<lex[position-1].sValue<<endl;

			else if(lex[position-1].type==14)
			cout<<lex[position-1].dValue<<endl;
            cout<<"(4)  "<<lex[position-5].sValue<<":="<<"t"<<endl;
		}
		else  //A ,B,E.D,F�Ĳ���ʽ
		{
			semStack.pop();
			if(semStack.top()==13)  //A�Ĳ���ʽ
			{
				cout<<"(1)  "<<lex[position-3].sValue<<":="<<lex[position-1].dValue<<endl;
				analyzeStack.push(2);  //A��ջ
			}
			else if(semStack.top()==15)//<
			{
				cout<<"(2)  if "<<lex[position-3].sValue;
				if(lex[position-2].type==15)  // <
					cout<<">=";
				else if(lex[position-2].type==16)// >
					cout<<"<=";
				cout<<lex[position-1].dValue<<" goto over"<<endl;
				analyzeStack.push(3);//B��ջ 
			}
			else if(semStack.top()==16)//>
			{
				cout<<"(2) if "<<lex[position-3].sValue;
				if(lex[position-2].type==15)
					cout<<">=";
				else if(lex[position-2].type==16)
					cout<<"<=";
				cout<<lex[position-1].dValue<<" goto over"<<endl; 
				analyzeStack.push(6); //E��ջ 
			}
			else if(semStack.top()==17)//��ʱջ��Ϊ�Ӻ�
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
	
	cout<<"        forѭ�����ķ��������ƣ������ȷ����������ַ��ʾ)  "<<endl;
    cout<<"�ʷ���������Ľ�����£�                                        "<<endl;
	scan();    
	cout<<"----------------------------------------------------------------"<<endl;
	cout<<"����ַ��������:"<<endl;
    lex[locate].type=21;
    
	locate++;	 //�����������#��������d
	analyzeStack.push(21);//�����������#�����ջ
	GramAnalyze();
	return 0;
}
