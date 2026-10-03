#pragma once
#include <string>
#include <vector>
#include <deque>

class DS
{
private:
	using return_type = std::string;
	using operator_comparison_type = int;
	using size_type = size_t;
	using pos_type = unsigned long long;

public:
	DS() = default;
	DS(std::vector<return_type> list, size_type task_cnt);

	inline size_type taskCount() const { return _task.size(); }
	inline size_type varSize() const { return _varSize; }

	// TEMP
	inline size_type currVar() const { return _currVar; }

	return_type operator()();

private:
	std::vector<return_type> _task;
	size_type _varSize = 0;

	std::vector<pos_type> _vars;
	size_type _currVar = 0;

	static pos_type getC(pos_type n, pos_type k);

	size_type searchMovePoint
	(size_type tasksRemained, size_type pointersRemained, const pos_type& pos) const;

	size_type searchMovePosition
	(size_type tasksRemained, size_type pointersRemained, pos_type& pos) const;

	//size_type findAPosition(pos_type pos, size_type l = 0) const {
	//	return findAPosition(pos, l, _varSize);
	//}
};
