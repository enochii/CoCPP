#include "smart_ptr.h"

#include <iostream>

struct wohaocia {
	double _;
	wohaocia() {
		std::cout << "我来了！\n";
	}
	virtual ~wohaocia() {
		std::cout << "我走了额！\n";
	}
	void set(int i) {
		_ = i;
	}
	double get() {
		return _;
	}
};

struct xi:public wohaocia{
	int __;
	xi() {
		std::cout << "xi()\n";
	}
	~xi() {
		std::cout << "~xi()\n";
	}
};

int main()
{
	{
		sch001::shared_ptr<double> sp(new double(0.0));

		std::cout << *sp << std::endl;
		*sp = 0.1;
		std::cout << *sp << std::endl;
		std::cout << sp.user_count() << std::endl;

		auto sp1 = sp;
		*sp1 = 0.3;
		std::cout << *sp << std::endl;
		std::cout << sp.user_count() << std::endl;

		{
			sch001::shared_ptr<wohaocia> p(new wohaocia());
		}
		sch001::shared_ptr<wohaocia> p_;
		{
			sch001::shared_ptr<wohaocia> p(new wohaocia());
			p_ = p;
			std::cout << "我还没走8！\n";
			std::cout << p_.user_count() << std::endl;
		}

		p_.reset(new wohaocia());
		std::cout << "我是分割线" << std::endl;
	}
	
	{
		std::cout << "\n=========\n";
		sch001::shared_ptr<xi> sbp = sch001::shared_ptr<wohaocia>(new wohaocia());
		sbp->set(10);
		sch001::weak_ptr<xi> sbwp = sbp;
		{
			auto sbp1 = sbwp.acquire();
			std::cout << sbp1->get();
		}
		std::cout << "\n=========\n";
	}

	system("pause");
	return 0;
}