#include"Problem.h"


#include"m_global.h"



#include"m_math.h"


//#define m_gp Global::msp_global->msp_problem

const  int Problem::next_step[8][2] = { { -1,-1 },{ -1,0 },{ -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 } };

const double Problem::m_inf = 1e7;


const double Problem::Rule = 36;

const int Problem::m_total_direction = 8;




Problem::Problem() {};


Problem::Problem(unsigned w, unsigned h) :m_w(w), m_h(h), mvv_map(w, vector<double>(h, 0)) {
	//mvvv_near_dis.assign(m_w, vector<double>(m_h, vector<double>(8, 0)));
	mvvv_near_dis.resize(m_w);
	for (unsigned i = 0; i < m_w; i++) {
		mvvv_near_dis[i].assign(m_h, vector<double>(8, 0));
	}
};
void Problem::creatMap(double map_seed) {
	

	for (int x = 0; x < m_w; ++x) {
		for (int y = 0; y < m_h;++y) {
			mvv_map[x][y] = m_ofNoise(x * 0.05, y * 0.05, map_seed * 0.5) * 100;
		}
	}


	// init the distance between two adjacent
	pos temp;
	for (int x = 0; x < m_w; x++) {// init the distance between two adjacent
		for (int y = 0; y < m_h; y++) {
			for (int i = 0; i < 8; i++) {
				temp.set(x + next_step[i][0], y + next_step[i][1]);
				if (judge(temp)) {
					mvvv_near_dis[x][y][i] = getDis(pos(x, y), temp);
				}
				else mvvv_near_dis[x][y][i] = m_inf;
			}
		}
	}
	




	//getDij();
	//for (int x = 0; x < m_w; x++) {
	//	mvvv_near_dis[x].assign(m_h, vector<double>(8, 0));

	//	for (int y = 0; y < m_h; y++) {
	//		for (int i = 0; i < 8; i++) {
	//			if (judge(x + next_step[i][0], y + next_step[i][1])){
	//				
	//			}
	//		}
	//	}
	//}

}



void Problem::getDij() {

	int size(m_w*m_h);
	vector<bool> visited(size, 0);
	double inf(1e8);
	vector<double> dis(size, inf);

	vector<int> before(size);

	
	dis[to_index(m_home)] = 0;

	pos temp;
	pos temp2;
	while (1) {
		double mi = inf;
		int next(-1);
		for (int i = 0; i < size; ++i) {
			if (!visited[i]&&dis[i] < mi) {
				mi = dis[i];
				next = i;
			}
		}

		if (next == -1) {
			m_dij = -1;
			break;
		}
		if (next == to_index(m_food)) {
			m_dij = dis[next];
			break;
		}
		visited[next] = 1;
		indexToPos(next, temp);
	//	temp.set(next);
		double newdis(0);
		for (int i = 0; i < 8; i++) {
			temp2 = temp;
			temp2.m_x += next_step[i][0];
			temp2.m_y += next_step[i][1];
			


			if(judge(temp2)&&!visited[to_index(temp2)]){
			//	temp2.m_z = m_map[to_index(temp2)];
				newdis = getDis(temp, temp2);
				if (dis[to_index(temp2)]>dis[to_index(temp)] + newdis) {
					dis[to_index(temp2)] = dis[to_index(temp)] + newdis;
					before[to_index(temp2)] = to_index(temp);

				}
			}
		}

	}

	m_dij_way.clear();
	int first(to_index(m_food)), last(to_index(m_home));
	m_dij_way.push_back(first);
	while (1) {
		first = before[first];
		m_dij_way.push_back(first);
		if (first == last)break;
	}

}