#include <iostream>

#include "SpeechManager.h"
using namespace std;

int main() 
{
	srand((unsigned)time(NULL));
	SpeechManager sm;
	int sel = 0;

	// try: 测试初始化的结果是否已经初始化了各个选手的各个参数
	/*for (map<int, Speaker>::iterator it = sm.sMP.begin(); it != sm.sMP.end(); ++it) {
		cout << "编号： " << it->first << "  选手名： " << it->second.sName << "  选手成绩： " << it->second.sScore[0] << endl;
	}*/
	/*for (vector<int>::iterator it = sm.v1.begin(); it != sm.v1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;*/

	while (true) {
		sm.showMenu();
		cout << endl << "请选择：";
		cin >> sel;

		switch (sel)
		{
		case 1:
			sm.startSpeechProcess();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 4:
			sm.exitSystem();
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}