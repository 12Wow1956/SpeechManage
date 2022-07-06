#include "SpeechManager.h"

SpeechManager::SpeechManager()
{
	this->initSyx();

	this->initSpeacher();

	this->loadRecord();
}

void SpeechManager::showMenu()
{
	cout << "*******************************************************" << endl;
	cout << "************** ��ӭ�����ݽ���������ϵͳ****************" << endl;
	cout << "**************  1����ʼ�ݽ�����        ****************" << endl;
	cout << "**************  2���鿴����������    ****************" << endl;
	cout << "**************  3������ļ���¼        ****************" << endl;
	cout << "**************  4���˳�����            ****************" << endl;
	cout << "*******************************************************" << endl;
}

// ��ʼ������
void SpeechManager::initSyx() {
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->sMP.clear();
	this->sIndex = 1;

	this->s_Record.clear();
}

// ��ʼ��12��ѡ��
void SpeechManager::initSpeacher() {

	string nameSeed = "ABCDEFGHIJKL";	

	// ��for loop��ʼ��12��ѡ��
	for (unsigned i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		// ����ѡ������
		Speaker sp; 
		sp.sName = name;

		for (int j = 0; j < 2; ++j) {
			sp.sScore[j] = 0;
		}

		// ��ʼ��v1:������ֻ�����ѡ�ֵı��
		this->v1.push_back(i + 10001);

		// ��ʼ�����ѡ���������Ե�map����
		sMP.insert(pair<int, Speaker>(i + 10001, sp));
	}	
}

// ��ʼ����������
void SpeechManager::startSpeechProcess() {
	// ��һ�α���
	// 1����ǩ
	startDraw();

	// 2������
	startContest();
	// 3���������
	jinJiList();

	this->sIndex++;

	// �ڶ��α���
	// 1����ǩ
	startDraw();
	// 2������
	startContest();
	// 3���������ս��
	jinJiList();

	saveRecord();

	// �ٴγ�ʼ��
	this->initSyx();

	this->initSpeacher();

	this->loadRecord();

	system("pause");
	system("cls");
}

// ��ǩ
void SpeechManager::startDraw() {
	cout << "�� <<" << this->sIndex << ">> �ֱ������ڳ�ǩ�С�����" << endl;
	cout << "----------------------------------" << endl;
	if (this->sIndex == 1) {
		random_shuffle(v1.begin(), v1.end());
		cout << endl;
		cout << "�����Ⱥ�˳�����£�" << endl;
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
			cout << *it << " ";
		}
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		cout << endl;
		cout << "�����Ⱥ�˳�����£�" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
			cout << *it << " ";
		}
	}

	cout << endl;
	system("pause");
	//system("cls");
}

void SpeechManager::startContest() {
	cout << endl;
	cout << "��������������-��������" << this->sIndex << "�ֱ���������ʽ��ʼ��---------������������" << endl << endl << endl;


	// �ȶ���һ������ѡ�֣������ӷ���㶨�ǵ�һ�α������ǵڶ��α���
	vector<int> vec_Src;
	if (this->sIndex == 1) {
		vec_Src = v1;
	}
	else {
		vec_Src = v2;
	}

	multimap<double, int, greater<double>> map_tmp;
	int num = 0;


	// for loop ��������ѡ�֣��ڵ��н�����ί��֡�������е��ܺ͡���ƽ����,������map����
	for (vector<int>::iterator it = vec_Src.begin(); it != vec_Src.end(); ++it) {

		num++;

		// ����Ϊÿһ��ѡ�ִ�Ŵ�ֵ�����
		deque<double>d;
		for (unsigned i = 0; i < vec_Src.size(); ++i) {
			// ���
			double score = (rand() % 401 + 600) / 10.f; // 400 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		// ����ȥ����߷ֺ���ͷ�
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		// ���浽����map
		sMP[*it].sScore[this->sIndex - 1] = avg;

		map_tmp.insert(make_pair(avg, *it)); // *it����it�����ú���Ǹ���ѡ�ֵı��
		if (num % 6 == 0) {
			cout << "�� " << num / 6 << "���ݽ������������£�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = map_tmp.begin(); it != map_tmp.end(); ++it) {
				cout << "��ţ� " << it->second << " ѡ������ " << this->sMP[it->second].sName << "ѡ�ֵ÷֣�"
					<< sMP[it->second].sScore[this->sIndex - 1] << endl;
			}


			// ��������������������������������������������У���ÿ��������ǰ�������뵽��һ�α����������У���������������������������������������������������������������������������������������������
			int cnt = 0;
			for (multimap<double, int, greater<double>>::iterator it = map_tmp.begin(); it != map_tmp.end() && cnt<3; ++it, cnt++) {
				if (this->sIndex == 1) {
					v2.push_back(it->second);
				}
				else {
					vVectory.push_back(it->second);
				}
			}

			// ��6��һ���������֮��Ӧ�������ʱ���������������������ۼӹ�����
			map_tmp.clear();
		}		
	}

	system("pause");
	cout << endl;
	//system("cls");
}

