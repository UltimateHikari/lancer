#include "navigation.hpp"

#include <vector>
#include <memory>
#include "model/entities.hpp"
#include "model/model.hpp"
#include <ftxui/component/event.hpp> 



namespace sc{

ftxui::Element RenderNodeColumn(){
  using namespace ftxui;
  return vbox({
    text("Star system name:"),
    separator(),
    text("Controlling corporation:"),
    text("Preferred commodities:"),
    text("System order level:"),
    text("System tech level:")
  }) |
  yflex;
}

ftxui::Element RenderNodeInfo(ent::Node& node){
  using namespace ftxui;
  return vbox({
    text(node.name),
    separator(),
    text(node.corp.name),
    text(node.pref.name),
    text(std::to_string(node.order_level)),
    text(std::to_string(node.order_level))   
  }) |
  yflex;
}

ftxui::Component RenderLaneLine(ent::Lane& lane, std::function<void()> on_click){
  using namespace ftxui;
  return Container::Horizontal({
    Renderer([&]{return hbox({
      text(lane.start.name),
      separator(),
      text(lane.end.name),
    }) |
    xflex;}),
    Button("fly", on_click)
    });
}

ftxui::Component RenderLanePanel(Model& mod){
  using namespace ftxui;
  auto lanes = mod.get_current_lanes();
  Components rendered;
  for(auto& i : lanes){
    rendered.push_back(RenderLaneLine(i, []{/*TODO answer sth*/}));
  }
  return Container::Vertical({rendered});
}

ftxui::Component RenderNodeInfoPanel(Model& mod){
  using namespace ftxui;
  auto current_node = mod.get_current_node();
  return Container::Horizontal({
    Renderer([]{return RenderNodeColumn();}),
    Renderer([&]{return RenderNodeInfo(current_node);})
  });
}

ftxui::Component RenderPanel(Model& mod){
  auto nodeinfo = RenderNodeInfoPanel(mod);
  auto lanepanel = RenderLanePanel(mod);
  int left_size = 40;
  return ftxui::ResizableSplitLeft(nodeinfo, lanepanel, &left_size);
}

class NavigationBase : public ftxui::ComponentBase{
private:
  Game& game;

  int selected_ = 0;
  int size_ = 0;
  ftxui::Box box_;
  bool Focusable() const final { return true; }

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
    NavigationBase(Game& game_):
      game(game_)
    {Add(RenderPanel(game.getModel()));}
};


ftxui::Component Navigation(Game& game) {
  return ftxui::Make<NavigationBase>(game);
}

}