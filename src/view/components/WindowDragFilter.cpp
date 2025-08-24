#include "WindowDragFilter.hpp"

WindowDragFilter::WindowDragFilter(QWidget *targetWindow, QObject *parent)
    : QObject(parent), m_targetWindow(targetWindow) {}

bool WindowDragFilter::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_dragging = true;
            m_dragPosition = QCursor::pos() - m_targetWindow->frameGeometry().topLeft();
            return true;
        }
    } else if (event->type() == QEvent::MouseMove && m_dragging) {
        m_targetWindow->move(QCursor::pos() - m_dragPosition);
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease && m_dragging) {
        m_dragging = false;
        return true;
    }

    return QObject::eventFilter(object, event); 
}
