#pragma once

class BaseViewItem;

class VETreeWidgetItem : public QTreeWidgetItem
{
public:

  VETreeWidgetItem( BaseViewItem *viewItem );
  ~VETreeWidgetItem();

  BaseViewItem *getViewItem() const;

private:

  BaseViewItem *m_viewItem;
};