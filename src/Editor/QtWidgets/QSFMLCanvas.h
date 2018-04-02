#include <SFML/Graphics.hpp>

#include <QtWidgets/qwidget.h>
#include <QtCore/qtimer.h>

class QSFMLCanvas :
    public QWidget,
    public sf::RenderWindow
{
public:
    virtual ~QSFMLCanvas();
    QSFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0 );
    QSFMLCanvas( QWidget* Parent );


public:
    sf::RenderWindow* Window();

private:
    virtual void OnInit();
    virtual void OnUpdate();
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent( QShowEvent* );
    virtual void paintEvent( QPaintEvent* );

protected:
    sf::RenderWindow* mRenderWindow;
    QTimer mTimer;
    bool   mInitialized;
};

