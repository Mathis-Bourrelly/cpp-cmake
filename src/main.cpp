
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <thread>  // For std::thread, std::this_thread
#include <windows.h>


import game;
import ui;
import timer_thread;
import auto_clipper_thread;
import wire_market_thread;
import trading_thread;


#include <windows.h>



int main() {
    SMALL_RECT WinRect = {0, 0, 110, 40};   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
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
    WireMarket wire_market_thread{};
    std::thread([&]() {
        wire_market_thread.start_market(screen,game);
    }).detach();

    TradingThread trading_thread(game);
    std::thread([&]() {
        trading_thread.start(screen);
    }).detach();

    trading_thread.depositFunds();
    StartUI(game,trading_thread,screen);

    return 0;

}

