#pragma once


#include"MPL.h"

class Problem {
	unsigned m_map_seed;
	//vector<double> m_phe;

	vector<int> m_dij_way; // 全局最优解所经过的点

	double m_dij;

	const static double Rule;//地图与实际的比例尺

	//double get_dis(const pos & p1, const pos &p2) {
	//     return sqrt((m_map[Global::msp_global->to_index(p1.m_x, p1.m_y)] - m_map[Global::msp_global->to_index(p2.m_x, p2.m_y)]) * 
	//		 (m_map[Global::msp_global->to_index(p1.m_x, p1.m_y)] - m_map[Global::msp_global->to_index(p2.m_x, p2.m_y)]) +
	//		 (p1.m_x - p2.m_x)*(p1.m_x - p2.m_x) * 36+ (p1.m_y - p2.m_y)*(p1.m_y - p2.m_y) * 36);
	//}
	Problem();

public:





	unsigned m_w = 0;
	unsigned m_h = 0;


	const static int  next_step[8][2];

	const static double m_inf;

	pos m_home;
	pos m_food;


	const static int m_total_direction;
	



	vector<vector<double>> mvv_map;

	vector<vector<vector<double>>> mvvv_near_dis;

//	Problem():m_map(Global::W*Global::H,0){};

	Problem(unsigned w, unsigned h);

	void creatfoodhome(int x1, int y1, int x2, int y2)
	{
		m_home.set(x1, y1);
		m_food.set(x2, y2);
	}
	
	void resize(unsigned w, unsigned h) {
		m_w = w;
		m_h = h;
		mvv_map.assign(w, vector<double>(h,0));
		m_dij_way.clear();
		m_dij = 0;

		
	}

	void init(double map_seed,const pos & home,const pos & food) {
		m_home = home;
		m_food = food;
		creatMap(map_seed);
		getDij();
	}

	void creatMap(double map_seed);

	void getDij();


	double get_dij_dis() {
		return m_dij;

	}


	int to_index(const pos& p1) {
		return p1.m_x + p1.m_y*m_h;
	}


	int to_index(const m_edge& e1) {
		return e1.m_x + e1.m_y*m_h;
	}

	int to_index(int x, int y) {
		return x + y*m_h;
	}


	void indexToPos(int index, pos & p1) {
		p1.m_x = index%m_h;
		p1.m_y = index / m_h;
	}


	bool judgeFood(const pos & p1) {
		return p1 == m_food;

	}

	bool judgeHome(const pos & p1)
	{
		return p1 == m_home;
	}


	bool judge(const pos & p1) {
		return p1.m_x >= 0 && p1.m_x < m_w&&p1.m_y >= 0 && p1.m_y < m_h;

	}

	bool judge(int x, int y) {
		return x >= 0 && x < m_w&&y >= 0 && y < m_h;
	}


	bool judgeNear(const pos & p1, const pos & p2) {
		return abs(p1.m_x - p2.m_x) <= 1 && abs(p1.m_y - p2.m_y) <= 1;

	}


	bool judgeNearFood(const pos & p1) {
		return abs(p1.m_x - m_food.m_x) <= 1 && abs(p1.m_y - m_food.m_y) <= 1;
	}


	


	double getDis(const pos & p1, const pos & p2) {

		if (judge(p1) && judge(p2)) {

			

			double z1(mvv_map[p1.m_x][p1.m_y]), z2(mvv_map[p2.m_x][p2.m_y]);
			return sqrt(static_cast<double>(p1.m_x - p2.m_x)*static_cast<double>(p1.m_x - p2.m_x)*Rule + static_cast<double>(p1.m_y - p2.m_y)*static_cast<double>(p1.m_y - p2.m_y)*Rule
				+ (z1 - z2)*(z1 - z2));
		}

		else return m_inf;
	}



	double getDis(const pos & p1, int direction) {
		if(judge(p1)&&direction>=0&&direction<8)
		return mvvv_near_dis[p1.m_x][p1.m_y][direction];
		else return m_inf;
	}


	vector<vector<double>> & getMap() {
		return mvv_map;
	}

//	void run_(const pos & home,const pos & food);
	

};