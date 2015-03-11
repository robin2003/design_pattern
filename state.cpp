#include <iostream>
#include <memory>
using namespace std;

class Child;
class ISchoolState
{
public:
	virtual void onState( Child* child ) = 0;
	virtual ~ISchoolState(  )
	{
	}
};

class Child
{
public:
	explicit Child( ISchoolState* state, int age )
		:m_state( state ),
		 m_age( age )
	{
	}

	void setState( ISchoolState* state )
	{
		m_state.reset( state );
	}
	
	void onSchool(  )
	{
		if( m_state.get(  ) != NULL )
		{
			m_state->onState( this );			
		}
	}
	
	int getAge(  ) const
	{
		return m_age;
	}

	void addOneAge(  )
	{
		m_age++;
	}
private:
	auto_ptr<ISchoolState> m_state;
	int m_age;
};

class Junior : public ISchoolState
{
public:
	void onState( Child* child )
	{
		int age = child->getAge(  );
		if( age >12 && age < 16 )
		{
			cout<<"age:"<<age<<" in junior school"<<endl;
		}
		else
		{
			child->setState( NULL );
		}
	}
	~Junior(  )
	{
		cout<<"---------------Junior destroy"<<endl;
	}
};

class Primary : public ISchoolState
{
public:
	void onState( Child* child )
	{
		int age = child->getAge(  );
		if( age > 6 && age <= 12 )
		{
			cout<<"age:"<<age<<" in primary school"<<endl;
		}
		else
		{
			child->setState( new Junior(  ) );
		}
	}
	~Primary(  )
	{
		cout<<"---------------primary destroy"<<endl;
	}
};

class Kindergarten : public ISchoolState
{
public:
	void onState( Child* child )
	{
		int age = child->getAge(  );
		if( age <= 6)
		{
			cout<<"age:"<<age<<" in kindergarten"<<endl;
		}
		else
		{
			child->setState( new Primary(  ) );
		}
	}

	~Kindergarten(  )
	{
		cout<<"---------------Kindergarten destroyed!"<<endl;
	}
};

int main( void )
{
	Kindergarten* kindergarten = new Kindergarten(  );
	Child child( kindergarten, 0 );

	int age = child.getAge(  );
	while( age < 17 )
	{
		child.onSchool(  );
		child.addOneAge(  );
		age = child.getAge(  );
	}
	
	return 0;
}
