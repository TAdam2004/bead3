#include "/Users/tadam/Documents/BevProg2/ITK_graphicslib-master/graphics.hpp"
#include "WidgetContainer.hpp"
#include "AmobaGame.hpp"
#include "GameBoardWidget.hpp"

using namespace genv;

const int XX = 600;
const int YY = 600;

int main() {
    gout.open(XX, YY);
    gout << font("LiberationSans-Regular.ttf", 30);

    WidgetContainer wc;
    GameBoardWidget* board = new GameBoardWidget(50, 50, 500);
    wc.addWidget(board);

    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        gout << move_to(0, 0) << color(255, 255, 255) << box(XX, YY);
        wc.handleEvent(ev);
        wc.drawWidgets();
        gout << refresh;
    }

    delete board;
    return 0;
}
