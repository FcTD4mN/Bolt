#include "Editor.Widgets.Animation.DialogSpriteSheet.h"




cDialogSpriteSheet::~cDialogSpriteSheet()
{
}


cDialogSpriteSheet::cDialogSpriteSheet( QWidget* iParent ) :
    tSuperClass( iParent )
{
    ui.setupUi( this );
}


int
cDialogSpriteSheet::GetNumberOfRows() const
{
    return  ui.numberOfRowsSpinBox->value();
}


int
cDialogSpriteSheet::GetNumberOfColumns() const
{
    return  ui.numberOfColumnsSpinBox->value();
}



