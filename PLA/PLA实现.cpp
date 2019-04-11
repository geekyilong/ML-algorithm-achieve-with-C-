/*************************************************************/
/*		       写一个PLA分类	                         */
/*	解决4维数组的分类问题	问迭代多少次后算法实现	    */
/*      1.找错误点；2.纠正错误。                             */
/*********************************************************/

#include<fstream>//读文件的头文件
#include<iostream>
#include<vector>

using namespace std;

#define DEMENSION 5

double weight[DEMENSION];
int step=0;
int n = 0;//样本数
char *file = "PLA - 副本.txt";

//储存训练样本；
struct record 
{
	double input[DEMENSION];
	int output;
};

//把 记录 存在向量里
vector<record> trainingSet;

//将数据读到训练样本向量中去
void getData(ifstream &dataFile)
{
	while (!dataFile.eof())//读到文件尾部返回真，非文件尾部返回假
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
	cout << "样本总共有" << n << "个" << endl;

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
	int correctNum = 0;//当前连续正确样本数，当等于n则表明轮完一圈，则表示全部正确，算法结束
	int index = 0;//当前正在计算的第几个样本
	bool isFinished = 0;
	while (!isFinished)//算法完成时退出while循环
	{
		if (trainingSet[index].output == sign(multiply(weight, trainingSet[index].input, DEMENSION)))correctNum++;
		else 
		{
			//修正权重w；
			double temp[DEMENSION];
			multiply(temp, trainingSet[index].input, DEMENSION, trainingSet[index].output);
			add(weight, temp, DEMENSION);
			step++;//修正的次数
			correctNum = 0;//出错了，没有连续正确
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
		getData(dataFile);//进入getData之后就不出来了
	}
	
	else
	{
		cout << "出错，文件打开失败！" << endl;
		exit(1);
	}
	int i;
	for (i = 0; i < DEMENSION; i++)weight[i] = 0.0;//(1)选初值w=0
	PLA();
	system("pause");

}




