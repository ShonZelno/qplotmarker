#include "graphics_coord_item.hpp"


#include <QApplication>
#include <QPainter>
#include <QPalette>
#include <QPen>


GraphicsCoordItem::GraphicsCoordItem(QGraphicsItem * parent)
    : QGraphicsTextItem( parent )
{}

void GraphicsCoordItem::setCoord(qreal value)
{
    m_coord = value;

    if ( m_labelFormat.isEmpty() )

        setPlainText( QString::number( value ) );
    else

        setPlainText( QString::asprintf( m_labelFormat.toUtf8().constData(),
                                         value)                              );
}

qreal GraphicsCoordItem::coord() const
{
    return m_coord;
}

void GraphicsCoordItem::setItemColor(const QColor & itemColor)
{
    m_itemColor = itemColor;

    update();
}

void GraphicsCoordItem::setLabelFormat(const QString & format)
{
    m_labelFormat = format;

    setCoord( m_coord );
}

void GraphicsCoordItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option)

    Q_UNUSED(widget)


    auto palette = qApp->palette();

    painter->setBrush( palette.color( QPalette::Base ) );

    painter->setPen( QPen( m_itemColor, 1 ) );

    painter->drawRect( boundingRect() );


    painter->setPen( palette.color( QPalette::WindowText ) );

    auto rect = boundingRect();

    rect = rect.marginsAdded( { RECT_MARGIN, RECT_MARGIN, 0, 0 } );

    painter->drawText( rect, toPlainText() );
}


