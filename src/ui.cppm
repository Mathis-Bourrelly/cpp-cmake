module;

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
export module ui;

import game;

using namespace ftxui;

export void StartUI(Game& game, auto& screen)
{

    std::string stock_temp = std::to_string(game.getMinimumStock());
    std::string price_temp = std::to_string(game.getMaxPrice());

    auto make_paperclip_button = Button("Make Paperclip", [&] { game.makePaperclip(1); });
    auto decrease_price_button = Button("Decrease Price", [&] { game.decreasePrice(); });
    auto increase_price_button = Button("Increase Price", [&] { game.increasePrice(); });
    auto buy_marketing_button = Button("Increase Marketing", [&] { game.buyMarketing(); });
    auto buy_autoclipper_button = Button("Buy Auto Clipper", [&] { game.buyAutoClipper(); });
    auto buy_wire_button = Button("Buy Wire", [&] { game.buyWire(); });
    auto buy_wire_buyer_button = Button("Buy Wire Buyer", [&] { game.buyWireBuyer(); });

    auto stock_input = Input(&stock_temp, "Enter Minimum Stock");
    auto price_input = Input(&price_temp, "Enter Max Price");
    auto apply_buyer_button = Button("Apply", [&] {
                int stock_value = std::stoi(stock_temp);
                int price_value = std::stoi(price_temp);
                game.setMinimumStock(stock_value);
                game.setMaxPrice(price_value);});


    auto button_container = Container::Vertical({
        make_paperclip_button,
        decrease_price_button,
        increase_price_button,
        buy_marketing_button,
        buy_autoclipper_button,
        buy_wire_button,
        buy_wire_buyer_button,
        stock_input,
        price_input,
        apply_buyer_button,
    });

    auto layout = Renderer(button_container, [&]
    {
        return vbox({
            hbox({
                filler(),
            text(game.getEventText()) | bgcolor(Color::Yellow) | color(Color::Black) | border,
                filler(),
            }),
            separator(),
            hbox({
                vbox({
                    text("Paperclips: " + std::to_string(game.getPaperclipCount())),
                    text("Unsold Paperclips: " + std::to_string(game.getUnsoldPaperclips())),
                    text("Funds: $" + std::format("{0:.2f}", game.getFunds())) | color(Color::Green),
                }),
                separator(),
                make_paperclip_button->Render() | flex,
            }),
            separator(),
            text("Price: $" + std::format("{0:.2f}", game.getPrice())) | color(Color::Yellow),
            text("Public Demand: " + std::to_string(static_cast<int>(game.getPublicDemand())) + "%") |
            color(Color::Cyan),
            hbox({
                decrease_price_button->Render() | flex,
                increase_price_button->Render() | flex,
            }),
            separator(),
            hbox({
                vbox({
                    text("Marketing Level: " + std::to_string(game.getMarketingLevel())),
                    text("Cost: $" + std::format("{0:.2f}", game.getMarketingCost())) | color(Color::Yellow),
                    buy_marketing_button->Render(),
                }),
                separator(),
                vbox({
                    text("Auto Clippers: " + std::to_string(game.getAutoClipperLevel())),
                    text("Cost: $" + std::format("{0:.2f}", game.getAutoClipperCost())) | color(Color::Yellow),
                    buy_autoclipper_button->Render(),
                }),
                separator(),
                vbox({
                    text("Wire Stock: " + std::to_string(game.getWireStock())),
                    text("Wire Price: $" + std::format("{0:.2f}", game.getWirePrice())) | color(Color::MagentaLight),
                    buy_wire_button->Render(),
                }),
                separator(),
                vbox({
                    text("Wire Buyer") | color(game.getWireBuyerState() ? Color::Green : Color::Red),
                    text("Cost : $1") | color(Color::Yellow),
                    buy_wire_buyer_button->Render(),
                }),
                vbox({
                    text("Minimum Stock"),
                    stock_input->Render() | size(HEIGHT,EQUAL,1),
                    text("Max Price"),
                    price_input->Render() | size(HEIGHT,EQUAL,1),
                }),
                apply_buyer_button->Render() | size(WIDTH,EQUAL,8),
            })
        }) | border;
    });
    screen.Loop(layout);
}
