#include <iostream>

struct TestObject
{
	unsigned int Value;

	TestObject()
	{
		std::cout << "++++  TestObject()\n";
	}
	~TestObject()
	{
		std::cout << "----  TestObject()\n";
	}

	TestObject(const TestObject & other)
	{
		std::cout << "====  TestObject(other)\n";
		(void)other;
	}
	TestObject & operator=(const TestObject & other)
	{
		std::cout << "====  operator=\n";
		(void)other;
		return *this;
	}

	TestObject ReturnObj() const
	{
		std::cout << "ReturnObj()\n";
		return TestObject();
	}
	TestObject ReturnTempObj() const
	{
		std::cout << "ReturnTempObj()\n";
		TestObject obj;
		std::cout << "Padding\n";
		return obj;
	}

	static TestObject StaticReturnObj()
	{
		std::cout << "StaticReturnObj()\n";
		return TestObject();
	}
	static TestObject StaticReturnTempObj()
	{
		std::cout << "StaticReturnTempObj()\n";
		TestObject obj;
		std::cout << "Padding\n";
		return obj;
	}

	static TestObject DoubleReturn1(TestObject * & ptr)
	{
		std::cout << "DualReturn()\n";
		TestObject obj;
		TestObject temp;

		if (ptr == NULL)
		{
			obj.Value = 0;
			ptr = &obj;
			return obj;
		}
		else
		{
			obj.Value = 0xFFFFFFFF;
			ptr = &obj;
			return obj;
		}
	}
	static TestObject DoubleReturn2(TestObject * & ptr)
	{
		std::cout << "DualReturn()\n";
		TestObject obj0;
		TestObject obj1;
		if (ptr == NULL)
		{
			ptr = &obj0;
			return obj0;
		}
		else
		{
			ptr = &obj1;
			return obj1;
		}
	}
};



void Normal()
{
	std::cout << "################\n";
	{
		std::cout << "Normal\n";
		TestObject obj;
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "Copy\n";
		TestObject obj0;
		TestObject obj1(obj0);
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "Copy\n";
		TestObject obj0;
		TestObject obj1 = obj0;
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "Copy\n";
		TestObject obj0;
		TestObject obj1;
		obj1 = obj0;
		std::cout << "   done\n";
	}
	std::cout << "################\n";

	/*	Conclusion:
			TestObj obj1(obj0);
			TestObj obj1 = obj0;
		both call the copy Constructor
	*/
}
void StaticReturn()
{
	std::cout << "################\n";
	{
		std::cout << "      Return()\n";
		TestObject obj(TestObject::StaticReturnObj());
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "      Return()\n";
		TestObject obj = TestObject::StaticReturnObj();
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "      Return()\n";
		TestObject obj;
		obj = TestObject::StaticReturnObj();
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "      static Return()\n";
		TestObject obj(TestObject::StaticReturnTempObj());
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "      static Return()\n";
		TestObject obj = TestObject::StaticReturnTempObj();
		std::cout << "   done\n";
	}
	std::cout << "################\n";
	{
		std::cout << "      static Return()\n";
		TestObject obj;
		obj = TestObject::StaticReturnTempObj();
		std::cout << "   done\n";
	}
	std::cout << "################\n";

	/*	Conclusion

			TestObject obj;
			obj = Func();
		calls operator= as expected.

		Since
			TestObj obj1(obj0);
			TestObj obj1 = obj0;
		are the same,
			TestObj obj(Func());
			TestObj obj = Func();
		also do the same.

		But, instead of calling the copy Constructor
		it just sets the outside object directly to the inside object.

		Question:
		Does the compiler know that the outside object wants to be the inside object
		and so it acutally uses the outside object inside ?

		How to test:
		make a function that takes a Parameter.
		create 2 Objects inside and return based on Parameter.
		also remember Address.
	*/
}
void DoubleReturn1()
{
	/*	Abstract:
		have a Funciton that
			creates multiple Objects
			does stuff with the main Object depending on Parameters
			has multiple returns for the main Object
		but
			only ever returns the same Object (main Object)
	*/
	std::cout << "################\n";
	{
		TestObject * ptr = NULL;
		std::cout << "ptr " << ptr << '\n';
		std::cout << '\n';
		
		TestObject obj(TestObject::DoubleReturn1(ptr));
		std::cout << '\n';

		std::cout << "ptr " << ptr << '\n';
		std::cout << "obj " << &obj << '\n';
		std::cout << "val " << obj.Value << '\n';
	}
	std::cout << "################\n";
	{
		TestObject * ptr = new TestObject();
		delete ptr;
		std::cout << "ptr now filled with garbadge\n";
		std::cout << "ptr " << ptr << '\n';
		std::cout << '\n';

		TestObject obj(TestObject::DoubleReturn1(ptr));
		std::cout << '\n';

		std::cout << "ptr " << ptr << '\n';
		std::cout << "obj " << &obj << '\n';
		std::cout << "val " << obj.Value << '\n';
	}
	std::cout << "################\n";
	/*	Conclusion:
		as long as the same Object is returned at every return in the function,
		then the Outside Object is the same as the inside Object
		(same Address to same on the Stack. I assume)
	*/
}
void DoubleReturn2()
{
	/*	Abstract:
		Function that:
			creates 2 Objects
			return eighter Object. depending on Parameters
	*/
	std::cout << "################\n";
	{
		TestObject * ptr = NULL;
		std::cout << "ptr " << ptr << '\n';
		std::cout << '\n';
		
		TestObject obj(TestObject::DoubleReturn2(ptr));
		std::cout << '\n';

		std::cout << "ptr " << ptr << '\n';
		std::cout << "obj " << &obj << '\n';
	}
	std::cout << "################\n";
	{
		TestObject * ptr = new TestObject();
		delete ptr;
		std::cout << "ptr now filled with garbadge\n";
		std::cout << "ptr " << ptr << '\n';
		std::cout << '\n';

		TestObject obj(TestObject::DoubleReturn2(ptr));
		std::cout << '\n';

		std::cout << "ptr " << ptr << '\n';
		std::cout << "obj " << &obj << '\n';
	}
	std::cout << "################\n";
	/*	Conclusion:
		If multiple objects can be returned,
		then the outside Object is different from the inside Objects
		and the return gets passed to the copy Constructor of the outside Object
	*/
}



int main()
{
	//Normal();
	//StaticReturn();
	//DoubleReturn1();
	//DoubleReturn2();
	return 0;
}
