#pragma once

#include"local_ant.h"

class MPL {


	// attention :: point is more suitable than edge

	vector<vector<double>> mvv_phe;
	
	//ector<


	double fmax = 0;
	double fmin = 0;

	
	const double m_q1 = 0.5;// possibility to choose next point according to the matrix
	const double m_q2 = 0.9; // possibility to random choose next point



	const double m_alpha = 1;


	static int m_antNum ;
	
	vector<LocalAnt> m_ant;

	double m_dis = 0;

	unsigned m_stop_sign;

	
	vector<pos> m_total_pos;


public:


	MPL();


	void setQ(double q1, double q2) {
		q1 = m_q1;
		q2 = m_q2;
	}


	//void updatePheromeno();


	inline double get_relative_fitness(double length);

	bool _run();


	void printf_result();


	void init();



	vector<pos> & get_total_pos() {
		return m_total_pos;

	}
	
	
};