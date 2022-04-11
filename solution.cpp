#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */ 

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

class CQualityControl
{
  public:
	static void                        checkAlgorithm                          ( ASheet                                sheet );
	void                               addLine                                 ( AProductionLine                       line );
	void                               start                                   ( int                                   workThreads );
	void                               stop                                    ( void );
  private:
	vector<AProductionLine> rollingMills;
	vector<thread> workThrs;
	vector<thread> comThrsGet;
	vector<thread> comThrsDone;
	

};

// TODO: CQualityControl implementation goes here
void workingThreadFunc(void) { }

void communicationThreadGetFunc(AProductionLine& line) {

}
void communicationThreadDoneFunc(AProductionLine& line) {

}

void CQualityControl::start(int workThreads) {
	/*
	 * start working threads
	 */
	for (int i = 0; i < workThreads; i++) {
		this->workThrs.push_back(thread(workingThreadFunc)); 
	}
	/*
	 * Start communication threads for every production mills
	 */
	for (auto & m : this->rollingMills) {
		this->comThrsGet.push_back(thread(communicationThreadGetFunc, ref(m)));
		this->comThrsDone.push_back(thread(communicationThreadDoneFunc, ref(m)));
	}
}

void CQualityControl::stop(void) {
	for (auto& w : this->workThrs) {
		w.join();
	}
	for (auto& g : this->comThrsGet) {
		g.join();
	}
	for (auto& d : this->comThrsDone) {
		d.join();
	}
}

void CQualityControl::checkAlgorithm (ASheet sheet) {
	;
}

void CQualityControl::addLine (AProductionLine line) {
	this->rollingMills.push_back(line);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                main                                    ( void )
{
  CQualityControl control;
  AProductionLineTest line = std::make_shared<CProductionLineTest> ();
  control . addLine ( line );
  control . start ( 4 );
  control . stop  ();
  if ( ! line -> allProcessed () )
    throw std::logic_error ( "(some) sheets were not correctly processsed" );
  return 0;  
}
#endif /* __PROGTEST__ */ 
