#pragma once



#ifndef INCLUDE_H

#define INCLUDE_H



#include<vector>

#include<random>
#include<stack>

#include<memory>
#include<iostream>

#include<algorithm>

#include<queue>
using namespace std;


 enum state { first_search, second_search, fail_return, successfully_return_s,change_relative_fitness,clearBefore, updateGlobal  };


class pos {
public:
	int m_x;
	int m_y;
	//double m_z;


	pos() :m_x(0), m_y(0){};

	pos(int a, int b) :m_x(a), m_y(b) {};

	void set(int x, int y) {
		m_x = x;
		m_y = y;
	}
	friend bool operator==(const pos & p1, const pos & p2) {
		return p1.m_x == p2.m_x&&p1.m_y == p2.m_y;

	}
	pos& operator=(const pos & p1) {
		m_x = p1.m_x;
		m_y = p1.m_y;
		return *this;

	}

	/*pos next_i(int i)const {
	return pos(m_x + Global::next_step[i][0], m_y + Global::next_step[i][1]);
	}

	void to_next_i(int i) {
	m_x += Global::next_step[i][0];
	m_y += Global::next_step[i][1];

	}

	friend double get_dis(const pos & p1,const pos &p2) {
	return sqrt(double(p1.m_x - p2.m_x)*double(p1.m_x - p2.m_x)*Global::Rule + double(p1.m_y - p2.m_y)*double(p1.m_y - p2.m_y)*Global::Rule
	+ (p1.m_z - p2.m_z)*(p1.m_z - p2.m_z));
	}


	void set(int x, int y,double z=0) {
	m_x = x;
	m_y = y;
	m_z = z;
	}


	void set(int index) {
	m_x = index%Global::H;
	m_y = index / Global::H;
	}

	bool judge() {
	return m_x < Global::W&&m_x >= 0 && m_y >= 0 && m_y < Global::H;
	}


	int to_index() {
	return m_x + m_y* Global::H;

	}
	*/


};




class m_edge:public pos {
public:

	int m_direction = 0;
	m_edge() :pos(), m_direction(0) {};
	m_edge(int x, int y, int di) :pos(x, y), m_direction(di) {};


};

#endif // !INCLUDE_H
