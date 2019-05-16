#pragma once

#include <cassert>

#include "smart_ptr.h"

namespace sch001 {
	template<class T>
	class shared_ptr;
	/*
	* 合理的做法是每个shared_ptr都会有一个shared_obj的member
	* shared_ptr只要在ctr/dtr调用shared_obj提供的接口release和
	* acquire，get_user_count即可
	*
	* 或者shared_ptr持有一个shared_obj的ptr，然后把user_count改为int而不是int*
	* 这样做除了在空shared_ptr时少用了ptr，在非空时多了个ptr没啥区别
	* 代码估计还会更丑
	*/
	/*
	* =================================================
	* release()和acquire()在构造和析构shared_obj不需要被调用
	*/
	template <class T>
	class shared_obj {
		friend class shared_ptr<T>;
		template<class T> friend class shared_obj;

		//记录shared_ptr的用户个数，即强引用
		int* user_count;
		//托管的资源，外界会通过shared_ptr这一层传一个raw指针进来
		T* resource;

		void release() {
			if (!user_count) {
				assert(!resource);
				return;
			}
			//
			if (--*user_count == 0) {
				delete user_count;user_count = nullptr;
				delete resource;resource = nullptr;
			}
		}
		void acquire() {
			if (!user_count) {
				std::cout << "Resource has been released!\n";
				assert(!resource);
				return;
			}
			++*user_count;
		}
		int get_user_cnt() {
			return user_count == nullptr ? 0 : *user_count;
		}

	public:
		//ctr
		shared_obj() :user_count(nullptr), resource(nullptr) {}
		shared_obj(const shared_obj& so) = default;
		shared_obj& operator=(const shared_obj& so) = default;
		/*
		{
		//当shared_ptr调用复制ctr时，会调用我
		//所以是让谁做acquire好点呢
		}
		*/
		//shared_obj(shared_obj&& so);
		shared_obj(T* src_ptr) :resource(src_ptr) {
			if (resource != nullptr) {
				user_count = new int(1);
			}
		}
		//
		template<class U>
		shared_obj(const shared_obj<U>& sobj):user_count(sobj.user_count), resource((T*)sobj.resource){}

		//会在shared_ptr被析构的时候被调用
		~shared_obj() {
			//release();
		}

		T* get() const {
			return resource;
		}
	};

}