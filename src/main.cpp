#include <ftxui/component/component.hpp>  // For components
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <ftxui/dom/elements.hpp>  // For elements
#include <thread>  // For std::thread, std::this_thread
#include <chrono>  // For std::chrono
#include <atomic>  // For std::atomic
#include <cmath>   // For std::pow
#include <string>  // For std::to_string

int main()
{
    using namespace ftxui;
    using namespace std;

    // Variables principales
    atomic<int> paperclip_count{0};
    atomic<int> unsold_paperclips{0};
    atomic<float> price{0.50};
    atomic<int> marketing_level{0};
    atomic<float> public_demand{0.16};
    atomic<float> funds{0.0};
    atomic<int> marketing_cost{200};


    // Calcul de la Public Demand avec la nouvelle formule
    auto calculate_public_demand = [&]()
    {
        public_demand = pow(1.2, marketing_level.load()) * (8.0 / price.load());
    };


    // Initialisation de la Public Demand
    calculate_public_demand();

    // Fonction de vente automatique


    // Boutons et leur logique
    auto make_paperclip_button = Button("Make Paperclip", [&]
    {
        paperclip_count.store(paperclip_count.load() + 1);
        unsold_paperclips.store(unsold_paperclips.load() + 1);
    });

    auto decrease_price_button = Button("Decrease Price", [&]
    {
        if (price.load() > 0.01f)
        {
            price.store(price.load() - 0.01f);
            calculate_public_demand();
        }
    });

    auto increase_price_button = Button("Increase Price", [&]
    {
        price.store(price.load() + 0.01f);
        calculate_public_demand();
    });

    auto buy_marketing_button = Button("Increase Marketing", [&]
    {
        if (funds >= marketing_cost.load())
        {
            funds -= marketing_cost.load();
            ++marketing_level;
            marketing_cost.store(marketing_cost.load() * 2); // Coût exponentiel
            calculate_public_demand();
        }
    });


    // Conteneur des boutons
    auto button_container = Container::Vertical({
        make_paperclip_button,
        decrease_price_button,
        increase_price_button,
        buy_marketing_button,
    });

    // Rendu global de l'interface
    auto layout = Renderer(button_container, [&]
    {
        return vbox({
            text("Paperclips: " + to_string(paperclip_count.load())) | bold,
            text("Unsold Paperclips: " + to_string(unsold_paperclips.load())) | bold,
            text("Funds: $" + to_string(funds.load()).substr(0, 5)) | bold | color(Color::Green),
            separator(),
            text("Price: $" + to_string(price.load()).substr(0, 4)) | color(Color::Yellow),
            hbox({
                decrease_price_button->Render() | flex,
                increase_price_button->Render() | flex,
            }),
            separator(),
            text("Marketing Level: " + to_string(marketing_level.load())) | bold,
            text("Next Marketing Cost: $" + to_string(marketing_cost.load())) | color(Color::Yellow),
            text("Public Demand: " + to_string(static_cast<int>(public_demand.load())) + "%") | bold | color(
                Color::Cyan),
            buy_marketing_button->Render(),
            separator(),
            make_paperclip_button->Render(),
        }) | border;
    });

    // Boucle principale
    auto screen = ScreenInteractive::TerminalOutput();


    auto auto_sell_paperclips = [&]()
    {
        while (true)
        {
            this_thread::sleep_for(chrono::seconds(1)); // Simulation de temps
            screen.PostEvent(Event::Custom);
            int to_sell = static_cast<int>(public_demand.load()); // Basé sur PD
            if (unsold_paperclips.load() > 0 && to_sell > 0)
            {
                int sold = min(unsold_paperclips.load(), to_sell);
                unsold_paperclips -= sold;
                funds += sold * price.load();
            }
        }
    };

    // Lancement de la vente automatique dans un thread
    thread(auto_sell_paperclips).detach();

    screen.Loop(layout);
    return 0;
}
