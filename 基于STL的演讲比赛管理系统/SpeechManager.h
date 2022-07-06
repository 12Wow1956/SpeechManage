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

	// ��һ�α���ѡ�� 12��
	vector<int> v1;

	// �ڶ��α���ѡ�� 6��
	vector<int> v2;

	// ���ս���ѡ�� 3��
	vector<int>vVectory;

	// ��ű�š��Լ�����ѡ�ֵ�����
	map<int, Speaker> sMP;

	// �ڼ��α���
	int sIndex;

	// ��ʼ������
	void initSyx();

	// ��ʼ��12��ѡ��
	void initSpeacher();

	// ��ʼ����������
	void startSpeechProcess();

	// ��ǩ
	void startDraw();

	// ��ʼ����
	void startContest();

	// ��ʾ��������
	void jinJiList(); 

	// �����¼
	void saveRecord();

	// ���ؼ�¼
	void loadRecord();

	// �ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	// ��¼����ı�����¼����û�и����ס�һ��map�����ļ�¼����һ�������¼�������Ժ����Ҫ��һ�������¼�ʹ���һ��vector����������������¼��
	map<int, vector<string>> s_Record;

	// ��ʾ�����¼
	void showRecord();

	// ����ļ�
	void clearRecord();

	void showMenu();

	// �˳�ϵͳ
	void exitSystem();

	~SpeechManager();
};