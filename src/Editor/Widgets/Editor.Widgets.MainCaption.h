#pragma once

#ifdef USE_RIVET

#include <RivetDefaultCaption>


class  QLabel;
class  QMenuBar;


namespace nEditor { namespace nWidgets { class cMainCaptionMenuBar; } }


namespace nEditor {
namespace nWidgets {


class cMainCaption :
    public ::Rivet::DefaultCaption
{
    Q_OBJECT

    typedef ::Rivet::DefaultCaption tSuperClass;
    typedef cMainCaption            tSelf;

public:
    // Construction / Destruction
    virtual  ~cMainCaption();
    cMainCaption( QWidget*  parent = NULL );

public:
    // HitTest override
    virtual  bool  HitEmptySpace( long iX, long iY )  override;

public:
    // Restricted Member access API
    cMainCaptionMenuBar*  MenuBar()  const;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Destroy();

protected:
    virtual  void  Compose()  override;

private:
    QLabel* mTitle;
    cMainCaptionMenuBar* mMenuBar;
};


} // nWidgets
} // nEditor

#endif // USE_RIVET
