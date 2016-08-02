

#include"local_ant.h"

#include"m_global.h"

//extern unique_ptr<Global>  Global::msp_global;
//

#define m_gp Global::msp_global->msp_problem

//int LocalAnt::m_memory_limit = 1000;


bool LocalAnt::isInNeighborhood(const pos & p1)
{

	if (!m_gp.judge(p1))return 0;
	pos temp;
	for (int i = 0; i < 8; i++) {
		temp.set(p1.m_x + m_gp.next_step[i][0], p1.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y] && mvv_distance_from_food[temp.m_x][temp.m_y]!=m_gp.m_inf)
			return true;
	}
	
	return false;
}

bool LocalAnt::inInNeighborhood_v2(const pos & p1)
{
	pos temp;

	for (int i = 0; i < 8; i++) {
		temp.set(p1.m_x + m_gp.next_step[i][0], p1.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y] && mvv_in_best_way[temp.m_x][temp.m_y])
			return true;
	}
	return false;
}

void LocalAnt::init() {
	//m_pos = m_gp.m_home;
	mvv_distance_from_home.assign(m_gp.m_w, vector<double>(m_gp.m_h, m_gp.m_inf));
	mvv_distance_from_food.assign(m_gp.m_w, vector<double>(m_gp.m_h, m_gp.m_inf));
	mvv_visited.assign(m_gp.m_w,vector<bool>(m_gp.m_h,0));

	m_pos = m_gp.m_home;

	m_best_dis = m_gp.m_inf;

	m_state = first_search;
	while (!m_first_way.empty())m_first_way.pop();

//	m_first_way.push(m_pos);

	mvv_in_queue.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));


	mvv_distance_from_home[m_gp.m_home.m_x][m_gp.m_home.m_y] = 0;
	mvv_distance_from_food[m_gp.m_food.m_x][m_gp.m_food.m_y] = 0;

	//mvv_visited[m_pos.m_x][m_pos.m_y] = 1;


	mvv_in_best_way.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));


	
	
}




void LocalAnt::reset() {
	mvv_visited.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));
	m_pos = m_gp.m_home;

	m_current_dis = 0;
	m_step = 0;
	//m_change = 0;
	
}

void LocalAnt::reset_from_food()
{
	m_current_dis = 0;

	while (!m_current.empty())
		m_current.pop();
}

void LocalAnt::reset_start_from_home()
{
	mvv_visited.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));
	m_pos = m_gp.m_home;
	m_current_dis = 0;
//	m_change = 0;
//	while (!m_current.empty())m_current.pop();

	
}


