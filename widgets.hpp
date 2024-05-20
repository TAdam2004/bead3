#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <utility>
#include "/Users/tadam/Documents/BevProg2/ITK_graphicslib-master/graphics.hpp"

class Widgets {
public:
    virtual ~Widgets() {}
    virtual void draw() const = 0;
    virtual void handleEvent(const genv::event& ev) = 0;
    virtual bool isMouseOver(const genv::event& ev) const;
    void setPosition(int x, int y);
    void setSize(int width, int height);
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getSize() const;

protected:
    int x_, y_;
    int width_, height_;
};

#endif // WIDGETS_HPP
