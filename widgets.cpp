#include "widgets.hpp"

void Widgets::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Widgets::setSize(int width, int height) {
    width_ = width;
    height_ = height;
}

std::pair<int, int> Widgets::getPosition() const {
    return std::make_pair(x_, y_);
}

std::pair<int, int> Widgets::getSize() const {
    return std::make_pair(width_, height_);
}

bool Widgets::isMouseOver(const genv::event& ev) const {
    return ev.pos_x >= x_ && ev.pos_x <= x_ + width_ && ev.pos_y >= y_ && ev.pos_y <= y_ + height_;
}
