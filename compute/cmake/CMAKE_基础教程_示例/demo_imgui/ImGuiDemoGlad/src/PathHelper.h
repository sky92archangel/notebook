#pragma once


#include  <direct.h>  
#include <iostream>
#include <string>


/// <summary>
/// ��õ�ǰ��ִ��Ŀ¼
/// </summary>
/// <returns></returns>
std::string GetCWD()
{
	const int MAX_LENGTH = 512;
	char buffer[MAX_LENGTH];

	getcwd(buffer, 512);
	std::string cwd = buffer;

	int pos = cwd.find("\\");
	while (pos != cwd.npos)
	{
		cwd.replace(pos, 1, "/");
		pos = cwd.find("\\");
	} 
	return cwd;
}