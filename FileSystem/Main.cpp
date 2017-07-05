#include "head.h"

void print()
{
	cout<<"--------------------------------------------------------------------"<<endl;
}

void MainPage()   // 主页信息
{
	cout<<"--------------------------command list-----------------------------\n";
	cout<<"---close file_name----------------关闭文件\n";
	cout<<"---copy name des_director_name----复制文件到指定目录（绝对路径）\n";
	cout<<"---create file_name---------------建立文件\n";
	cout<<"---deldir director_name-----------删除文件夹\n";
	cout<<"---delfile file_name--------------删除文件\n";
	cout<<"---dir----------------------------显示当前目录中的子目录和文件\n";
	cout<<"---initi--------------------------格式化文件系统\n";
	cout<<"---ini director_name--------------格式化文件夹\n";
	cout<<"---logout-------------------------保存结果并退出系统\n";
	cout<<"---ltdir -------------------------返回上一级目录\n";
	cout<<"---mkdir director_name------------建立目录\n";
	cout<<"---ntdir director_name------------进入下一级目录\n";
	cout<<"---open file_name-----------------打开文件\n";
	cout<<"---read file_name-----------------读文件\n";
	cout<<"---rename old_name new_name-------重命名\n";
	cout<<"---write file_name content--------写文件\n";
	cout<<"---wrmore file_name content time--向文件写入同一内容多次\n";
}

void CurrentDirector()   // 显示当前目录
{
	stack<int> temp;
	director temp_director = myFileSystem.vector_director[current_director_index];
	while(temp_director.last_director != -1)
	{
		temp.push(temp_director.id);
		temp_director = myFileSystem.vector_director[temp_director.last_director];
	}
	temp.push(temp_director.id);
	while(!temp.empty())
	{
		int index = temp.top();
		cout<<myFileSystem.vector_director[index].name<<">";
		temp.pop();
	}
	cout<<"$";
}

void main()
{
	//Initialize_Root_Path();
	string command;
	char ch ;
	
	while(1)
	{
		cout<<"是否初始化文件系统，若初始化，则之前的信息将消失!  Y/N"<<endl;
		cin>>ch;
		if(ch == 'Y' || ch =='y')
		{
			Initialize();
			break;
		}
		else
		{
			if(ch == 'N' || ch=='n')
			{
				if(Load())   // 若已初始化
				{
					break;
				}
				
			}
			else
			{
				cout<<"输入有误，请处输入Y/N"<<endl;

			}
		}
		print();
	}
	
	if(LoginIn())
	{
		cout<<"登陆成功！欢迎您，"<<current_user.name<<endl;
	}
	else
	{
		cout<<"由于您多次登录失败，本系统自动关闭"<<endl;
		cout<<"按任意键退出"<<endl;
		system("pause");
		exit(0);
	}

	MainPage();
	
	while(true)
	{
		print();
		CurrentDirector();   // 显示当前目录
		cin>>command;
		string param;

		if(command == "mkdir")
		{
			cin>>param;
			mkdir(param);
			continue;
		}
		if(command == "dir")
		{
			dir();
			continue;
		}
		if(command == "ntdir")
		{
			cin>>param;
			ntdir(param);
			continue;
		}
		if(command == "ltdir")
		{
			ltdir();
			continue;
		}
		if(command == "create")
		{
			cin>>param;
			create(param);
			continue;
		}
		if(command == "delfile")
		{
			cin>>param;
			delfile(param);
			continue;
		}
		if(command == "deldir")
		{
			cin>>param;
			deldir(param);
			continue;
		}
		if(command == "write")
		{
			cin>>param;
			string temp ;
			cin>>temp;
			write(param,temp);
			continue;
		}
		if(command == "wrmore")
		{
			cin>>param;
			string temp_1;
			cin>>temp_1;
			int temp_2;
			cin>>temp_2;
			wrmore(param,temp_1,temp_2);
			continue;
		}
		if(command == "open")
		{
			cin>>param;
			open(param);
			continue;
		}
		if(command == "read")
		{
			cin>>param;
			read(param);
			continue;
		}
		if(command == "close")
		{
			cin>>param;
			close(param);
			continue;
		}
		if(command == "logout")
		{
			LoginOut();
			system("pause");
			exit(0);
		}
		bool initi(string director_name);  // 格式化文件夹
		if(command == "initi")
		{
			Initialize();
			continue;
		}
		if(command == "rename")
		{
			cin>>param;
			string str;
			cin>>str;
			rename(param,str);
			continue;
		}
		if(command == "ini")
		{
			cin>>param;
			initi(param);
			continue;
		}
		if(command == "copy")
		{
			cin>>param;
			string str;
			cin>>str;
			copy(param,str);
			continue;
		}
		cout<<"错误指令，请重新输入"<<endl;
		while(1)    // 过滤掉剩余指令
		{
			char ch ;
			ch = getchar();		
			if(ch == '\n')
			{
				break;
			}
		}
	}

	system("pause");
}