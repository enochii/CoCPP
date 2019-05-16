#pragma once

#include <cassert>

#include "smart_ptr.h"

namespace sch001 {
	template<class T>
	class shared_ptr;
	/*
	* �����������ÿ��shared_ptr������һ��shared_obj��member
	* shared_ptrֻҪ��ctr/dtr����shared_obj�ṩ�Ľӿ�release��
	* acquire��get_user_count����
	*
	* ����shared_ptr����һ��shared_obj��ptr��Ȼ���user_count��Ϊint������int*
	* �����������ڿ�shared_ptrʱ������ptr���ڷǿ�ʱ���˸�ptrûɶ����
	* ������ƻ������
	*/
	/*
	* =================================================
	* release()��acquire()�ڹ��������shared_obj����Ҫ������
	*/
	template <class T>
	class shared_obj {
		friend class shared_ptr<T>;
		template<class T> friend class shared_obj;

		//��¼shared_ptr���û���������ǿ����
		int* user_count;
		//�йܵ���Դ������ͨ��shared_ptr��һ�㴫һ��rawָ�����
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
		//��shared_ptr���ø���ctrʱ���������
		//��������˭��acquire�õ���
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

		//����shared_ptr��������ʱ�򱻵���
		~shared_obj() {
			//release();
		}

		T* get() const {
			return resource;
		}
	};

}