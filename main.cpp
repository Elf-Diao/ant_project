




#include"m_global.h"
#include"Problem.h"



using namespace std;
#define m_gl Global::msp_global

int main() {
	m_gl->msp_mpl = new MPL();
	//m_gl->msp_problem = new Problem(50,50);
	
	
	//int stop(1);

	//cout << stop << endl;
	//cin.get();



	//MPL test1;
	
	m_gl->msp_problem.creatfoodhome(5, 7, 37, 30);

	m_gl->msp_problem.creatMap(0);

	m_gl->msp_problem.getDij();


	cout << m_gl->msp_problem.get_dij_dis() << endl;




	// test 

	bool yes = 0;




	//for (unsigned i = 1; i < 10000000; i++) {



	//	m_gl->reset_double_seed(i*100+i);

	//	cout << "seed ::" << i << endl;
	//	while (!yes) {
	//		yes = m_gl->msp_mpl->_run();
	//	}
	//	m_gl->msp_mpl->printf_result();
	//}







	for (int i = 0; i < 1000000000; i++)
	{
		m_gl->msp_mpl->_run();
	}

	m_gl->msp_mpl->printf_result();





	cin.get();
	cin.get();
	cin.get();

	return 0;
}




















//
//
//
//
//#include"m_global.h"
//#include"Problem.h"
//#include"MPL.h"
//
//int main() {
//
//
//	pos p1(0, 0), p2(45, 45);;
//
//	//cout << get_dis(p1, p2) << endl;
////
//////	Problem pro1;
////	////make_unique
////	pro1.init(0, p1, p2);
////
////	cout << pro1.get_dij_dis() << endl;
//
//
//
//	//for (int i = 0; i < 10; i++) {
//	//	cout << Global::msp_global->getDoubleRand() << endl;
//	//}
//	//Global::msp_global->reset_double_seed(0);
//	//cout << endl;
//	//for (int i = 0; i < 10; i++) {
//	//	cout << Global::msp_global->getDoubleRand() << endl;
//	//}
//	cin.get();
//	cin.get();
//	cin.get();
//
//	return 0;
//}