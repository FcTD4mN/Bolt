#include "Editor.Widgets.TreeViewDebug.h"

#include <qpointer.h>
#include <qapplication.h>
#include <qclipboard.h>
#include <qpainter.h>
#include <qstyle.h>
#include <QDragEnterEvent>

cTreeViewDebug::~cTreeViewDebug()
{
}


cTreeViewDebug::cTreeViewDebug( QWidget * Parent ) :
    tSuperClass( Parent )
{
}


void
cTreeViewDebug::dragEnterEvent( QDragEnterEvent * iEvent )
{
	tSuperClass::dragEnterEvent( iEvent );
	printf( "DragEventEnter happened\n" );
}


void
cTreeViewDebug::dragMoveEvent( QDragMoveEvent * iEvent )
{
	printf( "DragEventMove happened\n" );
	tSuperClass::dragMoveEvent( iEvent );
}


void
cTreeViewDebug::dragLeaveEvent( QDragLeaveEvent * iEvent )
{
	tSuperClass::dragLeaveEvent( iEvent );
	printf( "DragEventLeave happened\n" );
}


void
cTreeViewDebug::mouseMoveEvent( QMouseEvent * iEvent )
{
	tSuperClass::mouseMoveEvent( iEvent );
	printf( "mousemove\n" );
}


void
cTreeViewDebug::moveEvent( QMoveEvent * iEvent )
{
	tSuperClass::moveEvent( iEvent );
	printf( "m\n" );
}