void LocalAnt::add_point(int direction)
{
	m_current_dis += m_gp.getDis(m_pos, direction);
	m_pos.m_x += m_gp.next_step[direction][0];
	m_pos.m_y += m_gp.next_step[direction][1];
	mvv_visited[m_pos.m_x][m_pos.m_y] = 1;

	if (mvv_distance_from_home[m_pos.m_x][m_pos.m_y] > m_current_dis) {
		m_change = 1;
		mvv_distance_from_home[m_pos.m_x][m_pos.m_y] = m_current_dis;

		updateHomeDis();
	}
	else {
		m_current_dis = mvv_distance_from_home[m_pos.m_x][m_pos.m_y];
	}


	//m_current_dis += m_gp.getDis(m_pos, direction);
	//m_pos.m_x += m_gp.next_step[direction][0];
	//m_pos.m_y += m_gp.next_step[direction][1];



	//if (!m_gp.judge(m_pos))return false;
	//mvv_visited[m_pos.m_x][m_pos.m_y] = 1;
	////m_current.push(m_pos);

	//

	//{
	//	
	//	// update neighbor hood;
	//	pos temp;
	//	double temp_dis;
	//	if (mvv_distance_from_home[m_pos.m_x][m_pos.m_y] > m_current_dis) {
	//		m_change = 1;
	//		mvv_distance_from_home[m_pos.m_x][m_pos.m_y] = m_current_dis;

	//		updateHomeDis();
	//		//for (int i = 0; i < 8; i++) {
	//		//	temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
	//		//	if (m_gp.judge(temp)) {
	//		//		temp_dis = m_current_dis + m_gp.mvvv_near_dis[m_pos.m_x][m_pos.m_y][i];
	//		//		if (temp_dis < mvv_distance_from_home[temp.m_x][temp.m_y]) {
	//		//			mvv_distance_from_home[temp.m_x][temp.m_y] = temp_dis;
	//		//		}
	//		//	}
	//		//}
	//	}
	//	else {
	//		m_current_dis = mvv_distance_from_home[m_pos.m_x][m_pos.m_y];
	//	}
	//	return true;
	//}
}
bool LocalAnt::add_point(int direction, int * next)
{
	m_current_dis += m_gp.getDis(m_pos, direction);
	m_pos.m_x += m_gp.next_step[direction][0];
	m_pos.m_y += m_gp.next_step[direction][1];



	if (!m_gp.judge(m_pos))return false;
	mvv_visited[m_pos.m_x][m_pos.m_y] = 1;




	{

		// update neighbor hood;
		pos temp;
		double temp_dis;
		if (mvv_distance_from_home[m_pos.m_x][m_pos.m_y] > m_current_dis) {
			m_change = 1;
			mvv_distance_from_home[m_pos.m_x][m_pos.m_y] = m_current_dis;
		
			for (int i = 0; i < 8; i++) {
				if (next[i]) {
					temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
					temp_dis = m_current_dis + m_gp.mvvv_near_dis[m_pos.m_x][m_pos.m_y][i];
					if (m_gp.judge (temp)&&(temp_dis < mvv_distance_from_home[temp.m_x][temp.m_y])){
						mvv_distance_from_home[temp.m_x][temp.m_y] = temp_dis;
					}
					
				}
			}
		}
		else {
			m_current_dis = mvv_distance_from_home[m_pos.m_x][m_pos.m_y];
		}
		return true;
	}



}
void LocalAnt::add_point(const pos & p1)
{
	
	m_current_dis += m_gp.getDis(m_pos, p1);
	m_pos = p1;
	mvv_visited[m_pos.m_x][m_pos.m_y] = 1;

	if (mvv_distance_from_home[m_pos.m_x][m_pos.m_y] > m_current_dis) {
		m_change = 1;
		mvv_distance_from_home[m_pos.m_x][m_pos.m_y] = m_current_dis;

		updateHomeDis();
	}
	else {
		m_current_dis = mvv_distance_from_home[m_pos.m_x][m_pos.m_y];
	}
	
}


bool LocalAnt::isNearFood() {
	return m_gp.judgeNearFood(m_pos);
}

inline bool LocalAnt::isNearFood(const pos & p1)
{
	return m_gp.judgeNearFood(p1);
//	return false;
}

bool LocalAnt::clearGlobalMatrix(vector<vector<double>>& matrix) {

	if (m_best.empty()) {
		m_state = updateGlobal;
		m_best =m_current;
		return 1;
	}

	else {
		
		matrix[m_best.top().m_x][m_best.top ().m_y] -= m_fi_best;
		mvv_in_best_way[m_best.top().m_x][m_best.top().m_y] = 0;
		m_best.pop();

		return 0;

	}
}

bool LocalAnt::updateGlobalMatrix(vector<vector<double>>& matrix) {

	if (m_current.empty()) {
		m_state = second_search;
		m_fi_best = m_fi_after;
		m_best_dis = m_current_dis;
		reset_start_from_home();

		return 1;
	}

	else {

		matrix[m_current.top().m_x][m_current.top ().m_y]+= m_fi_after;
		mvv_in_best_way[m_current.top().m_x][m_current.top().m_y] = 1;
		m_current.pop();
		return 0;

	}
}

