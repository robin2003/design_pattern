#include <iostream>
#include <assert.h>

using namespace std;

class Singlton
{
public:
	static Singlton* getInstance(  )
	{
		static Singlton instance;
		return &instance;
	}

	void doSomeThing(  )
	{
		cout<<"do some thing"<<endl;
	}
private:
	Singlton(  )
	{
	}
	~Singlton(  )
	{
		cout<<"destroy!"<<endl;
	}
	Singlton( Singlton& rhs );
	Singlton& operator=( Singlton& rhs );
};

int main( void )
{
	Singlton* instance = Singlton::getInstance(  );
	instance->doSomeThing(  );

	Singlton* instance2 = Singlton::getInstance(  );
	assert( instance == instance2 );
	
	return 0;
}
