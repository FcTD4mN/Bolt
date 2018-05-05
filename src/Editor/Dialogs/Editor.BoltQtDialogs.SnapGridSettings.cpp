#include "Editor.BoltQtDialogs.SnapGridSettings.h"


cSnapGridSettings::~cSnapGridSettings()
{
}


cSnapGridSettings::cSnapGridSettings( QWidget * iParent ) :
    tSuperClass( iParent )
{
    ui.setupUi( this );
}


double
cSnapGridSettings::CellWidth() const
{
    return  ui.spinBoxCellWidth->value();
}


double
cSnapGridSettings::CellHeight() const
{
    return  ui.spinBoxCellHeight->value();
}


void
cSnapGridSettings::SetCellWidth( double iWidth )
{
    ui.spinBoxCellWidth->setValue( iWidth );
}


void
cSnapGridSettings::SetCellHeight( double iHeight )
{
    ui.spinBoxCellHeight->setValue( iHeight );
}
