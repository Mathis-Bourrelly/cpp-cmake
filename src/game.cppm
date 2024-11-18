module;
#include <cmath>
#include <random>
export module game;

export class Game {
public:
    Game();
    void makePaperclip();
    void increasePrice();
    void decreasePrice();
    void calculatePublicDemand();
    void autoSellPaperclips();
    int& getPaperclipCount();
    int& getUnsoldPaperclips();
    float& getPrice();

    float& getPublicDemand();
    float& getFunds();

    void buyMarketing();
    void buyAutoClipper();

    int getMarketingLevel() const;
    int& getAutoClipperLevel();

    float getMarketingCost() const;
    float getAutoClipperCost() const;

private:
    int paperclip_count;
    int unsold_paperclips;
    float price;
    float public_demand;
    float funds;
    int marketing_level;
    int autoclipper_level;
    float marketing_cost;
    float autoclipper_cost;
};

Game::Game():
    paperclip_count(10000),
    unsold_paperclips(10000),
    price(0.10f),
    public_demand(0.16f),
    funds(0.0),
    marketing_level(0),
    autoclipper_level(0),
    marketing_cost(200.0f),
    autoclipper_cost(5.0f)
{
    calculatePublicDemand();
}

void Game::makePaperclip() {
    paperclip_count++;
    unsold_paperclips++;
}

void Game::increasePrice() {
    price += 0.01f;
    calculatePublicDemand();
}

void Game::decreasePrice() {
    price = std::max(0.01f, price - 0.01f);
    calculatePublicDemand();
}

void Game::buyMarketing() {
    if (funds >= marketing_cost) {
        funds -= marketing_cost;
        ++marketing_level;
        marketing_cost *= 2;
        calculatePublicDemand();
    }
}

void Game::buyAutoClipper() {
    if (funds >= autoclipper_cost) {
        funds -= autoclipper_cost;
        ++autoclipper_level;
        autoclipper_cost = pow(1.1f,autoclipper_level)+5;
        calculatePublicDemand();
    }
}

void Game::calculatePublicDemand() {
    public_demand = std::pow(1.1, marketing_level) * (8.001f / price);
}

int& Game::getPaperclipCount() { return paperclip_count; }
int& Game::getUnsoldPaperclips() { return unsold_paperclips; }
float& Game::getPrice() { return price; }
int Game::getMarketingLevel() const { return marketing_level; }
int& Game::getAutoClipperLevel() { return autoclipper_level; }
float& Game::getPublicDemand()  { return public_demand; }
float& Game::getFunds() { return funds; }
float Game::getMarketingCost() const { return marketing_cost; }
float Game::getAutoClipperCost() const { return autoclipper_cost; }
