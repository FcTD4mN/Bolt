#include "Editor.Delegates.EntityProperties.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.Entity.h"

#include "Core.Registries.ComponentRegistry.h"

#include <QComboBox>
#include <QPainter>
#include <QPushButton>
#include <QApplication>
#include <QMouseEvent>
#include <QDialog>


cEntityPropertiesDelegate::cEntityPropertiesDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mEntity( 0 )
{
}


void cEntityPropertiesDelegate::paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if( index.data() == "compAnimations" && index.column() == 1 )
    {
        QStyleOptionButton button;
        button.rect = option.rect;
        button.text = "Edit";
        button.state = QStyle::State_Enabled;

        QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter );
    }
    else
    {
        tSuperClass::paint( painter, option, index );
    }
}


QWidget*
cEntityPropertiesDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    auto tcheck = iIndex.data();
    if( iIndex.parent().data() == "Components" && iIndex.column() == 0 )
        return  new QComboBox( iParent );

    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cEntityPropertiesDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    if( mEntity && iIndex.parent().data() == "Components" )
    {
        auto combo = dynamic_cast< QComboBox* >( iEditor );
        if( combo )
        {
            QString currentComponentName = iIndex.data( Qt::DisplayRole ).toString();
            combo->addItem( currentComponentName );

            for( int i = 0; i < ::nCore::nRegistries::cComponentRegistry::Instance()->ItemCount(); ++i )
            {
                auto component = ::nCore::nRegistries::cComponentRegistry::Instance()->GetItemAtIndex( i );
                std::string compName = component->Name();

                if( mEntity->GetComponentByName( compName ) == nullptr ) // We can only see components that are not already in the entity
                {
                    if( component->Name() != currentComponentName.toStdString() )
                    {
                        combo->addItem( component->Name().c_str() );
                    }
                }
            }
        }
    }
    else
    {
        tSuperClass::setEditorData( iEditor, iIndex );
    }
}


void
cEntityPropertiesDelegate::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
{
    if( iIndex.parent().data() == "Components" )
    {
        auto combo = dynamic_cast<QComboBox*>( iEditor );
        if( combo && combo->currentIndex() > 0 ) // index 0 means we selected the same component, so no need to change anything
            iModel->setData( iIndex, combo->currentText() );
    }
    else
    {
        tSuperClass::setModelData( iEditor, iModel, iIndex );
    }
}


bool
cEntityPropertiesDelegate::editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &iIndex )
{
    if( event->type() == QEvent::MouseButtonRelease )
    {
        if( iIndex.data() == "compAnimations" && iIndex.column() == 1 )
        {
            QMouseEvent * e = (QMouseEvent *)event;
            int clickX = e->x();
            int clickY = e->y();

            if( option.rect.contains( clickX, clickY ) )
            {
                QDialog * d = new QDialog();
                d->setGeometry( 20, 30, 100, 100 );
                d->show();
                // Here we should bring animation editor to front or something
            }

            return  true;
        }
    }

    return  tSuperClass::editorEvent( event, model, option, iIndex );
}

void
cEntityPropertiesDelegate::SetEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    mEntity = iEntity;
}
