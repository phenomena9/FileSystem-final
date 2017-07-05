#include "head.h"

user current_user;

bool CheckUser(string name,string password) // 检查该用户是否是初始化的用户
{
	for(int i=0;i<MAX_User_NUMBER;i++)
	{
		if(myFileSystem.user_info[i].name == name && myFileSystem.user_info[i].password == password)
		{
			return true;
		}

	}
	return false;
}//dongle

bool LoginIn()    //登录模块
{
	
	int chance = 5;
	string name;
	string password;
	while(chance > 0)
	{
		cout<<"请输入用户名:";
		cin>>name;
		cout<<"请输入密码：";
		cin>>password;
		if(CheckUser(name,password))
		{
			current_user.name = name;
			current_user.password = password;
			return true;
		}
		else
		{
			cout<<"用户名或密码错误，您还有"<<--chance<<"次机会"<<endl;
			print();
		}
	}
	return false;
	
	
}//dongle


