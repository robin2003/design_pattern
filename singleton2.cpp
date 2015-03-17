#include <pthread.h>		
#include <assert.h>
#include <iostream>

using namespace std;

class Mutex
{
public:
	Mutex(  )
	{
		pthread_mutex_init( &m_mutex, NULL );
	}
	~Mutex(  )
	{
		pthread_mutex_destroy( &m_mutex );
	}

	void lock(  )
	{
		pthread_mutex_lock( &m_mutex );
	}

	void unlock(  )
	{
		pthread_mutex_unlock( &m_mutex );	
	}

private:
	pthread_mutex_t m_mutex;
};

class MutexHelper
{
public:
	MutexHelper( Mutex mutex )
		:m_mutex( mutex )
	{
		m_mutex.lock(  );
	}
	
	~MutexHelper(  )
	{
		m_mutex.unlock(  );
	}
private:
	Mutex m_mutex;
};

class Singlton
{
public:
	static Singlton* getInstance(  )
	{
		if( m_instance == NULL )
		{
			MutexHelper mh( m_mutex );
			if( m_instance == NULL )
			{
				m_instance = new Singlton(  );
				return m_instance;
			}
		}
		
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
	
private:
	static Singlton* m_instance;
	static Mutex m_mutex;
};

Singlton* Singlton::m_instance = NULL;
Mutex Singlton::m_mutex ;

int main( void )
{
	Singlton* instance = Singlton::getInstance(  );
	instance->doSomeThing(  );

	Singlton* instance2 = Singlton::getInstance(  );
	assert( instance == instance2 );
	
	return 0;
}
