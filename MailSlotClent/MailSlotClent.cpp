// MailSlotClent.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <process.h>

int main(int argc, char* argv[])
{
	HANDLE hslot;	// 定义客户端邮槽句柄
	DWORD dwByteWrites;	// 定义存放写入数据个数的变量
	char computerName[256];
	char content[256];	// 定义消息内容
	sprintf_s(computerName, "\\\\.\\Mailslot\\slotsample");
	hslot = CreateFile(computerName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hslot == INVALID_HANDLE_VALUE)
	{
		printf("创建客户端邮槽失败，错误代码=%d\n", GetLastError());
		return -1;
	}
	sprintf_s(content, "我是客户端邮槽，向服务器发送测试数据");
	if (WriteFile(hslot, content, strlen(content), &dwByteWrites, NULL) == 0)
	{
		printf("向邮槽写入数据失败，错误代码=%d\n", GetLastError());
		return -1;
	}
	printf("向邮槽写入%d个字节的数据\n", dwByteWrites);
	CloseHandle(hslot);
	system("pause");
	return 0;
}