// ��ʾ��������
void SpeechManager::jinJiList() {

	vector<int>v;
	if (this->sIndex == 1) {
		v = v2;
	}
	else {
		v = vVectory;
	}

	cout << "��������������������������" << this->sIndex << "�ν����������£���������������������������������" << endl;
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {		
			cout << "��ţ�" << *it << " ������" << sMP[*it].sName << " �÷�: " << sMP[*it].sScore[sIndex-1] << endl;
	}

}

// �����¼
void SpeechManager::saveRecord() {
	// д�����
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->vVectory.begin(); it != this->vVectory.end(); ++it) {
		ofs << *it << "," << this->sMP[*it].sScore[1] << ",";
	}
	ofs << endl;

	ofs.close();

	this->fileIsEmpty = false;
	cout << "��¼�ѱ��棡" << endl;

	cout << "���α�����ʽ������" << endl;
}

// ���ؼ�¼
void SpeechManager::loadRecord() {
	// �ļ��������
	ifstream ifs;
	
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ�գ�" << endl;
		ifs.close();
		return;
	}

	// �ļ�������������
	this->fileIsEmpty = false;
	ifs.putback(ch); // ���ոճ����ļ��Ƿ�Ϊ�յ��Ǹ��ַ�������

	
	string data;
	int index = 0; // ��һ�����������������¼�Ľ���

	// 10012,91.075,10003,82.3,10008,81.775,
	while (ifs >> data) {
		int start = 0;
		int pos = -1;

		// +++++++++++++++++++++�������д���λ�÷Ŵ�����whileѭ���⡿������Ҵ��ļ���ȡ������ļ�¼һֱ��ֻ�ǵ�һ��
		// ����Ӧ������ÿ�λس�������һ�����ÿ���¼��vector��������һ���ŵ�һ��vector�����С��������ں����ŵ�s_Record������ʱ�Ų��������
		vector<string> vs;

		// +++++++++++++++++++++++++++++++++++++++++������������ȥ�Ҷ��ŵ�λ��+++++++++++++++++++++++++++++++++++++++
		// pos���ҵ��Ժ󷵻ص�λ���±�
		while (true) {
			pos = data.find(",", start);

			if (pos == -1) {
				// û�ҵ������
				break;
			}

			string tmp = data.substr(start, pos - start);
			//cout << tmp << endl; ע�͵�Ŀ������Ϊ�������������
			// Ӧ���Ȱ���һ��ļ�¼�����ж�����string������һ��vector
			vs.push_back(tmp); // ÿ����һ��string�ַ����Ͱ����Ž�vector����

			start = pos + 1;
		}

		// ���ն��������ַ������������¼��
		s_Record.insert(pair<int, vector<string>>(index, vs));
		index++;

		// test:������map���������Ƿ���붫����
		/*for (map<int, vector<string>>::iterator it = s_Record.begin(); it != s_Record.end(); ++it) {
			cout << "�� " << it->first << "�죺  "
				<< "  �ھ���ţ� " << it->second[0] << " �ھ��ɼ���" << it->second[1]
				<< "  �Ǿ���ţ� " << it->second[2] << " �Ǿ��ɼ���" << it->second[3]
				<< "  ������ţ� " << it->second[4] << " �����ɼ���" << it->second[5] << endl;
		}*/
		
	}
	ifs.close();
}

// ��ʾ�����¼
void SpeechManager::showRecord() {

	if (this->fileIsEmpty) {
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else {

		for (int i = 0; i < s_Record.size(); ++i) {			
			cout << "�� " << i+1 << "�죺  "
				<< "  �ھ���ţ� " << s_Record[i][0] << " �ھ��ɼ���" << s_Record[i][1]
				<< "  �Ǿ���ţ� " << s_Record[i][2] << " �Ǿ��ɼ���" << s_Record[i][3]
				<< "  ������ţ� " << s_Record[i][4] << " �����ɼ���" << s_Record[i][5] << endl;
			}

		
	}

	system("pause");
	system("cls");
}

// ����ļ�
void SpeechManager::clearRecord() {
	int sel = 0;
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	cin >> sel;

	if (sel == 1) {
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc); // ����ļ����ھ�ɾ���½�

		ofs.close();
		cout << "����գ�" << endl;

		// �ٴγ�ʼ��һ�¸�λ����ѡ�ֵ��Ա��в�����
		this->initSyx();

		this->initSpeacher();

		this->loadRecord();
	}

	system("pause");
	system("cls");
}

// �˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);

	system("cls");
}

SpeechManager::~SpeechManager()
{

}