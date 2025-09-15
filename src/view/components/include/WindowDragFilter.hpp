#pragma once

#include <QObject>
#include <QPoint>
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QCursor>

/**
 * @class WindowDragFilter
 * @brief Event filter that enables dragging functionality for frameless windows.
 * 
 * WindowDragFilter provides mouse-based window dragging capabilities for widgets.
 */
class WindowDragFilter : public QObject {
    Q_OBJECT
    
private:
    QWidget *m_targetWindow;
    QPoint m_dragPosition;
    bool m_dragging = false;

public:
    /**
     * @brief Constructs a window drag filter for the specified target window.
     * 
     * Initializes the drag filter to enable mouse-based dragging functionality
     * for the specified widget.
     * 
     * @param targetWindow The widget that should become draggable when
     *                     mouse events are received. This is typically
     *                     a top-level window, dialog, or frameless widget.
     * @param parent Optional parent QObject for memory management.
     *               Defaults to nullptr.
     */
    WindowDragFilter(QWidget *targetWindow, QObject *parent = nullptr);
    
protected:
    /**
     * @brief Filters events to implement window dragging functionality.
     * 
     * Overrides QObject::eventFilter() to intercept mouse events and implement
     * custom window dragging behavior. Handles mouse press, move, and release
     * events to provide smooth window repositioning. The filter responds to
     * left mouse button interactions and calculates appropriate window movements
     * based on cursor position changes.
     * 
     * @param object The object that generated the event. Used to ensure
     *               events are processed from the correct source widget.
     * @param event The event to be filtered. Mouse events are processed
     *              for dragging functionality while other events are
     *              passed through unchanged.
     * 
     * @return true if the event was handled by the filter and should not
     *         be processed further, false if the event should continue
     *         through the normal event processing chain.
     */
    bool eventFilter(QObject *object, QEvent *event) override;
};