bool LocalAnt::random_search()
{


//	updateHomeDis();

	//Global::msp_global->getDoubleRand();

	double randNum(Global::msp_global->getDoubleRand());

	int next[8] = { 0,0 };

	int total_next = 0;
	pos temp;
	for (int i = 0; i < 8; i++) {
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y]) {
			total_next++;
			next[i] = 1;
		}
	}

	if (total_next == 0)return false;
	else {
		randNum *= double(total_next);
		randNum = int(randNum);
		total_next = -1;
		int next_step = -1;
		//int i;
		for (int i = 0; i < 8; i++) {
			if (next[i]) {
				total_next++;
				if (total_next >= randNum) {
					next_step = i;
					break;
				}
			}
		}
		if (next_step == -1)return false;
		if (add_point(next_step, next)) {
			if (m_gp.judgeFood(m_pos))
			{
					m_state = successfully_return_s;
					reset();
					return true;
				
			}

			else {
				m_state = first_search;
			}
		}
		else return false;
		
	//	for (int i = 0; i < )
	}
	
	return 0;
}



// this one is better 
void LocalAnt::random_search_queue()
{



	if (m_gp.judgeFood(m_pos))
	{
		m_state = successfully_return_s;

		mvv_visited.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));
		reset_from_food();
		return;

	}

	if (m_gp.judgeNearFood(m_pos)) {
		add_point(m_gp.m_food);
		mvv_visited.assign(m_gp.m_w, vector<bool>(m_gp.m_h, 0));

		m_state = successfully_return_s;
		reset_from_food();
		return;
	}

	pos temp_next;

	int next[8] = { 0 };

	int total(0);
	
	for (int i = 0; i < m_gp.m_total_direction; i++)
	{
		temp_next.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp_next)&&!mvv_visited[temp_next.m_x][temp_next.m_y])
		{
			next[i] = 1;
			total++;


			if (!mvv_in_queue[temp_next.m_x][temp_next.m_y]&&i)
			{
				m_first_way.push(temp_next);
				mvv_in_queue[temp_next.m_x][temp_next.m_y] = 1;

			}

		}
	}



	if (total == 0) {
		pos current(m_first_way.front());
		m_first_way.pop();

		while (mvv_visited[current.m_x][current.m_y]) {
			current = m_first_way.front();
			m_first_way.pop();

		}
		add_point(current);

	}


	else {


		double randNum(Global::msp_global->getDoubleRand());

		randNum *= double(total);
		total = 0;

		randNum = int(randNum);
		int i;
		for (i = 0; i < 8; i++)
		{
			if (next[i]) {
				total++;
				if (total >= randNum) {
					break;
				}
			}
		}

		add_point(i);

	}
}


// attention blank ::
bool LocalAnt::blocked_up()
{

	
	return false;
}
bool LocalAnt::random_search_neighorhood()
{

	int next[8] = { 0,0 };
	int total_next = 0;
	pos temp;
	for (int i = 0; i < 8; i++) {
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y] && isInNeighborhood(temp))
		{
			total_next++;
			next[i] = 1;
		}
	}
	
	if (total_next == 0) {
		return false;
	}
	else {
		double randNum (Global::msp_global->getDoubleRand());
		randNum *= total_next;
		randNum = int(randNum);
		total_next = -1;
		int temp_next;
		for (int i = 0; i < 8; i++) {
			if (next[i])
			{
				total_next++;
				if (total_next >= randNum)
				{
					temp_next = i;
					break;
				}
			}
		}
		add_point(temp_next);
		if (m_gp.judgeFood(m_pos))
		{
			m_state = successfully_return_s;
			reset_from_food();
			//reset();
			return true;
		}

		if (m_gp.judgeNearFood(m_pos))
		{
			add_point(m_gp.m_food);
			m_state = successfully_return_s;
			reset_from_food();
			return true;
		}

		return true;
		
		
	}
}

