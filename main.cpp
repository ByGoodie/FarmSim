#include "App.h"
#include <thread>

int main(void) {
    App app;

    sf::Mutex mtx;

    app.run();

    return 0;
}