#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

namespace  nQt::nModels     { class cEntityListModel; }
namespace  nQt::nModels     { class cProjectHierarchyModel; }
namespace  nCore::nProject  { class cProject; }

class cProjectEditor;
class cPropertyEditor;
class cAnimationsComponentEditor;
class QDockWidget;


namespace  nEditor::nMainWindows {

class cBoltEditor :
    public QMainWindow
{
    Q_OBJECT

public:
    ~cBoltEditor();
    cBoltEditor(QWidget *parent = Q_NULLPTR);

    void Setup();

public slots:
    // Project
    void  NewProject();
    void  OpenProject();

    // Properties
    void  ShowProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );
    void  TogglePropertyEditor();

    // Animations
    void  ToggleAnimationsComponentEditor();

    void  UpdateMenuInfos();

signals:
    void  CurrentProjectChanged( ::nQt::nModels::cProjectHierarchyModel* iProject );

private:
    Ui::BoltEditorClass ui;
    ::nQt::nModels::cEntityListModel*   mPrototypeListModel;
    ::nCore::nProject::cProject*        mProject; // The project the editor is editing


    // Editors
        // Property
    cPropertyEditor*                mPropertyEditor;
    QDockWidget*                    mPropertyEditorDock;

        // Project
    cProjectEditor*                 mProjectEditor;
    QDockWidget*                    mProjectEditorDock;

        // Animation
    cAnimationsComponentEditor*     mAnimationsComponentEditor;
    QDockWidget*                    mAnimationsComponentEditorDock;
};


} // nEditor::nMainWindows

