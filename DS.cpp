#include "DS.h"
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <random>

using namespace std;

DS::DS(vector<return_type> list, size_type task_cnt) :
	_tasks(list), _varSize(task_cnt), _currId(0), _ids(getC(list.size(), task_cnt)) {
	iota(_ids.begin(), _ids.end(), 1); // start from 1
	shuffle(_ids.begin(), _ids.end(), mt19937(random_device()()));
}

DS::pointer_type DS::getC(pointer_type n, pointer_type k) {
	if (k > n) return 0;
	if (k == 0 || k == n) return 1;

	// C(n, k) == C(n, n - k)
	if (k > n / 2) k = n - k;

	pointer_type result = 1;
	for (pointer_type i = 1; i <= k; i++) {
		result *= (n - k + i);
		result /= i;
	}

	return result;
}

DS::size_type DS::searchMovePoint(const size_type& tasksRemained,
	const size_type& pointersRemained, const pointer_type& id) const {
	pointer_type l = 0, r = pointersRemained + 1;
	pointer_type t;
	while (l + 1 < r) {
		t = midpoint(l, r);
		if (((pointersRemained - t) ? getC(tasksRemained - t, pointersRemained - t) : 0) < id)
			r = t;
		else l = t;
	}
	return r;
}

DS::size_type DS::searchMovePosition(const size_type& tasksRemained,
	const size_type& pointersRemained, const pointer_type& id) const {
	if (pointersRemained == 0) return id - 1;

	pointer_type l = 0, r = tasksRemained - 1;
	pointer_type localVarCount = getC(tasksRemained, pointersRemained + 1);
	pointer_type t;
	while (l + 1 < r) {
		t = midpoint(l, r);

		// sum of skipped vars:
		//	k+1				 k		k
		// C	=  SUM[from C   to C  ]
		//	n+1				 k		n
		if (localVarCount - getC(tasksRemained - t, pointersRemained + 1) < id)
			l = t;
		else r = t;
	}
	return l;
}

DS::return_type DS::operator()() {
	if (_currId >= _ids.size())
		throw domain_error("All of task variants are used. Cannot get more");

	pointer_type id = _ids[_currId++];
	pointer_type tasksRemained = taskCount();
	pointer_type pointersRemained = varSize();
	pointer_type pmove = 0, ppos = 0;
	vector<pointer_type> ans_pos;


	while ((pmove = searchMovePoint(tasksRemained, pointersRemained, id)) !=
		pointersRemained + 1) {
		for (pointer_type i = 1; i < pmove; i++)
			ans_pos.push_back(taskCount() - tasksRemained + i);
		tasksRemained -= pmove - 1;
		pointersRemained -= pmove;

		ppos = searchMovePosition(tasksRemained, pointersRemained, id);

		id -=
			getC(tasksRemained, pointersRemained + 1) -
			getC(tasksRemained - ppos, pointersRemained + 1);
		tasksRemained -= ppos + 1;
		ans_pos.push_back(((ans_pos.empty() ? 0 : ans_pos.back()) + 1) + ppos);
	}

	return_type ans;
	for (auto x : ans_pos) {
		ans += _tasks[x - 1] + "\n\n";
	}
	return ans;
}

std::strong_ordering DS::operator<=>(const DS& other) const{
	if (varSize() != other.varSize() || taskCount() != other.taskCount())
		throw invalid_argument("cannot compare 2 classes on different data size");
	return { _currId <=> other._currId };
}