#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

using namespace std;

class Goods;
typedef boost::shared_ptr<Goods> GOODS_PTR;

class Goods
{
public:
	explicit Goods( const string& cat, const string& name )
		:m_catergry( cat ), m_name( name )
	{
	}
	GOODS_PTR clone(  )
	{
		string name( "default" );
		GOODS_PTR ptr( new Goods( m_catergry, name ) );
		return ptr;
	}
	void setName( const string& name )
	{
		m_name = name;
	}

	void toString(  )
	{
		cout<<"cat: "<<m_catergry<<" name: "<<m_name<<endl;
	}
	~Goods(  )
	{
		cout<<"---------goods destroy"<<endl;
	}
private:
	string m_catergry;
	string m_name;
};

int main( void )
{
	string cat( "mobile" );
	string name( "IPhone 6" );
	Goods goods( cat, name );
	goods.toString(  );
	
	string another( "samsung S6" );
	GOODS_PTR ptr = goods.clone(  );
	ptr->toString(  );
	ptr->setName( another  );
	ptr->toString(  );
	
	return 0;
}
