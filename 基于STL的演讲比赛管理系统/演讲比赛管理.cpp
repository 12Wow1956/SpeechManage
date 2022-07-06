#include <iostream>

#include "SpeechManager.h"
using namespace std;

int main() 
{
	srand((unsigned)time(NULL));
	SpeechManager sm;
	int sel = 0;

	// try: ���Գ�ʼ���Ľ���Ƿ��Ѿ���ʼ���˸���ѡ�ֵĸ�������
	/*for (map<int, Speaker>::iterator it = sm.sMP.begin(); it != sm.sMP.end(); ++it) {
		cout << "��ţ� " << it->first << "  ѡ������ " << it->second.sName << "  ѡ�ֳɼ��� " << it->second.sScore[0] << endl;
	}*/
	/*for (vector<int>::iterator it = sm.v1.begin(); it != sm.v1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;*/

	while (true) {
		sm.showMenu();
		cout << endl << "��ѡ��";
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