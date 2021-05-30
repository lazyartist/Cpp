#include <iostream>
#include <string>

using namespace std;

void _0701_function_return() {

	int a = 10;
	int &b = a;
	b = 5;
	int *c = &b;

	cout << a << ", " << b << ", " << *c << endl;

	// call by value: 함수 인자를 값을 복사하여 전달, fn(int a)
	// call by address: 함수 인자를 변수의 주소(포인터)로 전달, fn(int *a)
	// call by reference: 함수의 인자를 레퍼런스를 이용하여 전달, fn(int &a)

	cout << "===== return type =====" << endl;
	{
		class A {
		public:
			// 일반 생성자
			A(string name) {
				//this->pName = &name; // 이 함수내에서만 사용하고 사라질 인자값을 할당하면 안된다.
				this->pName = new string(name); // 새로운 string 객체를 생성해서 할당해야한다.
				cout << "constructor: " << this << ", " << this->pName->c_str() << endl;
			}

			// 복사 생성자
			A(const A& other) { // const를 붙여서 코드 안정성을 높인다. const 인자는 함수내에서 수정할 수 없다.
				this->pName = new string("copy" + *(other.pName));
				cout << "copy constructor this(" << this->pName->c_str() << " " << this << "), other(" << other.pName->c_str() << " " << (&other) << ")" << endl;
			}

			// 이동 생성자
			A(A&& other) { 
				this->pName = new string("move" + *(other.pName));
				cout << "move constructor this(" << this->pName->c_str() << " " << this << "), other(" << other.pName->c_str() << " " << (&other) << ")" << endl;
				other.pName = nullptr;
			}

			~A() {
				cout << "destructor: " << this << endl;
				if (pName != nullptr) {
					cout << "delete" << endl;
					delete pName;
				}
			}

			string *pName = nullptr;
			//string name = nullptr; // string name은 포인터가 아니므로 nullptr을 지정할 수 없다.
		};

		cout << "===== value return =====" << endl;
		{
			class returnValue {
			public:
				A operator()() {
					A tmp("tmp");
					return tmp;
				}
			};

			/*
			이동생성자(rvalue reference)가 호출되는 이유
				반환될 임시객체 생성시 인자로 전달되는 tmp는 곧 사라질 객체이므로 
				rvalue(값을 대입하고 사라질 임시객체)로 인식해서 이동생성자가 호출된다.
				이동생성자에서는 rvalue의 힙변수를 이동시키고 nullptr로 만들어 메모리 해제되지 않게 한다.
				std::move() 함수가 이 작업을 지원한다.
				todo std::move 작동법 확인
			*/

			returnValue()();
			/*
			constructor: 010FFC18, tmp // 함수내 지역변수 tmp 생성
			move constructor this(movetmp 010FFCD8), other(tmp 010FFC18) // 반환 임시객체 생성 및 이동생성자 호출
			destructor: 010FFC18 // 함수내 지역변수 tmp 소멸
			// 함수내 지역변수 tmp의 pName는 이동 생성자에서 nullptr이 할당됐으므로 소멸되지 않는다.
			destructor: 010FFCD8 // 반환 임시객체 movetmp 소멸
			delete // 반환 임시객체 move 소멸 시 pName 해제
			*/

			cout << "-----" << endl;

			A a = returnValue()();
			cout << "a: " << &a << ", " << a.pName->c_str() << endl;
			/*
			// 위와 다른 부분만 주석
			constructor: 0059F4B0, tmp
			move constructor this(movetmp 0059F66C), other(tmp 0059F4B0)
			destructor: 0059F4B0
			a: 0059F66C, movetmp // a에 반환 임시객체가 할당됐다.
								 // ** 반환값을 변수에 저장 시 대입으로 인한 복사생성이 되지 않고 임시변수를 곧바로 변수에 할당한다.**
								 // (컴파일러가 해주는지 언어 명세에 있는건지 모르겠다.)
								 // 따라서 다음행으로 넘어가도 임시객체가 지워지지 않는다.
			destructor: 0059F66C
			delete

			윤성우 열혈 C++ 프로그래밍 p.239: 임시변수를 곧바로 변수에 할당하는 내용참고
			*/
		}

		cout << "===== reference return =====" << endl;
		{
			class returnReference {
			public:
				const A& operator()() {
					A tmp("tmp");
					return tmp;
				}
			};

			returnReference()();
			/*
			constructor: 00C5F8A4, tmp // 함수내 지역변수 tmp 생성
			// 참조를 반환하기 때문에 반환 임시객체를 생성하지 않는다.
			destructor: 00C5F8A4, tmp // 함수내 지역변수 tmp 소멸
			delete
			*/

			//(returnReference()()).name = "aaa"; // 런타임 에러. 임시객체가 가리키는 지역객체가 사라져서 그런듯
												  // 함수 반환타입에 const를 붙이면 컴파일 에러. 임시변수의 값을 변경하지 못하게 하기 때문.
												  // 이렇게 쓰는 경우가 거의없어서 사람들이 함수반환의 const는 의미없다고 한거 같다.
			cout << "-----" << endl;

			//A a = returnReference()(); // 참조를 반환하고 반환값을 변수에서 받는 경우 : 런타임 에러
			/*
			constructor: 0095FA08, tmp
			destructor: 0095FA08, tmp // 지역변수를 반환하고 소멸된다.
			// A a 변수를 생성하고 복사생성저를 호출하며 에러난다.

			참조반환은 임시객체를 생성하지 않고 지역변수의 참조를 반환하고 반환 즉시 지역변수는 소멸된다.
			반환값이 사라질 객체이므로 반환값을 받는 변수에 할당할 수 없어서 
				새로운 객체가 생성되고 이 객체의 생성자 호출 인자로 사라진 객체가 전달된다.
			이미 소멸된 객체가 전달됐으므로 이상 동작 또는 에러가 난다.
			*/
		}

		cout << "===== pointer return =====" << endl;
		{
			class returnPointer {
			public:
				A* operator()() {
					A tmp("tmp");
					return &tmp;
				}
			};

			returnPointer()();
			/*
			constructor: 00C5F8A4, tmp // 함수내 지역변수 tmp 생성
				// 참조를 반환하기 때문에 반환 임시객체를 생성하지 않는다.
			destructor: 00C5F8A4, tmp // 함수내 지역변수 tmp 소멸
			delete
			*/

			//*(returnPointer()()) = A("aaa", 1); // 런타임 에러. 임시객체가 가리키는 지역객체가 사라져서 그런듯

			cout << "-----" << endl;

			A* a = returnPointer()();
			//cout << "a: " << a << ", " << a->name << endl; // 런타임 에러
			/*
			함수내부에서 생성된 객체를 반환값으로 받았으므로 함수 실행이 끝나자 포인터가 쓰레기값을 가리킨다.
			*/
		}

		cout << "===== heap reference return =====" << endl;
		{
			class returnHeapReference {
			public:
				A& operator()() {
					A* tmp = new A("tmp");
					//A tmp("tmp", 1);
					return *tmp;
				}
			};

			{
				returnHeapReference()();
				/*
				constructor: 013B49A0, tmp // 함수내에서 Heap 변수 tmp 생성
				// 지역변수(포인터변수)는 사라져도 힙에 생성된 객체는 소멸되지 않기 때문에 소멸자가 호출되지 않는다.
				*/

				cout << "-----" << endl;

				*(returnHeapReference()().pName) = "aaaa";
				/*
				constructor: 00CF4788, tmp // 힙에 객체가 살아있기 때문에 런타임 에러안남.
				*/

				/*
				함수 반환값을 받는 곳에서 메모리 해제하지 않으면 메모리릭이 발생할 수 있다.
				*/
			}

			cout << "----- 객체로 받기" << endl;
			{
				A a = returnHeapReference()();
				cout << "a: " << &a << ", " << a.pName << endl;
				/*
				constructor: 013BF040, tmp // 함수내에서 Heap 변수 tmp 생성
				copy constructor this(copytmp 00F5F9C8), other(tmp 013BF040) // 힙에 생성한 객체의 참조를 반환했으므로
																			 // A a 변수를 생성하고 복사생성자를 호출한다.
				a: 00F5F9C8, copytmp // a 변수는 힙에 생성된 tmp의 복사본이다.(포인터가 다르다)
				destructor: 00F5F9C8, copytmp

				// 힙에 생성된 tmp는 소멸될 수 없다.(메모리릭 발생)
				*/
			}

			cout << "----- 포인터로 받기" << endl;
			{
				A* a = &returnHeapReference()();
				cout << "a: " << a << ", " << a->pName << endl;
				delete a;
				/*
				constructor: 0006F6C8, tmp // 함수내에서 Heap 변수 tmp 생성
					// 참조반환 및 포인터 대입 시 객체의 생성이 아니기 때문에 복사생성자가 호출되지 않는다.
				a: 0006F6C8, tmp // a 변수는 힙에 생성된 tmp와 같은 객체이다.
				destructor: 0006F6C8, tmp // 포인터로 힙의 메모리를 해제할 수 있다.
				*/
			}
		}
	}
}