bool LocalAnt::random_search_neighborhood_v2()
{

	int next[8] = { 0,0 };
	int total_next = 0;
	pos temp;
	for (int i = 0; i < 8; i++) {
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y] && inInNeighborhood_v2(temp))
		{
			total_next++;
			next[i] = 1;
		}
	}

	if (total_next == 0) {
		return false;
	}
	else {
		double randNum(Global::msp_global->getDoubleRand());
		randNum *= total_next;
		randNum = int(randNum);
		total_next = -1;
		int temp_next;
		for (int i = 0; i < 8; i++) {
			if (next[i])
			{
				total_next++;
				if (total_next >= randNum)
				{
					temp_next = i;
					break;
				}
			}
		}
		add_point(temp_next);
		if (m_gp.judgeFood(m_pos))
		{
			m_state = successfully_return_s;
			reset_from_food();
			//reset();
			return true;
		}

		if (m_gp.judgeNearFood(m_pos))
		{
			add_point(m_gp.m_food);
			m_state = successfully_return_s;
			reset_from_food();
			return true;
		}

		return true;


	}
}

bool LocalAnt::random_search_neighborhood_v3()
{

	double dis(m_gp.m_inf);
	//	double temp;
	pos next_pos;

	int possibility[8] = {0};

	int total_next = 0;

	for (int i = 0; i < 8; i++) {

		next_pos.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (isInNeighborhood(next_pos)&&!mvv_visited[next_pos.m_x][next_pos.m_y]){
		//	mvv_visited[next_pos.m_x][next_pos.m_y] = 1;
			possibility[i] = 1;
			total_next++;
		}
	}

	int next=-1;


	double randNum(Global::msp_global->getDoubleRand());

	randNum *= double(total_next);
	total_next = 0;

	randNum = int(randNum);
	for (int i = 0; i < 8; i++)
	{
		if (possibility[i]) {
			total_next++;
			if (total_next >= randNum) {
				next = i;
				break;
			}
		}
	}




	if (next==-1) {
		//reset_start_from_home();
		//m_state = second_search;
		return false;

	}
	else {


		// rectangle_visit is a way to shorten the way,but the result is not too good
	//	rectangle_visit(next);
		


		add_point(next);



		if (m_gp.judgeFood(m_pos))
		{
			m_state = successfully_return_s;
			reset_from_food();
			//reset();
			return true;
		}

		if (m_gp.judgeNearFood(m_pos))
		{
			add_point(m_gp.m_food);
			m_state = successfully_return_s;
			reset_from_food();
			return true;
		}
		return true;
	}


	return true;
}

void LocalAnt::rectangle_visit(int next)
{

	int ans = -1;


	double shorten_way(m_gp.getDis(m_pos,next));

	int near((next + 1) % 8);
	pos dir(m_pos.m_x + m_gp.next_step[next][0], m_pos.m_y + m_gp.next_step[next][1]);
	
	pos temp(m_pos.m_x + m_gp.next_step[near][0], m_pos.m_y + m_gp.next_step[near][1]);

	double newdis;

	if (m_gp.judge(temp)) {
		newdis=(mvv_distance_from_home[temp.m_x][temp.m_y] + m_gp.getDis(temp, dir));
		if (newdis < shorten_way) {
			newdis = shorten_way;
			ans = near;
		}

			mvv_visited[temp.m_x][temp.m_y] = 1;

	}

	near = (next + 7 - 1) % 8;
	temp.set(m_pos.m_x + m_gp.next_step[near][0], m_pos.m_y + m_gp.next_step[near][1]);
	if (m_gp.judge(temp)) {
		newdis = m_gp.getDis(m_pos, near) + m_gp.getDis(temp, dir);
		if (newdis < shorten_way) {
			newdis = shorten_way;
			ans = near;
		}


			mvv_visited[temp.m_x][temp.m_y] = 1;

	}

	if (ans!=-1) {
		temp.set(m_pos.m_x + m_gp.next_step[ans][0], m_pos.m_y + m_gp.next_step[ans][1]);
		add_point(temp);

	}


}





