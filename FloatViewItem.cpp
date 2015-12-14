#include "FloatViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QSpinBox.h>
#include <assert.h>

FloatViewItem::FloatViewItem(
  QString const &name,
  QVariant const &value
  )
  : BaseViewItem(name)
{
  m_spinner = new QDoubleSpinBox;
  connect(
    m_spinner, SIGNAL( valueChanged( double ) ), 
    this, SLOT( OnSpinnerChanged( double ) )
    );
  connect(
    m_spinner, SIGNAL( editingFinished() ), 
    this, SLOT( OnEditFinished() )
    );
  UpdateViewValue( value );
}

FloatViewItem::~FloatViewItem()
{
}

QWidget *FloatViewItem::getWidget()
{
  return m_spinner;
}

void FloatViewItem::UpdateViewValue( QVariant value )
{
  m_spinner->setValue( value.toDouble() );
}

void FloatViewItem::OnSpinnerChanged( double value )
{
  emit ViewValueChanged(
    QVariant::fromValue<double>( m_spinner->value() ),
    GetName(),
    0
    );
}

void FloatViewItem::OnEditFinished()
{
  emit ViewValueChanged(
    QVariant::fromValue<double>( m_spinner->value() ),
    GetName(),
    1
    );
}

//////////////////////////////////////////////////////////////////////////
// 
static FloatViewItem* CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
  if ( value.type() == QVariant::Double
    || value.type() == QMetaType::Float )
  {
    return new FloatViewItem( name, value );
  }
  return nullptr;
}

EXPOSE_VIEW_ITEM( FloatViewItem, CreateItem, 3 );
