#pragma once
#include <string>
#include <vector>
#include <deque>

class DS
{
private:
	using return_type = std::string;
	using pointer_type = unsigned long long;
	using size_type = size_t;

public:
	DS() = default;
	DS(std::vector<return_type> list, size_type task_cnt);

	inline size_type taskCount() const { return _tasks.size(); }
	inline size_type varSize() const { return _varSize; }
	inline size_type varCount() const { return getC(taskCount(), varSize()); }

	// TEMP
	inline size_type currVar() const { return _currId; }

	return_type operator()();

	std::strong_ordering operator<=>(const DS& other) const;

private:
	std::vector<return_type> _tasks;
	size_type _varSize = 0;

	std::deque<pointer_type> _ids;
	size_type _currId = 0;

	static pointer_type getC(pointer_type n, pointer_type k);

	size_type searchMovePoint(const size_type& tasksRemained,
		const size_type& pointersRemained, const pointer_type& id) const;

	size_type searchMovePosition(const size_type& tasksRemained,
		const size_type& pointersRemained, const pointer_type& id) const;

	//size_type findAPosition(pos_type pos, size_type l = 0) const {
	//	return findAPosition(pos, l, _varSize);
	//}
};
