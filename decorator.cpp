#include <iostream>

using namespace std;

class IComponent
{
public:
	virtual void draw(  ) = 0;
	virtual ~IComponent(  )
	{
	}
};

class Button : public IComponent
{
public:
	void draw(  )
	{
		cout<<"draw button"<<endl;
	}
};

class ButtonDecorator : public IComponent
{
public:
	explicit ButtonDecorator( IComponent* comp )
		:m_Comp( comp )
	{
	}
	void draw(  )
	{
		cout<<"draw picture"<<endl;
		m_Comp->draw(  );
	}

private:
	IComponent* m_Comp;
};


int main( void )
{
	Button button;
	ButtonDecorator bd( &button );
	bd.draw(  );
	
	return 0;
}
