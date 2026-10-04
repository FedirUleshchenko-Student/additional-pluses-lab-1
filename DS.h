#pragma once
#include <string>
#include <vector>
#include <deque>
#include <compare>

class DS
{
private:
	using return_type = std::string;
	using pointer_type = unsigned long long;
	using size_type = size_t;
public:
	/// <summary>
	/// Data structure constructor
	/// Throws bad_alloc if cannot allocate memory
	/// </summary>
	/// <param name="tasks">DS of strings of all tasks to choose from</param>
	/// <param name="needed_task_cnt">Number of tasks in every variant</param>
	DS(std::vector<return_type> tasks, size_type needed_task_cnt);

	// Returns number of possible tasks to choose from
	inline size_type taskCount() const { return _tasks.size(); }

	// Returns a number of tasks, that needs to be in every variant
	inline size_type varSize() const { return _varSize; }

	// Returns a number of possible variants on data inside DS
	inline size_type varCount() const { return getC(taskCount(), varSize()); }

	// Returns a new random variant, that had not rolled before
	return_type operator()();

	// Compares 2 class elements
	// Compares by their number of remaining variants to generate
	// if other DS element has different size (tasks or varSize) -> Throws invalid_argument
	std::strong_ordering operator<=>(const DS& other) const;
private:
	std::vector<return_type> _tasks;
	size_type _varSize = 0;

	std::deque<pointer_type> _ids;
	size_type _currId = 0;

	static pointer_type getC(pointer_type n, pointer_type k);

	/// <summary>
	/// First of 2 funcs of "Id Converting" Algorithm.
	/// Works locally on: 
	/// Tasks - [n - tasksRemained + 1, n];
	/// Pointers - [k - pointersRemained + 1, k];
	/// </summary>
	/// <param name="tasksRemained">- number of possible positions to fit in pointers</param>
	/// <param name="pointersRemained">- number of free pointers</param>
	/// <param name="id">- remained id`s of needed random variant. It decreases as the algorithm operates</param>
	/// <returns>Returns first left pointer that moves. Count starts from 1</returns>
	size_type searchMovePoint(const size_type& tasksRemained,
		const size_type& pointersRemained, const pointer_type& id) const;

	/// <summary>
	/// Second of 2 funcs of "Id Converting" Algorithm.
	/// Works locally on: 
	/// Tasks - [n - tasksRemained + 1, n];
	/// Pointers - [k - pointersRemained + 1, k];
	/// </summary>
	/// <param name="tasksRemained">- number of possible positions to fit in pointers. Starting position of movable pointer COUNTS</param>
	/// <param name="pointersRemained">- number of free pointers. Movable pointer DOES NOT COUNT</param>
	/// <param name="id">- remained id`s of needed random variant. It decreases as the algorithm operates</param>
	/// <returns>Returns the amount of positions to move right the movable pointer</returns>
	size_type searchMovePosition(const size_type& tasksRemained,
		const size_type& pointersRemained, const pointer_type& id) const;
};
