#pragma once
#include <functional>

using namespace std;


template<class T>
class DataSet {
	//T is a stl contianer type
	T _container;

public:
	T ToList() { return _container; }

	DataSet<T>(T& container) : _container(container) {}

	DataSet<T>(T&& container) : _container(move(container)) {}

	template<class ret_type>
	DataSet<vector<ret_type>> Select(function<ret_type (typename T::value_type)> selector) {
		vector<ret_type> new_container;
		for (const auto& item : _container) {
			new_container.push_back(selector(item));
		}

		return DataSet(move(new_container));
	}

	DataSet<T> Where(function<bool(typename T::value_type)> filter) {
		T new_container;
		for (const auto& item : _container) {
			if (filter(item)) {
				new_container.push_back(item);
			}
		}
		return DataSet(move(new_container));
	}

};

template<class T>
DataSet<T> From(T& container) {
	return DataSet<T>(container);
}