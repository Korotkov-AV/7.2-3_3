// 7.2-3(3).cpp : c++17

#include <iostream>
#include<thread>
#include<mutex>




class Data {
public:
	int a;
	std::mutex mA;

	Data(int a) {
		this->a = a;
	}

	void show() {
		std::cout << "a= " << a << std::endl;
	}
};

void swap_lock_guard(Data& ob1, Data& ob2) {
	std::lock_guard lockA(ob1.mA);
	std::lock_guard lockB(ob2.mA);

	std::swap(ob1.a, ob2.a);
	std::cout << "*swap*" << std::endl;
}

void swap_uniquelock(Data& ob1, Data& ob2) {
	std::unique_lock locA{ ob1.mA };
	std::unique_lock locB{ ob2.mA };
	//locA.lock();
	//locB.lock();

	std::swap(ob1.a, ob2.a);
	std::cout << "*swap*" << std::endl;
}

void swap_scopedlock(Data& ob1, Data& ob2) {
	std::scoped_lock loc{ ob1.mA, ob2.mA };

	std::swap(ob1.a, ob2.a);
	std::cout << "*swap*" << std::endl;
}


void swap_lock(Data& ob1, Data& ob2) {
	(ob1.mA).lock();
	(ob2.mA).lock();

	std::swap(ob1.a, ob2.a);
	std::cout << "*swap*" << std::endl;

	(ob1.mA).unlock();
	(ob2.mA).unlock();
}

int main()
{
	Data number1(1);
	Data number2(2);
	number1.show();
	number2.show();
	std::cout << "---------" << std::endl;


	swap_lock(number1, number2);
	number1.show();
	number2.show();
	std::cout << "---------" << std::endl;

	swap_uniquelock(number1, number2);
	number1.show();
	number2.show();
	std::cout << "---------" << std::endl;

	swap_scopedlock(number1, number2);
	number1.show();
	number2.show();
	std::cout << "---------" << std::endl;

	return 0;
}
