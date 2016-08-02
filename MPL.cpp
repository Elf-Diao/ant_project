#include"MPL.h"



#include"m_global.h"

//extern unique_ptr<Global>  Global::msp_global;

//extern Global * msp_global;

int MPL::m_antNum = 20;

#define m_gp Global::msp_global->msp_problem

MPL::MPL():fmax(0),fmin(m_gp.m_inf),mvv_phe(m_gp.m_w,vector<double>(m_gp.m_h,0.01)),m_ant(m_antNum){
	m_dis = m_gp.m_inf;
	for (int i = 0; i < m_antNum; i++)
	{
		m_ant[i].init();
	}

	
	
	
	m_stop_sign = 0;
	for (int i = 0; i < m_antNum; i++)
	{
		m_stop_sign = m_stop_sign | (1 << i);

	}
}

bool MPL::_run()
{

	m_total_pos.clear();

	for (int i = 0; i < m_antNum; i++)
	{
		if (m_dis > m_ant[i].get_best_dis())
		{
			m_dis = m_ant[i].get_best_dis();
		}



		if (m_ant[i].get_state() == first_search)
		{
			m_ant[i].random_search_queue();
		}

		else if (m_ant[i].get_state() == second_search){


			
			

			double choose(Global::msp_global->getDoubleRand());

			if (choose < m_q1) {
				if (m_ant[i].selectNextPointMatrixNeighbor(mvv_phe))continue;
				choose += m_q1;
			}
			if (choose < m_q2) {
				if(m_ant[i].random_search_neighborhood_v3())continue;

			}

			m_ant[i].selectNextPointGreedy();

			//m_ant[i].

		//	m_ant[i].selectNextPointGreedy();

		//	m_ant[i].random_search_neighborhood_v3();


			m_ant[i].selectNextPointMatrixNeighbor(mvv_phe);


		}

		else if (m_ant[i].get_state() == change_relative_fitness)
		{

		//	return 1;
			m_ant[i].get_fi() = get_relative_fitness(m_ant[i].get_current_dis());
			m_ant[i].get_state() = clearBefore;
			int change(m_ant[i].get_change());
			m_ant[i].get_change() = 0;
			m_stop_sign = m_stop_sign&(change << i);// stop criteria 

			
		}

		else if (m_ant[i].get_state() == clearBefore)
		{
			m_ant[i].clearGlobalMatrix(mvv_phe);
		}

		else if (m_ant[i].get_state() == updateGlobal)
		{
			m_ant[i].updateGlobalMatrix(mvv_phe);
		}

		else if(m_ant[i].get_state()==successfully_return_s) {
			if (m_ant[i].successfully_return_v2() == -1) {
				int change(m_ant[i].get_change());
				m_ant[i].get_change() = 0;
				m_stop_sign = m_stop_sign&(change << i);// stop criteria 


			}
		}
		else {
			m_ant[i].fail_return();
		}
		m_total_pos.push_back(m_ant[i].get_pos());
	}

	return 0;
}


double MPL::get_relative_fitness(double length) {
	if (fmax < length)fmax = length;
	if (fmin > length)fmin = length;
	return 2 * (1.0 / (1 + exp(-m_alpha*((fmax - length + 1) / (fmax - fmin + 1))))) - 1;
}

void MPL::printf_result()
{

	m_dis = m_gp.m_inf;
	//for (int i = 0; i < m_antNum; i++)
	//{
	//	if (m_dis > m_ant[i].get_best_dis())
	//	{
	//		m_dis = m_ant[i].get_best_dis();
	//	}

	//}


	for (int i = 0; i < m_antNum; i++)
	{
		if (m_dis > m_ant[i].get_current_dis())
		{
			m_dis = m_ant[i].get_current_dis();
		}

	}


	cout << "best  distance" << m_dis << endl;

}

void MPL::init()
{

	fmax = 0;
	fmin = m_gp.m_inf;
	mvv_phe.assign(m_gp.m_w, vector<double>(m_gp.m_h, 0));
	m_dis = m_gp.m_inf;
	for (int i = 0; i < m_antNum; i++)
	{
		m_ant[i].init();
	}
}




