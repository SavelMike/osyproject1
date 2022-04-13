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

typedef enum { inGetWait, inProcess, inDoneWait } sheetState_t;

struct sheetData
{
	ASheet sheet;
	sheetState_t state;
	condition_variable condvar;
	struct sheetData* next;
};

struct listHead
{
	struct sheetData* first;
	bool done;
	condition_variable condvar;
};

/*
 * allocate new struct sheetData, add to end of list
 */
void addSheet(struct listHead *list, ASheet &sheet) {
	struct sheetData *newSheet = new struct sheetData;

	newSheet->sheet = sheet;
	newSheet->state = inGetWait;
	newSheet->next = nullptr;

	/*
	 * add newSheet to end of list
	 * !!! critical section
	 */
	struct sheetData *head = list->first;
	if (head == nullptr) {
		/* list was empty */
		list->first = newSheet;
		return;
	}
	while (head->next) {
		head = head->next;
	}
	head->next = newSheet;
}

void removeSheet(struct listHead *list) {
	struct sheetData* next;
	next = list->first->next;
	delete(list->first);
	list->first = next;
}


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
	struct listHead* lists;
};

// TODO: CQualityControl implementation goes here
void workingThreadFunc(struct listHead* lists, int n) {
	cout << "Working thread\n";
}

void communicationThreadGetFunc(AProductionLine& line, struct listHead* sheetList) {
	cout << "Communication get\n";
	while (true) {
		ASheet s = line->getSheet();
		if (s == nullptr) {
			// Let done thread know that no more new sheets will come
			// !!! Critical section
			sheetList->done = true;
			break;
		}

		/* add ASheet to list */
		addSheet(sheetList, s);
	}
}

bool firstIsDoneable(struct listHead* list) {
	if (list->first == nullptr || list->first->state != inDoneWait) {
		return false;
	}

	return true;
}

/*
 * wait until first element on \sheetList is in state Done
 * termnate when list is empty
 */
void communicationThreadDoneFunc(AProductionLine& line, struct listHead* sheetList) {
	cout << "Communication done\n";
	while (true) {
		// Wait until first sheet
		// !!! Critical section
		while (!firstIsDoneable(sheetList)) {
//			condwait();
		}
		line->doneSheet(sheetList->first->sheet);
		removeSheet(sheetList);
	}
	
}

void CQualityControl::start(int workThreads) {
	// Allocate array of lists of struct sheetDatas
	int n = this->rollingMills.size();
	this->lists = new struct listHead[n];
	for (int i = 0; i < n; i++) {
		this->lists[i].first = nullptr;
		this->lists[i].done = false;
	}
	/*
	 * start working threads
	 */
	for (int i = 0; i < workThreads; i++) {
		this->workThrs.push_back(thread(workingThreadFunc, this->lists, n));
		
	}
	/*
	 * Start communication threads for every production mills
	 */
	int i = 0;
	for (auto & m : this->rollingMills) {
		this->comThrsGet.push_back(thread(communicationThreadGetFunc, ref(m), &this->lists[i]));
		this->comThrsDone.push_back(thread(communicationThreadDoneFunc, ref(m), &this->lists[i]));
		i++;
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
