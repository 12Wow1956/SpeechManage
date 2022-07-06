#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include "Speaker.h"
using namespace std;

class SpeechManager {
public:
	SpeechManager();

	// 第一次比赛选手 12名
	vector<int> v1;

	// 第二次比赛选手 6名
	vector<int> v2;

	// 最终晋级选手 3名
	vector<int>vVectory;

	// 存放编号、以及具体选手的容器
	map<int, Speaker> sMP;

	// 第几次比赛
	int sIndex;

	// 初始化属性
	void initSyx();

	// 初始化12名选手
	void initSpeacher();

	// 开始比赛的流程
	void startSpeechProcess();

	// 抽签
	void startDraw();

	// 开始比赛
	void startContest();

	// 显示晋级名单
	void jinJiList(); 

	// 保存记录
	void saveRecord();

	// 读回记录
	void loadRecord();

	// 判断文件是否为空
	bool fileIsEmpty;

	// 记录往届的比赛记录：【没有搞明白】一条map容器的记录会存放一条往届记录。（所以后面才要读一条往届记录就创建一个vector容器用来存放往届记录）
	map<int, vector<string>> s_Record;

	// 显示往届记录
	void showRecord();

	// 清空文件
	void clearRecord();

	void showMenu();

	// 退出系统
	void exitSystem();

	~SpeechManager();
};