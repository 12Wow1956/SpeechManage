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
	cout << "************** 欢迎来到演讲比赛管理系统****************" << endl;
	cout << "**************  1、开始演讲比赛        ****************" << endl;
	cout << "**************  2、查看往届比赛结果    ****************" << endl;
	cout << "**************  3、清空文件记录        ****************" << endl;
	cout << "**************  4、退出程序            ****************" << endl;
	cout << "*******************************************************" << endl;
}

// 初始化属性
void SpeechManager::initSyx() {
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->sMP.clear();
	this->sIndex = 1;

	this->s_Record.clear();
}

// 初始化12名选手
void SpeechManager::initSpeacher() {

	string nameSeed = "ABCDEFGHIJKL";	

	// 用for loop初始化12名选手
	for (unsigned i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		// 定义选手属性
		Speaker sp; 
		sp.sName = name;

		for (int j = 0; j < 2; ++j) {
			sp.sScore[j] = 0;
		}

		// 初始化v1:它里面只存放了选手的编号
		this->v1.push_back(i + 10001);

		// 初始化存放选手完整属性的map容器
		sMP.insert(pair<int, Speaker>(i + 10001, sp));
	}	
}

// 开始比赛的流程
void SpeechManager::startSpeechProcess() {
	// 第一次比赛
	// 1、抽签
	startDraw();

	// 2、比赛
	startContest();
	// 3、宣布结果
	jinJiList();

	this->sIndex++;

	// 第二次比赛
	// 1、抽签
	startDraw();
	// 2、比赛
	startContest();
	// 3、宣布最终结果
	jinJiList();

	saveRecord();

	// 再次初始化
	this->initSyx();

	this->initSpeacher();

	this->loadRecord();

	system("pause");
	system("cls");
}

// 抽签
void SpeechManager::startDraw() {
	cout << "第 <<" << this->sIndex << ">> 轮比赛正在抽签中。。。" << endl;
	cout << "----------------------------------" << endl;
	if (this->sIndex == 1) {
		random_shuffle(v1.begin(), v1.end());
		cout << endl;
		cout << "比赛先后顺序如下：" << endl;
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
			cout << *it << " ";
		}
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		cout << endl;
		cout << "比赛先后顺序如下：" << endl;
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
	cout << "———————-———第" << this->sIndex << "轮比赛现在正式开始：---------——————" << endl << endl << endl;


	// 先定义一个比赛选手，这样子方便搞定是第一次比赛还是第二次比赛
	vector<int> vec_Src;
	if (this->sIndex == 1) {
		vec_Src = v1;
	}
	else {
		vec_Src = v2;
	}

	multimap<double, int, greater<double>> map_tmp;
	int num = 0;


	// for loop 遍历比赛选手：在当中进行评委打分、相加所有得总和、得平均分,并存入map容器
	for (vector<int>::iterator it = vec_Src.begin(); it != vec_Src.end(); ++it) {

		num++;

		// 定义为每一个选手存放打分的容器
		deque<double>d;
		for (unsigned i = 0; i < vec_Src.size(); ++i) {
			// 打分
			double score = (rand() % 401 + 600) / 10.f; // 400 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		// 排序去掉最高分和最低分
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		// 保存到容器map
		sMP[*it].sScore[this->sIndex - 1] = avg;

		map_tmp.insert(make_pair(avg, *it)); // *it，即it解引用后就是各个选手的编号
		if (num % 6 == 0) {
			cout << "第 " << num / 6 << "组演讲比赛名次如下：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = map_tmp.begin(); it != map_tmp.end(); ++it) {
				cout << "编号： " << it->second << " 选手名： " << this->sMP[it->second].sName << "选手得分："
					<< sMP[it->second].sScore[this->sIndex - 1] << endl;
			}


			// ——————————————————这里，比赛中，将每组排序后的前三名放入到下一次比赛的容器中！！！完美——————————————————————————————————————————
			int cnt = 0;
			for (multimap<double, int, greater<double>>::iterator it = map_tmp.begin(); it != map_tmp.end() && cnt<3; ++it, cnt++) {
				if (this->sIndex == 1) {
					v2.push_back(it->second);
				}
				else {
					vVectory.push_back(it->second);
				}
			}

			// 按6人一组的排序完之后应该清空临时容器，否则后面的排名会累加过来！
			map_tmp.clear();
		}		
	}

	system("pause");
	cout << endl;
	//system("cls");
}

