#pragma once



#include"Problem.h"

class pos;


class Global {



	default_random_engine  m_e;

	uniform_real_distribution<double> m_u_double;

	uniform_int_distribution<int> m_i_double;

public:






	Problem  msp_problem;
	MPL *  msp_mpl=0;
	//MPL msp_mpl;


	static unique_ptr<Global> msp_global;


	

	//static Global* msp_global;



	Global() :m_e(2), m_u_double(0.0, 1.0) ,msp_problem(50,50) {};

	Global(unsigned seedPro) :m_e(seedPro), m_u_double(0.0, 1.0), msp_problem(50, 50) {};

	void reset_double_seed(unsigned seed) {
		m_e.seed(seed);
	//	m_e.seed()
	}


	double getDoubleRand() {

		return m_u_double(m_e);
	}


	int getIntRand(int mi,int ma) {
		return int(m_u_double(m_e)*double(ma - mi + 1))+mi;
	}

/*
	int to_index(int x, int y) {

		return x + y* Global::H;
	}

	void to_xy(int index, int &x, int &y) {
		x = index%Global::H;
		y = index / Global::H;
	}*/
	//int 


	//void to_xyi( pos & p1, int &next) {
	//	if (next>= 4) {
	//		p1.to_next_i(next);
	//		next = 8 - next;
	//	}
	//}

};





