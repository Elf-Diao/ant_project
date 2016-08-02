#pragma once

#include"m_global.h"
struct TestNode {


	unsigned m_w;
	unsigned m_h;


	unsigned m_seed;
	unsigned m_map_seed;
	double m_dij;
	double m_best;

	long long m_step;
	
	double m_error;

	friend bool operator<(const TestNode &t1, const TestNode &t2) {
		return t1.m_dij < t2.m_dij;

	}


};



class Test {
	vector<TestNode> m_memory;

	vector<pos> m_home;
	vector<pos> m_food;

	void sortTest() {
		sort(m_memory.begin(), m_memory.end());
	}


public:




	//void handle(unsigned num,double map_seed=0,unsigned home_seed=0);// 测试的数据个数
	
};