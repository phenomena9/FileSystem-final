#include"head.h"
#include <stdlib.h>
#include <stdio.h>

fileSystem myFileSystem;
int memory_index;
char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];
int current_director_index;
int next_free_list_index;
int super_stack_number;

void Initialize_dataBlock()  //初始化数据块
{
	for(int i=0;i<DATA_BLOCK_NUMBER;i++)
	{
		dataBlock temp ;
		temp.next = -1;
		temp.used = 0;
		for(int j=0;j<DATA_BLOCK_LENGTH+1;j++)
		{
			temp.content[j] = '\0';//临时变量内容置为0
		}
		myFileSystem.dataArea.push_back(temp);//在vector尾部加入数据
		//cout<<"每块大小"<<sizeof(temp)<<endl;
	}
	//cout<<"数据块数目"<<myFileSystem.dataArea.size()<<endl;
	cout<<"初始化数据域成功！"<<endl;
	return ;
}


void Initialize_Index_List()  //初始化成组链
{
	
	next_free_list_index = 0;
	super_stack_number = 0;
	while(!myFileSystem.superStack.empty())//如果超级栈不空，将栈内内容全都pop出去
	{
		myFileSystem.superStack.pop();
	}
	for(int i=0;i<INDEX_LIST_NUMBER;i++)
	{
		for(int j=INDEX_LIST_LENGTH-1;j>=0;j--)
		{
			myFileSystem.free_list[i][j] = i*INDEX_LIST_LENGTH + INDEX_LIST_LENGTH - j -1;
			//cout<<i<<","<<j<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	cout<<"初始化成组链成功！"<<endl;
	return ;
}


void Initialize_User_Info()   // 初始化用户信息
{
	char temp[6]; 
	strcpy_s(temp,"user");
	for(int i=0;i<MAX_User_NUMBER;i++)
	{
		temp[4] = (char)i+49;
		temp[5] = '\0';
		myFileSystem.user_info[i].name = temp ; 
		myFileSystem.user_info[i].password = temp;
		//cout<<"转换的内容"<<myFileSystem.user_info[i].name<<endl;
	}
	cout<<"初始化用户信息成功!"<<endl;
}


void Initialize_Vector_Director()   //初始化目录信息
{
	myFileSystem.vector_director.clear();
	director first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	myFileSystem.vector_director.push_back(first);
	cout<<"初始化目录信息成功!"<<endl;
}



/*
void Initialize_Root_Path()   //初始化根路径
{
	root_path = "d:\\MyFileSystem";
	while(1)
	{
		cout<<"请设置本文件系统的根目录，默认为："<<root_path<<endl;
		cout<<"是否更改？Y/N"<<endl;
		char input ;
		
		while(1)
		{
			cin>>input;
			if(input == 'Y' || input == 'y')
			{
				cout<<"请输入新的根目录"<<endl;
				string temp;
				cin>>temp;
				if(temp[1] == ':' && temp[2] == '\\'&& ((temp[0] >= 'c' && temp[0]<='g') || ((temp[0] >= 'C' && temp[0]<='G'))) )
				{
					cout<<"更改跟目录成功！"<<endl;
					root_path = temp;
					print();
					return ;
				}
				else
				{
					cout<<"输入的根目录名不符合规范!"<<endl;
					break;
				}
			}
			else
			{
				if(input == 'N' || input == 'n')
				{
					//cout<<"初始化操作已取消！"<<endl;
					print();
					return;
				}
				else
				{
					cout<<"输入指令有误，请输入Y/N"<<endl;
				}
			}
		}
		print();
	}
	
	
}
*/
void Initialize_Memory()  // 初始化内存
{
	memory_index = 0;
	for(int i=0;i<MAX_FILE_LENGTH;i++)
	{
		for(int j=0;j<DATA_BLOCK_LENGTH;j++)
		{
			memory[i][j]='\0';
		}
	}
	cout<<"初始化内存成功!"<<endl;
}


bool Initialize()  // 初始化
{
	//Initialize_Root_Path();        // 初始化根路径
	
	Initialize_Vector_Director();   // 初始化文件夹信息

	current_director_index = 0;
	open_file_list.clear();
	myFileSystem.vector_file.clear();
	
	Initialize_dataBlock();		 // 初始化数据块
	Initialize_Index_List();		// 初始化成组链
	Initialize_User_Info();			// 初始化用户信息

	print();
	return true;
		
}



