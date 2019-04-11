/********************************************************/
/*					дһ��PLA������						*/
/*		���4ά����ķ�������	�ʵ������ٴκ��㷨ʵ��	*/
//				1.�Ҵ���㣻2.��������
/********************************************************/

#include<fstream>//���ļ���ͷ�ļ�
#include<iostream>
#include<vector>

using namespace std;

#define DEMENSION 5

double weight[DEMENSION];
int step=0;
int n = 0;//������
char *file = "PLA - ����.txt";

//����ѵ��������
struct record {
	double input[DEMENSION];
	int output;
};

//�� ��¼ ��������������Ǵ��ڽṹ�������ڣ��������Ը���ʵ��һ�������
vector<record> trainingSet;

//�����ݶ���ѵ������������ȥ
void getData(ifstream &dataFile)
{
	while (!dataFile.eof())//�����ļ�β�������棬���ļ�β�����ؼ�
	{
		record curRecord;
		curRecord.input[0] = 1;
		int i;
		for (i = 1; i < DEMENSION; i++)
		{
			dataFile >> curRecord.input[i];
			//trainingSet.push_back(curRecord);
		}
		dataFile >> curRecord.output;
		trainingSet.push_back(curRecord);		
	}
	dataFile.close();
	n = trainingSet.size();
	cout << "�����ܹ���" << n << "��" << endl;

}

int sign(double x) 
{
	if (x <= 0)return -1;
	else return 1;
}
void add(double *v1, double *v2, int demension) 
{
	int i;
	for (i = 0; i < demension; i++)v1[i] += v2[i];
}
double multiply(double *v1, double *v2, int demension)
{
	double temp = 0.0;
	int i = 0;
	for (i = 0; i < demension; i++)temp += v1[i] * v2[i];
	return temp;
}

void multiply(double *result, double *v, int demension, int num) 
{
	int i;
	for (i = 0; i < demension; i++)result[i] = num * v[i];
}

void PLA()
{
	cout << "����" << endl;
	int correctNum = 0;//��ǰ������ȷ��������������n���������һȦ�����ʾȫ����ȷ���㷨����
	int index = 0;//��ǰ���ڼ���ĵڼ�������
	bool isFinished = 0;
	while (!isFinished)//�㷨���ʱ�˳�whileѭ��
	{
		if (trainingSet[index].output == sign(multiply(weight, trainingSet[index].input, DEMENSION)))correctNum++;
		else 
		{
			//����Ȩ��w��
			double temp[DEMENSION];
			multiply(temp, trainingSet[index].input, DEMENSION, trainingSet[index].output);
			add(weight, temp, DEMENSION);
			step++;//�����Ĵ���
			correctNum = 0;//�����ˣ�û��������ȷ
			cout << "step" << step << ":" << endl << "index=" << index << "is wrong" << endl;
		}
		if (index == n - 1)index = 0;
		else index++;
		if (correctNum == n)isFinished = 1;
	}
	cout << "total step:" << step << endl;
}

void main()
{
	ifstream dataFile(file);
	
	if (dataFile.is_open())
	{
		getData(dataFile);//����getData֮��Ͳ�������
	}
	
	else
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}
	int i;
	for (i = 0; i < DEMENSION; i++)weight[i] = 0.0;//(1)ѡ��ֵw=0
	PLA();
	system("pause");

}




