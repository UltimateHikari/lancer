#include "inventory.hpp"

#include <vector>
#include <memory>
#include "model/entities.hpp"
#include "model/model.hpp"
#include <ftxui/component/event.hpp> 



namespace sc{


ftxui::Element RenderModule(std::pair<ent::Module, int>& module){
    using namespace ftxui;
    return hbox({
             text(module.first.type.name),
             separator(),
             text(module.first.name),
             separator(),
             text(std::to_string(module.second))
             | size(WIDTH, EQUAL, 800) | xflex,
         }) |
         xflex;
}

ftxui::Element RenderCommodity(std::pair<ent::Commodity, int>& commodity){
    using namespace ftxui;
    return hbox({
             text(commodity.first.type.name),
             separator(),
             text(commodity.first.name),
             separator(),
             text(std::to_string(commodity.second))
             | size(WIDTH, EQUAL, 800) | xflex,
         }) |
         xflex;
}

ftxui::Element RenderLines(Game& game){
    ftxui::Elements lines;    
    auto& model = game.getModel();
    auto modules = model.get_modules();
    auto commodities = model.get_commodities();
    for(auto& i: modules){
        lines.push_back(RenderModule(i));
    }
    for(auto& i: commodities){
        lines.push_back(RenderCommodity(i));
    }

    if(lines.empty()){
        lines.push_back(ftxui::text("Inventory empty"));
    }

    return vbox(std::move(lines)) | ftxui::border;
}

class InventoryBase : public ftxui::ComponentBase{
private:
    std::shared_ptr<std::vector<ent::Commodity>> commodities;
    std::shared_ptr<std::vector<ent::Module>> modules;
    Model& model;

    int selected_ = 0;
    int size_ = 0;
    ftxui::Box box_;
    bool Focusable() const final { return true; }

    

    bool OnEvent(ftxui::Event event) final{
        using namespace ftxui;
        if (event.is_mouse() && box_.Contain(event.mouse().x, event.mouse().y))
        TakeFocus();

        int selected_old = selected_;
        if (event == Event::ArrowUp || event == Event::Character('k') ||
            (event.is_mouse() && event.mouse().button == Mouse::WheelUp)) {
        selected_--;
        }
        if ((event == Event::ArrowDown || event == Event::Character('j') ||
            (event.is_mouse() && event.mouse().button == Mouse::WheelDown))) {
        selected_++;
        }
        if (event == Event::PageDown)
        selected_ += box_.y_max - box_.y_min;
        if (event == Event::PageUp)
        selected_ -= box_.y_max - box_.y_min;
        if (event == Event::Home)
        selected_ = 0;
        if (event == Event::End)
        selected_ = size_;

        selected_ = std::max(0, std::min(size_ - 1, selected_));
        return selected_old != selected_;
    }
public:
    ftxui::Element Render() final{
        using namespace ftxui;
        auto focused = Focused() ? focus : ftxui::select;
        auto style = Focused() ? inverted : nothing;

        ftxui::Element background = ComponentBase::Render();
        background->ComputeRequirement();
        size_ = background->requirement().min_y;
        return dbox({
                std::move(background),
                vbox({
                    text(L"") | size(HEIGHT, EQUAL, selected_),
                    text(L"") | style | focused,
                }),
            }) |
           vscroll_indicator | yframe | yflex | reflect(box_);
    }
    InventoryBase(Game& game):
        model{game.getModel()}
    {Add(ftxui::Renderer([&]{return RenderLines(game);}));}
};

ftxui::Component Inventory(Game& game) {
  return ftxui::Make<InventoryBase>(game);
}

}