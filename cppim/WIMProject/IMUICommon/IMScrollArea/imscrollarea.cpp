#include "imscrollarea.h"

#include <QScrollBar>

class IMScrollAreaPrivate
{
public:
    IMScrollAreaPrivate()
    {

    }
};

IMScrollArea::IMScrollArea( QWidget * parent ):
    QScrollArea(parent),d_ptr( new IMScrollAreaPrivate )
{
    installEventFilter(this);
    setLineWidth(0);
    setWidgetResizable(true);
    setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);
    horizontalScrollBar()->setVisible( false );
    horizontalScrollBar()->setEnabled( false );
    setContentsMargins(0,0,0,0);
}

IMScrollArea::~IMScrollArea()
{

}
