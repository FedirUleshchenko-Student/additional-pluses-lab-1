#include "DS.h"
#include <numeric>
#include <algorithm>
#include <exception>
#include <random>

#include <format>
#include <iostream>

using namespace std;

DS::DS(vector<return_type> list, size_type task_cnt) :
	_task(list), _varSize(task_cnt), _currVar(0), _vars(getC(list.size(), task_cnt)) {
	iota(_vars.begin(), _vars.end(), 1); // start from 1

	// FOR FUTURE USE
	// 
	//shuffle(_vars.begin(), _vars.end(), mt19937(random_device()()));
}

DS::pos_type DS::getC(pos_type n, pos_type k) {
	if (k < 0 || k > n) return 0;
	if (k == 0 || k == n) return 1;

	// C(n, k) == C(n, n - k)
	if (k > n / 2) k = n - k;

	pos_type result = 1;
	for (pos_type i = 1; i <= k; i++) {
		result *= (n - k + i);
		result /= i;
	}

	return result;
}

// returns first left pointer that MOVES
// Count starts from 1
DS::size_type DS::searchMovePoint
(size_type tasksRemained, size_type pointersRemained, const pos_type& pos) const {
	size_type l = 0, r = pointersRemained + 1;
	size_type t;
	while (l + 1 < r) {
		t = midpoint(l, r);

		// if vars starts from 0 -> <=
		if (((pointersRemained - t) ? getC(tasksRemained - t, pointersRemained - t) : 0)
			< pos) r = t;
		else l = t;
	}
	return r;
}

// returns the amount of positions to move right the movable pointer
// 
// movable task DOES NOT count in pointersRemained
// starting position of movable task COUNTS in tasksRemained variable
DS::size_type DS::searchMovePosition
(size_type tasksRemained, size_type pointersRemained, pos_type& pos) const {
	if (pointersRemained == 0) {
		return pos - 1;
	}

	size_type l = 0;
	size_type r = tasksRemained - 1;
	size_type t;

	size_type maxVar = getC(tasksRemained, pointersRemained + 1);

	while (l + 1 < r) {
		t = midpoint(l, r);

		// sum of skipped vars:
		//	k+1				 k		k
		// C	=  SUM[from C   to C  ]
		//	n+1				 k		n
		if (maxVar - getC(tasksRemained - t, pointersRemained + 1 - t)
			<= pos) l = t;
		else r = t;
	}

	pos -= maxVar - getC(tasksRemained - l, pointersRemained + 1);
	//pos--;

	return l;
}

DS::return_type DS::operator()() {
	pos_type id = _vars[_currVar++];
	// size_type ??
	pos_type tasksRemained = taskCount();
	pos_type pointersRemained = varSize();

	pos_type pmove = 0;
	pos_type ppos = 0;

	vector<pos_type> ans_pos;


	while ((pmove = searchMovePoint(tasksRemained, pointersRemained, id)) !=
		pointersRemained + 1) {
		// rework
		for (int i = taskCount() - tasksRemained + 1; i < pmove; i++)
			ans_pos.push_back(i);

		tasksRemained -= pmove - 1;
		pointersRemained -= pmove;

		ppos = searchMovePosition(tasksRemained, pointersRemained, id);
		tasksRemained -= ppos + 1;

		ans_pos.push_back(((ans_pos.empty() ? 0 : ans_pos.front()) + 1) + ppos);
	}

	return_type ans;
	for (auto x : ans_pos) {
		ans += _task[x] + '\n' + '\n';
	}
	return ans;
}