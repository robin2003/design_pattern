#include <iostream>
#include <string>
#include <list>

using namespace std;

class IComponent
{
public:
	explicit IComponent( const string& name  )
		:m_name( name )
	{
	}
	
	virtual void add( IComponent* comp )
	{
		cout<<"can't add"<<endl;
	}
	
	virtual void del( IComponent* comp )
	{
		cout<<"can't delete"<<endl;
	}

	const string& getName(  ) const
	{
		return m_name;
	}

	virtual ~IComponent(  )
	{
	}
	
	virtual void display( int depth ) const = 0;

	
protected:
	void printDepth( int depth ) const
	{
		while( depth )
		{
			depth--;
			cout<<"---";
		}
	}

private:
	string m_name;
};

class Leaf : public IComponent
{
public:
	explicit Leaf( const string& name )
		: IComponent( name )
	{
	}

	void display( int depth ) const
	{
		const string& name = getName(  );
		printDepth( depth );
		cout<<"---leaf "<<name<<endl;
	}
};

class Composit : public IComponent
{
public:
	explicit Composit( const string& name )
		: IComponent( name )
	{
	}

	void add( IComponent* comp )
	{
		m_lists.push_back( comp );
		m_lists.unique(  );
	}

	void del( IComponent* comp )
	{
		list<IComponent*>::iterator iter = m_lists.begin(  );
		for( ;iter != m_lists.end(  ); iter++ )
		{
			if( *iter == comp )
			{
				m_lists.erase( iter );
				break;
			}
		}
	}

	void display( int depth = 0 ) const
	{
		printDepth( depth );
		depth++;
		
		cout<<"---composit "<<getName(  )<<endl;
		list<IComponent*>::const_iterator iter = m_lists.begin(  );
		for( ;iter != m_lists.end(  ); iter++ )
		{
			const IComponent* comp = *iter;
			comp->display( depth );
		}
	}
	
private:
	list<IComponent*> m_lists;
};

int main(  )
{
	Leaf lf1( string( "lf1" ) );
	Leaf lf2( string( "lf2" ) );
	Composit comp1( string( "comp1" ) );
	comp1.add( &lf1 );
	comp1.add( &lf2 );
	
	Composit comp2( string( "comp2" ) );
	comp2.add( &comp1 );
	Leaf lf3( string( "lf3" ) );
	comp2.add( &lf3 );

	comp2.display( 0 );
	
	return 0;
}
