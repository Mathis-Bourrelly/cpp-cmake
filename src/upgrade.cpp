module;
#include <functional>
#include <string>

export module upgrade;

export namespace upgrade

{
    class Upgrade
    {
    public:
        int id;
        std::string name;
        std::string description;
        int cost;
        int paperclip_requirement;
        int perf;

        Upgrade(int id, std::string name, std::string description, int cost, int paperclip_requirement, int perf)
            : id(id),
              name(name),
              description(description),
              cost(cost),
              paperclip_requirement(paperclip_requirement),
              perf(perf){}

    };
};