void LocalAnt::add_point_to_stack(int direction)
{
	m_current_dis += m_gp.getDis(m_pos, direction);
	m_pos.m_x += m_gp.next_step[direction][0];
	m_pos.m_y += m_gp.next_step[direction][1];
	//mvv_visited[m_pos.m_x][m_pos.m_y] = 1;
	m_current.push(m_pos);

}

bool LocalAnt::selectNextPointGreedy() {
	
	//bool isfind = 0;
	
	int next(-1);
	double dis (m_gp.m_inf);
//	double temp;
	pos next_pos;
	for (int i = 0; i < 8; i++) {
		//if(!mvv_visited[][])
		
		next_pos.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(next_pos) && !mvv_visited[next_pos.m_x][next_pos.m_y]) {

			if (mvv_distance_from_food[next_pos.m_x][next_pos.m_y] < dis) {
				next = i;
				dis = mvv_distance_from_food[next_pos.m_x][next_pos.m_y];
			}
		}
	}

	if (dis == m_gp.m_inf) {
	//	reset_from_food();
		reset_start_from_home();
		m_state = second_search;
		return false;

	}
	else {

		add_point(next);
		if (m_gp.judgeFood(m_pos))
		{
				m_state = successfully_return_s;
				reset_from_food();
				//reset();
				return true;
		}

		if (m_gp.judgeNearFood(m_pos))
		{
			add_point(m_gp.m_food);
			m_state = successfully_return_s;
			reset_from_food();
			return true;
		}

	}

	return false;

}







//bool LocalAnt::selectNextPointMatrixNeighbor(vector<vector<double>>& matrix)
//{
//	
//
//	double next[8] = {0,0};
//	pos temp;
//	double total_next = 0;
//	for (int i = 0; i < 8; i++) {
//		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y +m_gp.next_step[i][1]);
//		if (m_gp.judge(temp) && !mvv_visited[temp.m_x][temp.m_y] && isInNeighborhood(temp))
//		{
//			next[i] = matrix[temp.m_x][temp.m_y];
//			total_next += next[i];
//		}
//	}
//	double randNum(Global::msp_global->getDoubleRand());
//	randNum *= total_next;
//	total_next = 0;
//	int choose = -1;
//	for (int i = 0; i < 8; i++)
//	{
//		total_next += next[i];
//		if (total_next >= randNum) {
//			choose = i;
//			break;
//		}
//	}
//
//	if (choose == -1||!add_point(choose))return false;
//	else {
//		if (m_gp.judgeFood(m_pos))
//		{
//
//			if (m_change) {
//				m_state = successfully_return_s;
//				reset();
//			}
//			else {
//				m_state = second_search;
//				reset();
//
//			}
//			
//		}
//
//		m_state = second_search;
//		reset();
//		return true;
//	}
//	m_state = second_search;
//	reset();
//
//	//return false;
//}

bool LocalAnt::selectNextPointMatrixNeighbor(vector<vector<double>>& matrix)
{

	double dis(m_gp.m_inf);
	//	double temp;
	pos next_pos;

	double possibility[8] = { 0 };

	double total_next = 0;

	for (int i = 0; i < 8; i++) {

		next_pos.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (isInNeighborhood(next_pos) && !mvv_visited[next_pos.m_x][next_pos.m_y]) {
			//	mvv_visited[next_pos.m_x][next_pos.m_y] = 1;
			possibility[i] = matrix[next_pos.m_x][next_pos.m_y];
			total_next+=possibility[i];
		}
	}

	int next = -1;


	double randNum(Global::msp_global->getDoubleRand());

	randNum *= total_next;
	total_next = 0;

	for (int i = 0; i < 8; i++)
	{
		if (possibility[i]) {
			total_next+=possibility[i];
			if (total_next >= randNum) {
				next = i;
				break;
			}
		}
	}




	if (next == -1) {
		//	reset_from_food();
	//	reset_start_from_home();
	//	m_state = second_search;
		return false;

	}
	else {

		//	rectangle_visit(next);


		add_point(next);



		if (m_gp.judgeFood(m_pos))
		{
			m_state = successfully_return_s;
			reset_from_food();
			//reset();
			return true;
		}

		if (m_gp.judgeNearFood(m_pos))
		{
			add_point(m_gp.m_food);
			m_state = successfully_return_s;
			reset_from_food();
			return true;
		}
		return true;
	}


	return false;
}

