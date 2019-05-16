#pragma once

#include <iostream>
#include "shared_obj.h"


namespace sch001 {
	template <class T>
	class weak_ptr;

	//TODO: 增加型别转换？
	template <class T>
	class shared_ptr {
		typedef weak_ptr<T> weak_type;
		shared_obj<T> ref_cnt;

		template< class T> friend class shared_ptr;
		template< class T> friend class weak_ptr;
		//
	public:
		explicit operator weak_type() {
			std::cout << "please implement me!\n";
		}
		shared_ptr() = default;
		shared_ptr(T* raw_ptr):ref_cnt(raw_ptr){}
		shared_ptr(const shared_ptr& sp) :ref_cnt(sp.ref_cnt) {
			ref_cnt.acquire();
		}
		shared_ptr& operator=(const shared_ptr& sp) {
			//
			ref_cnt = sp.ref_cnt;
			ref_cnt.acquire();
			return *this;
		}
		
		~shared_ptr() {
			//assert(ref_cnt.get_user_cnt() != 0);
			ref_cnt.release();
		}

		template<class U>
		shared_ptr(shared_ptr<U> sptr):ref_cnt(sptr.ref_cnt) {}

		explicit operator bool() {
			return ref_cnt.get_user_cnt() != 0;
		}
		bool unique() {
			return ref_cnt.get_user_cnt() == 1;
		}
		int user_count() {
			return ref_cnt.get_user_cnt();
		}
		void reset() {
			ref_cnt.release();
		}
		void reset(T* new_ptr) {
			
			if (get() == new_ptr) {
				std::cout << "我set我自己\n";
				//do nothing
			}
			else {
				ref_cnt.release();
				ref_cnt.resource = new_ptr;
				ref_cnt.user_count = new int(1);
				//ref_cnt = shared_obj<T>(new_ptr);
			}
		}
		//get the raw ptr
		T* get() {
			return ref_cnt.get();
		}

		T& operator*() const noexcept {
			return *(ref_cnt.get());
		}
		T* operator->() const noexcept {
			return ref_cnt.get();
		}
	private:
		shared_ptr(shared_obj<T> sobj) {
			ref_cnt = sobj;
			ref_cnt.acquire();
		}
	};

	//weak_ptr
	template<class T>
	class weak_ptr {
		shared_obj<T> ref_cnt;
		//shared_ptr<T>* strong_ptr;
		
	public:
		//ctr
		weak_ptr(const shared_ptr<T>& sp) {
			ref_cnt = sp.ref_cnt;
		}
		weak_ptr& operator=(const shared_ptr<T>& sp) {
			ref_cnt = sp.ref_cnt;
			return *this;
		}

		~weak_ptr() = default;

		shared_ptr<T> acquire() {
			//std::cout << "Please implement me!\n";
			return shared_ptr<T>(ref_cnt);
		}
	};
}