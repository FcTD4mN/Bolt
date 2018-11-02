#pragma once

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLWidget :
    public QWidget,
    public sf::RenderWindow
{
    Q_OBJECT

public:
    // Construction / Destruction
    virtual  ~QSFMLWidget();
    QSFMLWidget( QWidget* iParent = NULL );

private :
    // Private API
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnDraw();
protected:
    // Events overrides
    virtual void showEvent(QShowEvent*)  override;
    virtual void paintEvent(QPaintEvent*)  override;

protected:
#ifdef WINDOWS
    // Protected Qt / WinAPI native events override
    virtual  bool  nativeEvent( const  QByteArray& eventType, void* message, long* result )  override;
#endif // WINDOWS

private:
    // Behaviour override
    virtual QPaintEngine* paintEngine() const  override;

private:
    QTimer  mTimer;
    bool    mInitialized;
};

