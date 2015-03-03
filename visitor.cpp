#include <vector>
#include <iostream>

using namespace std;

class IVisitor;
class FileElement;
class FolderElement;

// abstract element
class IElement
{
public:
	virtual void accept( IVisitor* visitor ) = 0;
	virtual ~IElement(  )
	{
	}
};

class IVisitor
{
public:
	virtual void doVisit( FileElement* elem ) = 0;
	virtual void doVisit( FolderElement* elem ) = 0;
	virtual ~IVisitor(  )
	{
	}
};

class DefaultVisitor : public IVisitor
{
public:
	virtual void doVisit( FileElement* elem )
	{
	}
	virtual void doVisit( FolderElement* elem )
	{
	}
	virtual ~DefaultVisitor(  )
	{
	}
};

class FileVisitor : public DefaultVisitor
{
public:
	virtual void doVisit( FileElement* elem )
	{
		cout<<"This is a file"<<endl;
	}
};

class FolderVisitor : public DefaultVisitor
{
public:
	virtual void doVisit( FolderElement* elem )
	{
		cout<<"This is a folder"<<endl;
	}
};

class FileFolderVisitor : public DefaultVisitor
{
public:
	virtual void doVisit( FileElement* elem )
	{
		cout<<"This is a file"<<endl;
	}

	virtual void doVisit( FolderElement* elem )
	{
		cout<<"This is a folder"<<endl;
	}

};

class FileElement : public IElement
{
public:
	virtual void accept( IVisitor* visitor )
	{
		visitor->doVisit( this );
	}
};

class FolderElement : public IElement
{
public:
	virtual void accept( IVisitor* visitor )
	{
		visitor->doVisit( this );
	}
};

class FileSystem
{
public:
	void addElement( IElement* p )
	{
		m_Elements.push_back( p );
	}
	void applyVisitor( IVisitor* visitor )
	{
		vector<IElement*>::iterator it = m_Elements.begin(  );
		for( ; it != m_Elements.end(  ); it++ )
		{
			IElement* elem = *it;
			elem->accept( visitor );
		}
	}
private:
	vector<IElement*> m_Elements;
};


static FileSystem fs;

int main( void )
{

	FileElement fileElem;
	FolderElement folderElem;

	fs.addElement( &fileElem );
	fs.addElement( &folderElem );

	FileVisitor fileVisitor;
	cout<<"file visitor----"<<endl;
	fs.applyVisitor( &fileVisitor );
	
	FolderVisitor folderVisitor;
	cout<<"folder visitor----"<<endl;
	fs.applyVisitor( &folderVisitor );

	FileFolderVisitor filefoldervisitor;
	cout<<"file folder visitor----"<<endl;
	fs.applyVisitor( &filefoldervisitor );
	
	return 0;
}
