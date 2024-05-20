#ifndef GAME_BOARD_WIDGET_HPP
#define GAME_BOARD_WIDGET_HPP

#include "/Users/tadam/Documents/BevProg2/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"
#include "AmobaGame.hpp"

class GameBoardWidget : public Widgets {
private:
    AmobaGame game;
    int cellSize;
    bool gameWon;

public:
    GameBoardWidget(int x, int y, int size);
    void draw() const override;
    void handleEvent(const genv::event& ev) override;
    void drawCircle(int x, int y, int r) const;
};

#endif
