#pragma once

#include "BaseViewItemCreator.h"

class FloatViewItemCreator : public BaseViewItemCreator
{
public:
	FloatViewItemCreator();
	~FloatViewItemCreator();

	virtual BaseViewItem* CreateItem(const QVariant& data, const QString& name, const char* tag) override;
};