module;

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/table.hpp>
export module ui;

import game;
import upgrade;
import trading_thread;

using namespace ftxui;


export void StartUI(Game& game/*, TradingThread& trading_thread*/, auto& screen)
{
    //std::vector<std::string> risk_options = {"Low", "Medium", "High"};
    //int selected_risk = 0;
    auto stock_increase_button = Button("+", [&] { game.setMinimumStock(game.getMinimumStock() + 10); });
    auto stock_decrease_button = Button("-", [&] { game.setMinimumStock(game.getMinimumStock() - 10); });

    auto price_increase_button = Button("+", [&] { game.setMaxPrice(game.getMaxPrice() + 1); });
    auto price_decrease_button = Button("-", [&] { game.setMaxPrice(game.getMaxPrice() - 1); });

    auto make_paperclip_button = Button("Make Paperclip", [&] { game.makePaperclip(1); });
    auto decrease_price_button = Button("Decrease Price", [&] { game.decreasePrice(); });
    auto increase_price_button = Button("Increase Price", [&] { game.increasePrice(); });
    auto buy_marketing_button = Button("Increase Marketing", [&] { game.buyMarketing(); });
    auto buy_autoclipper_button = Button("Buy Auto Clipper", [&] { game.buyAutoClipper(); });
    auto buy_wire_button = Button("Buy Wire", [&] { game.buyWire(); });
    auto buy_wire_buyer_button = Button("Buy Wire Buyer", [&] { game.buyWireBuyer(); });


    auto upgrade1 = std::make_shared<upgrade::Upgrade>(1, "Improved AutoClippers", "Increases performance by 25%", 70,
                                                       3000, 25);
    auto upgrade1Button = Button("Buy", [&] { game.purchaseUpgrade(upgrade1); });
    auto upgrade2 = std::make_shared<upgrade::Upgrade>(2, "Even Better AutoClippers", "Increases performance by 50%",
                                                       150, 5000, 50);
    auto upgrade2Button = Button("Buy", [&] { game.purchaseUpgrade(upgrade2); });
    auto upgrade3 = std::make_shared<upgrade::Upgrade>(3, "Optimized AutoClippers", "Increases performance by 75%", 250,
                                                       10000, 75);
    auto upgrade3Button = Button("Buy", [&] { game.purchaseUpgrade(upgrade3); });

    //auto dropdownRisk = Dropdown(&risk_options, &selected_risk);
    //auto depositeButton = Button("Deposit", [&] { trading_thread.depositFunds(); });
    //auto withdrawButton = Button("Withdraw", [&] { trading_thread.withdrawFunds(); });

    auto button_container = Container::Vertical({
        stock_increase_button,
        stock_decrease_button,
        price_increase_button,
        price_decrease_button,

        make_paperclip_button,
        decrease_price_button,
        increase_price_button,
        buy_marketing_button,
        buy_autoclipper_button,
        buy_wire_button,
        buy_wire_buyer_button,
        upgrade1Button,
        upgrade2Button,
        upgrade3Button,
        //dropdownRisk,
        //depositeButton,
        //withdrawButton,
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
                    text("Performance: " + std::to_string(100 + game.getAutoclipperPerformance()) + "%"),
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

                (game.getWireBuyerState()
                     ? vbox({
                         text("Wire Buyer") | color(game.getWireBuyerState() ? Color::Green : Color::Red),
                         vbox({
                             text("Minimum Stock: " + std::to_string(game.getMinimumStock())),
                             hbox({
                                 stock_decrease_button->Render() | flex,
                                 stock_increase_button->Render() | flex,
                             }),
                         }),
                         separator(),
                         vbox({
                             text("Max Price: $" + std::to_string(game.getMaxPrice())),
                             hbox({
                                 price_decrease_button->Render() | flex,
                                 price_increase_button->Render() | flex,
                             }),
                         }),
                     }) | flex
                     : vbox({
                         text("Wire Buyer") | color(game.getWireBuyerState() ? Color::Green : Color::Red),
                         text("Cost : $100") | color(Color::Yellow),
                         buy_wire_buyer_button->Render(),
                     })),
                separator(),
                vbox({
                    (game.isUpgradePurchased(upgrade1->id) || game.getPaperclipCount() < upgrade1->paperclip_requirement
                         ? text("")
                         : vbox({
                             text(upgrade1->name) | bold,
                             text(upgrade1->description),
                             text("Cost: $" + std::to_string(upgrade1->cost)) | color(Color::Yellow),
                             upgrade1Button->Render(),
                         })),

                    (game.isUpgradePurchased(upgrade2->id) || game.getPaperclipCount() < upgrade2->paperclip_requirement
                         ? text("")
                         : vbox({
                             text(upgrade2->name) | bold,
                             text(upgrade2->description),
                             text("Cost: $" + std::to_string(upgrade2->cost)) | color(Color::Yellow),
                             upgrade2Button->Render(),
                         })),

                    (game.isUpgradePurchased(upgrade3->id) || game.getPaperclipCount() < upgrade3->paperclip_requirement
                         ? text("")
                         : vbox({
                             text(upgrade3->name) | bold,
                             text(upgrade3->description),
                             text("Cost: $" + std::to_string(upgrade3->cost)) | color(Color::Yellow),
                             upgrade3Button->Render(),
                         })),
                }),
            }),
            /*separator(),
            vbox({
                text("Investments") | bold | color(Color::Blue),
                hbox({
                    text("Risk Level: " + std::to_string(game.getTradingRiskLevel())) | color(Color::Red),

                    dropdownRisk->Render(),
                    filler(),
                }),
                separator(),
                hbox({
                    depositeButton->Render(),
                    withdrawButton->Render(),
                }),
                hbox({

                }),
                separator(),

            }),*/
        }) | border;
    });
    screen.Loop(layout);
}
