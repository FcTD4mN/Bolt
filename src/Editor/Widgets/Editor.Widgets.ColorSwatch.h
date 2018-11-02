#pragma once

#include <QLabel>


class cColorSwatch :
    public QLabel
{
    Q_OBJECT

public:
    typedef  QLabel  tSuperClass;

public:
    virtual ~cColorSwatch();
    cColorSwatch( QWidget* iParent = nullptr );

public:
    // Events overrides
    void  mouseReleaseEvent( QMouseEvent* iEvent ) override;

public:
    // Set/Get
    void            Color( const QColor& iColor );
    const QColor&   Color() const;

signals:
    void  swatchClicked();

private:
    QColor   mColor;
};

