#pragma once

#include <vector>
#include "DllExport.h"
#include <QtCore/QVariant.h>

class BaseViewItemCreator;
class BaseViewItem;
class BaseModelItem;

// This factory is responsible for returning the appropriate BaseViewItem
// when creating for a given data type
class VALUEEDIT_API ViewItemFactory /*sealed*/
{
	Q_DISABLE_COPY(ViewItemFactory)

private:
	// Friend ViewItemCreator to allow it to 
	// register itself with us
	friend class BaseViewItemCreator;

#pragma warning(push)
#pragma warning(disable: 4251)
	std::vector<BaseViewItemCreator*> m_creators;
#pragma warning(pop)

protected:

	typedef std::vector<BaseViewItemCreator*>::const_iterator CreatorIT;
	CreatorIT creatorBegin() const { return m_creators.begin(); }
	CreatorIT creatorEnd() const { return m_creators.end(); }

	typedef std::vector<BaseViewItemCreator*>::const_reverse_iterator CreatorRIT;
	CreatorRIT creatorRBegin() const { return m_creators.rbegin(); }
	CreatorRIT creatorREnd() const { return m_creators.rend(); }

	//////////////////////////////////////////////////////////////////////////
	ViewItemFactory();
	~ViewItemFactory();

	// Register arbitrary widget creators 
	// Note - It is not necessary to explicitly register 
	// any ValueCreator, as soon as an instance of the
	// the class is created it will automatically
	// register itself with the system
	bool RegisterCreator(BaseViewItemCreator* creator);
	// DeRegister widget creators.  This is called
	// automatically when an item is released.
	void DeRegisterCreator(BaseViewItemCreator* creator);

	// Create the most appropriate value editor given the following data
	// \data The data being edited.  We create a BaseViewItem that matches the
	//	type of this data.
	// \viewtype[optional] What dimension the data represents.  For example, a 
	//		float can represent any of an angle/ratio/distance etc.
	// \tag[optional] One more piece of metadata, just in case you want to 
	//		only display a value for a tagged value.
	// TODO: Perhaps just pass in a MetaData option here to represent all metadata?
	BaseViewItem* CreateViewItem(
	  BaseModelItem *modelItem,
		QString const &name,
		QVariant const &value,
	  char const *tag
	  );

public:

	static ViewItemFactory* GetInstance();
	//////////////////////////////////////////////////////////////////////////


	// Call this function to build a View layer from the
	// given Model interface.  This will not create any
	// actual widgets
	BaseViewItem* BuildView(BaseModelItem* model);
	
	// Create the most appropriate value editor given the following data
	// \data The data being edited.  We create a BaseViewItem that matches the
	//	type of this data.
	// \viewtype[optional] What dimension the data represents.  For example, a 
	//		float can represent any of an angle/ratio/distance etc.
	// \tag[optional] One more piece of metadata, just in case you want to 
	//		only display a value for a tagged value.
	// TODO: Perhaps just pass in a MetaData option here to represent all metadata?
	BaseViewItem* CreateViewItem(
	  BaseModelItem *modelItem,
	  char const *tag = 0
	  );
	
	// Create the most appropriate value editor given the following data
	// \data The data being edited.  We create a BaseViewItem that matches the
	//	type of this data.
	// \viewtype[optional] What dimension the data represents.  For example, a 
	//		float can represent any of an angle/ratio/distance etc.
	// \tag[optional] One more piece of metadata, just in case you want to 
	//		only display a value for a tagged value.
	// TODO: Perhaps just pass in a MetaData option here to represent all metadata?
	BaseViewItem* CreateViewItem(
		QString const &name,
		QVariant const &value,
	  char const *tag = 0
	  );
};
