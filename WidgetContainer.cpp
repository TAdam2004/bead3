#include "widgetContainer.hpp"

void WidgetContainer::addWidget(Widgets* widget) {
    widgets_.push_back(widget);
}

void WidgetContainer::removeWidget(Widgets* widget) {
    auto it = std::find(widgets_.begin(), widgets_.end(), widget);
    if (it != widgets_.end()) {
        widgets_.erase(it);
    }
}

void WidgetContainer::clearWidgets() {
    widgets_.clear();
}

void WidgetContainer::handleEvent(const genv::event& ev) {
    for (Widgets* widget : widgets_) {
        widget->handleEvent(ev);
    }
}

void WidgetContainer::drawWidgets() const {
    for (const Widgets* widget : widgets_) {
        widget->draw();
    }
}
