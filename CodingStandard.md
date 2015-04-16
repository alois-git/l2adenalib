The L2AdenaLib coding standard

# Introduction #

If you would like to write code for this project, please follow these guidelines.

# Standard #

Here is a sample header file
```
/*
 * Test.h - A file...
 *
 * Copyright notice
 */

#include <file.h>

namespace bob
{

	/*
	 * Test - This is a test class
	 */
	class Test : public file
	{
	public:

		/*
		 * @param b: [IN] The test number
		 */
		Test(int b);

		virtual ~Test();

		/*
		 * @param a: [IN] Lentgh of b
		 * @param b: [IN] A fixed length array
		 * @param c: [OUT] b represented in float
		 * return: true on sucess, false on failure
		 */
		bool funcOne(int a, char b[], float* c); // First word lowercase, each additional word capitalized

	private:

		/*
		 * Set to the value of a whenever funcOne is called
		 */
		int PrivateVar; // First word uppercase, each additional word capitalized

	}

}

```

And here is that file that implements that

```
/*
 * Test.cpp - A file...
 *
 * Copyright notice
 */

#include <Test.h>
#include <iostream>

namespace bob
{

Test::Test(int b)
{
	if(b == 0) // Note that there is a line break before the {
	{
		std::cout << "Adena PLIX!\n"; // No using namespace statements
	}else
	{
		std::cout << "JAJAJAJJA!\n";
	}
};

Test::~Test()
{
	// No code
}

/*
 * Internaly: PrivateVar set to a
 */
bool Test::funcOne(int a, char b[], float* c)
{
	PrivateVar = a;

	if(a == 0)
		return false;

	int i; // For loop iterators should be defined outside of the for loop.
	for(i = 0; i < a; i++)
		c += b[i]; // One line for loops don't need brackets

	return true;
};

}

```
