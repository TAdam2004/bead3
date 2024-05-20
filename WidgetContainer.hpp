#ifndef WIDGET_CONTAINER_HPP
#define WIDGET_CONTAINER_HPP

#include <vector>
#include "widgets.hpp"

class WidgetContainer {
protected:
    std::vector<Widgets*> widgets_;

public:
    virtual ~WidgetContainer() {}
    virtual void addWidget(Widgets* widget);
    virtual void removeWidget(Widgets* widget);
    virtual void clearWidgets();
    virtual void handleEvent(const genv::event& ev);
    virtual void drawWidgets() const;
};

#endif // WIDGET_CONTAINER_HPP