// 显示晋级名单
void SpeechManager::jinJiList() {

	vector<int>v;
	if (this->sIndex == 1) {
		v = v2;
	}
	else {
		v = vVectory;
	}

	cout << "————————————第" << this->sIndex << "次晋级名单如下：————————————————" << endl;
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {		
			cout << "编号：" << *it << " 姓名：" << sMP[*it].sName << " 得分: " << sMP[*it].sScore[sIndex-1] << endl;
	}

}

// 保存记录
void SpeechManager::saveRecord() {
	// 写是输出
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->vVectory.begin(); it != this->vVectory.end(); ++it) {
		ofs << *it << "," << this->sMP[*it].sScore[1] << ",";
	}
	ofs << endl;

	ofs.close();

	this->fileIsEmpty = false;
	cout << "记录已保存！" << endl;

	cout << "本次比赛正式结束！" << endl;
}

// 读回记录
void SpeechManager::loadRecord() {
	// 文件三种情况
	ifstream ifs;
	
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "文件为空！" << endl;
		ifs.close();
		return;
	}

	// 文件存在且有数据
	this->fileIsEmpty = false;
	ifs.putback(ch); // 将刚刚尝试文件是否为空的那个字符读回来

	
	string data;
	int index = 0; // 用一个变量来保存往届记录的届数

	// 10012,91.075,10003,82.3,10008,81.775,
	while (ifs >> data) {
		int start = 0;
		int pos = -1;

		// +++++++++++++++++++++以下这行代码位置放错【放在while循环外】最后导致我从文件读取到程序的记录一直都只是第一行
		// 而是应该让它每次回车都创建一个存放每届记录的vector容器，即一届存放到一个vector容器中。这样子在后面存放到s_Record容器中时才不会出错啦
		vector<string> vs;

		// +++++++++++++++++++++++++++++++++++++++++我忘记了让它去找逗号的位置+++++++++++++++++++++++++++++++++++++++
		// pos是找到以后返回的位置下标
		while (true) {
			pos = data.find(",", start);

			if (pos == -1) {
				// 没找到的情况
				break;
			}

			string tmp = data.substr(start, pos - start);
			//cout << tmp << endl; 注释的目的是因为不是让它输出的
			// 应该先把这一届的记录即所有读到的string，存入一个vector
			vs.push_back(tmp); // 每读到一个string字符串就把它放进vector容器

			start = pos + 1;
		}

		// 最终读进来的字符串容器存入记录中
		s_Record.insert(pair<int, vector<string>>(index, vs));
		index++;

		// test:测试下map容器中我是否存入东西啦
		/*for (map<int, vector<string>>::iterator it = s_Record.begin(); it != s_Record.end(); ++it) {
			cout << "第 " << it->first << "届：  "
				<< "  冠军编号： " << it->second[0] << " 冠军成绩：" << it->second[1]
				<< "  亚军编号： " << it->second[2] << " 亚军成绩：" << it->second[3]
				<< "  季军编号： " << it->second[4] << " 季军成绩：" << it->second[5] << endl;
		}*/
		
	}
	ifs.close();
}

// 显示往届记录
void SpeechManager::showRecord() {

	if (this->fileIsEmpty) {
		cout << "文件不存在，或记录为空！" << endl;
	}
	else {

		for (int i = 0; i < s_Record.size(); ++i) {			
			cout << "第 " << i+1 << "届：  "
				<< "  冠军编号： " << s_Record[i][0] << " 冠军成绩：" << s_Record[i][1]
				<< "  亚军编号： " << s_Record[i][2] << " 亚军成绩：" << s_Record[i][3]
				<< "  季军编号： " << s_Record[i][4] << " 季军成绩：" << s_Record[i][5] << endl;
			}

		
	}

	system("pause");
	system("cls");
}

// 清空文件
void SpeechManager::clearRecord() {
	int sel = 0;
	cout << "确认清空吗？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;
	cin >> sel;

	if (sel == 1) {
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc); // 如果文件存在就删除新建

		ofs.close();
		cout << "已清空！" << endl;

		// 再次初始化一下各位容器选手等以便有残留。
		this->initSyx();

		this->initSpeacher();

		this->loadRecord();
	}

	system("pause");
	system("cls");
}

// 退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);

	system("cls");
}

SpeechManager::~SpeechManager()
{

}