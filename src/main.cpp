
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <thread>  // For std::thread, std::this_thread


import game;
import ui;
import timer_thread;
import auto_clipper_thread;
import wire_market_thread;

int main() {
    Game game;

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    //thread for auto sell
    timer_thread::TimerThread auto_sell_thread(game.getPublicDemand());
    std::thread([&]() {
        auto_sell_thread.auto_sell_paperclips(
            game.getUnsoldPaperclips(),
            game.getFunds(),
            game.getPrice(),
            screen);
    }).detach();

    //thread for auto clippers
    auto_clipper_thread::AutoClipper auto_clipper_thread(game.getAutoClipperLevel());
    std::thread([&]() {
        auto_clipper_thread.auto_make_paperclips(screen,game);
    }).detach();

    //thread for wire market
    wire_market_thread::WireMarket wire_market_thread{};
    std::thread([&]() {
        wire_market_thread.start_market(screen,game);
    }).detach();


    StartUI(game, screen);
    return 0;
}