bool LocalAnt::successfully_return()
{

	updateFoodDis();
	pos temp;
	double dis (m_gp.m_inf);
	int next(-1);
	for (int i = 0; i < 8; i++)
	{
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
			if (m_gp.judge(temp)&&dis > mvv_distance_from_home[temp.m_x][temp.m_y])
			{
				next = i;
				dis = mvv_distance_from_home[temp.m_x][temp.m_y];
			}
	}


	add_point_to_stack(next);
	

	if (m_gp.judgeHome(m_pos))
	{
		if (better_than_history())
		{
			m_state = change_relative_fitness;
			reset();
		}


		else {
			m_state = second_search;
			while (!m_current.empty())m_current.pop();
			m_current_dis = 0;
			m_fi_after = 0;
			m_step = 0;
			//m_change = 0;

		}
		m_state = second_search;
		reset();
		return true;
	}
	m_state = second_search;
	reset();
	return false;
}

int LocalAnt::successfully_return_v2()
{
	updateFoodDis();
	mvv_visited[m_pos.m_x][m_pos.m_y] = 1;
	pos temp;
	double dis(m_gp.m_inf);
	int next(-1);
	for (int i = 0; i < 8; i++)
	{
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp) && dis > mvv_distance_from_home[temp.m_x][temp.m_y]&&!mvv_visited[temp.m_x][temp.m_y])
		{
			next = i;
			dis = mvv_distance_from_home[temp.m_x][temp.m_y];
		}
	}
	if (next == -1) {
		m_state = second_search;
		reset_start_from_home();
		return -1;
	}

	add_point_to_stack(next);

	if (dis == 0) {// means is in home

		if (m_current_dis < m_best_dis)// means find a better way than history
		{
			m_state = change_relative_fitness;
			m_change = 1;

			
			return 1;

		}

		else {
			m_state = second_search;
			reset_start_from_home();
			return -1;

		}


		return true;

	}


	return 0;
}

bool LocalAnt::fail_return()
{

	//vector<vector<bool>> mvv_visited;
	if (!m_best.empty())
	{
		m_state = second_search;

	}
	else m_state = first_search;


	reset();



	return false;
}

void LocalAnt::updateHomeDis()
{
	pos temp;
	//bool change(0);
	for (int i = 0; i < m_gp.m_total_direction; i++)
	{
		
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp)&&mvv_distance_from_home[temp.m_x][temp.m_y]>m_gp.getDis(m_pos, i)+m_current_dis)
		{
			mvv_distance_from_home[temp.m_x][temp.m_y] = m_gp.getDis(m_pos, i) + m_current_dis;
			m_change = 1;
		}
	}
	//return change;
}

void LocalAnt::updateFoodDis()
{

	pos temp;
	//bool change(0);

	for (int i = 0; i < 8; i++)
	{
		temp.set(m_pos.m_x + m_gp.next_step[i][0], m_pos.m_y + m_gp.next_step[i][1]);
		if (m_gp.judge(temp)&&mvv_distance_from_food[temp.m_x][temp.m_y]>m_gp.getDis(m_pos, i) + m_current_dis)
		{
			mvv_distance_from_food[temp.m_x][temp.m_y] = m_gp.getDis(m_pos, i) + m_current_dis;
			m_change = 1;
		}
	}
	//return false;
}
