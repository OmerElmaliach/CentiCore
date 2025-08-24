#pragma once

#include <QObject>
#include <QPoint>
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QCursor>

class WindowDragFilter : public QObject {
    Q_OBJECT

private:
    QWidget *m_targetWindow;
    QPoint m_dragPosition;
    bool m_dragging = false;

public:
    explicit WindowDragFilter(QWidget *targetWindow, QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
};
