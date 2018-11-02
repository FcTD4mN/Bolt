#pragma once

#include <QTreeView>
#include <QDropEvent>


class cTreeViewDebug :
    public QTreeView
{
    Q_OBJECT

public:
    typedef QTreeView tSuperClass;

public:
    ~cTreeViewDebug();
	cTreeViewDebug( QWidget *parent = Q_NULLPTR );

public:
	void  dragEnterEvent( QDragEnterEvent* iEvent ) override;
	void  dragMoveEvent( QDragMoveEvent* iEvent ) override;
	void  dragLeaveEvent( QDragLeaveEvent* iEvent ) override;

	void mouseMoveEvent( QMouseEvent* iEvent ) override;
	void moveEvent( QMoveEvent* iEvent ) override;
/*
inline bool canDrop(QDropEvent *event) {
	const QMimeData *mime = event->mimeData();

	// Drag enter event shall always be accepted, if mime type and action match.
	// Whether the data can actually be dropped will be checked in drag move.
	if (event->type() == QEvent::DragEnter && (event->dropAction() & model->supportedDropActions()))
	{
		const QStringList modelTypes = model->mimeTypes();
		for (const auto &modelType : modelTypes) {
			if (mime->hasFormat(modelType))
				return true;
		}
	}*/
};



