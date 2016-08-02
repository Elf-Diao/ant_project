#pragma once



#include"include.h"




class LocalAnt {




//	static int m_memory_limit;

	vector<vector<double>> mvv_distance_from_home;//the shortest distance from home point to current point
	vector<vector<double>> mvv_distance_from_food; // the shortest distance from food point to current point




//	int m_before_direction=-1;



	// best solution in history
	stack<pos> m_best; // the points along the current  best way


	double m_best_dis = 0;// best solution distance
	double m_fi_best = 0;//relative fitness




	// current information




	vector<vector<bool>> mvv_visited;

	pos m_pos;

	state m_state;




	stack<pos> m_current;

	double m_current_dis = 0;
	double m_fi_after;
	//double m_phe_after = 0;

	int m_step = 0;


	bool m_change = 0;



	// first search to find a feasible way


	queue<pos> m_first_way;

	//mvv_in_queue;

	vector<vector<bool>> mvv_in_queue;





	bool isInNeighborhood(const pos & p1);

	bool inInNeighborhood_v2(const pos & p1);


	



	// remember the points along the best way

	vector<vector<bool>>  mvv_in_best_way;



	



public:

	void init();




	void reset();

	void reset_from_food();

	void reset_start_from_home();



	//bool step(int direction);// the ant next step 

	void add_point(int direction);// i

	bool add_point(int direction, int * next);

	void add_point(const pos & p1);



	inline bool isNearFood();


	inline bool isNearFood(const pos & p1);

	bool clearGlobalMatrix(vector<vector<double>>& matrix);// clear the pheromone left before;


	bool updateGlobalMatrix(vector<vector<double>> & matrix);


	bool random_search();// randomly search next unvisited point  ,0 means out of memory


	void random_search_queue();


	bool blocked_up();// nothing in it


	//bool searchNextPoint

	bool random_search_neighorhood();

	bool random_search_neighborhood_v2();


	bool random_search_neighborhood_v3();




	void rectangle_visit(int next);






	void add_point_to_stack(int next);
	//bool isMemoryFull()

	bool selectNextPointGreedy();


	


	

	bool selectNextPointMatrixNeighbor(vector<vector<double>>& matrix);
	
	//bool selectNextPointRandom();

	
	bool successfully_return();



	int successfully_return_v2();// 0 means on the way, -1 the distance is longer than the best one ,1 means find a better way


	bool fail_return();



	void updateHomeDis();
	void updateFoodDis();

	bool better_than_history() {
		return m_current_dis < m_best_dis;
	}


	state & get_state() {
		return m_state;

	}


	bool& get_change(){
		return m_change;

	}

	double get_best_dis()const 
	{
		return m_best_dis;
	}
	double get_current_dis()const
	{
		return m_current_dis;
	}

	double & get_fi() {
		return m_fi_after;

	}


	pos & get_pos() {
		return m_pos;
	}
};