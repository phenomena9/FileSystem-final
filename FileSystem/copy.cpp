#include "head.h"

bool ParsePath(string path)  // 把路径解析出来
{
	int begin = 0;
	int ending = 0;
	string accessed;  // 已经过的路径
	bool flag = true;  // 表示是否是第一个目录
	while(ending < strlen(path.c_str()))
	{
		if(path[ending] == '\\')
		{
			string director = path.substr(begin,ending-begin);
			if(flag)
			{
				if(director != "home")             // 首目录必须是home
				{
					cout<<"输入的路径不正确！"<<endl;
					cout<<"请输入绝对路径！如：home\\one\\two"<<endl;
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if(!ntdir(director))  //到下一目录
				{
					cout<<"无法到达"<<accessed<<"路径下的"<<director<<"文件夹"<<endl;
					return false;
				}
				accessed += director;
			}
			
			begin = ending+1;
			//cout<<"得到的目录是"<<director<<endl;
			
		}
		ending ++;
	}
	string director = path.substr(begin,ending - begin);
	if(!ntdir(director))
	{
		cout<<"无法到达"<<accessed<<"路径下的"<<director<<"文件夹"<<endl;
		return false;
	}
	cout<<"跳转到"<<path<<"成功！"<<endl;
	return true;
}


void CopyDirector(int pos,int limit)   //复制pos处的目录   limit是为了防止 新建的目录被重复新建 如果发现要新建的目录索引大于或等于
	//limit就不用再新建了
{
	//把pos处目录包含的所有文件夹全部新建，更新last_director
	
	director current = myFileSystem.vector_director[pos];
	director temp;
	temp.id = myFileSystem.vector_director.size();
	
	temp.name = current.name;
	temp.owner = current.owner;
	temp.last_director = current_director_index;   //更新last_director
		
	list<int>::iterator p = current.file_list.begin();  //文件的索引相同  
	while(p != current.file_list.end())
	{
		temp.file_list.push_back(*p);
		p++;
	}

	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);  // 在当前目录中加入新的目录
	myFileSystem.vector_director.push_back(temp);//在目录信息中加入新的目录
	current_director_index = temp.id;	//更新当前目录
	
	p = current.director_list.begin();  // 在当前目录的子目录中继续复制
	while(p != current.director_list.end())
	{
		if(*p != -1 && *p < limit)
		{
			CopyDirector(*p,limit);
		}
		p++;
	}
	
}

bool copy(string name,string path)
{
	int strore_director = current_director_index;  //暂存
	current_director_index = 0;
	int pos = IsFileInCurrentDirector(name);
	if(pos == -1)
	{
		pos = IsDirectorInCurrentDirector(name);
		if(pos == -1)
		{
			cout<<"当前目录没有"<<name<<"的文件或文件夹"<<endl;
			cout<<"复制失败！"<<endl;
			return false;
		}
		else// 复制的是文件夹
		{
			if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")//验证权限
			{
				cout<<"您没有操作"<<name<<"文件夹的权限"<<endl;
				cout<<"复制失败!"<<endl;
				return false;
			}

			if(!ParsePath(path))  //跳转到要复制到的目录中
			{
				cout<<"复制失败！"<<endl;
				return false;
			}
			CopyDirector(pos,myFileSystem.vector_director.size());


		}
	}
	else  // 复制的是文件
	{
		if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")//验证权限
		{
			cout<<"您没有操作"<<name<<"文件夹的权限"<<endl;
			cout<<"复制失败!"<<endl;
			return false;
		}

		if(!ParsePath(path))    //跳转到要复制到的目录中
		{
			cout<<"复制失败！"<<endl;
			return false;
		}
		myFileSystem.vector_director[current_director_index].file_list.push_back(pos);     //在该目录下添加对应文件的索引即可
	}

	cout<<"复制成功!"<<endl;
	current_director_index = strore_director;  //恢复当前目录
	return true;
}