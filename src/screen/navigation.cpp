#include "navigation.hpp"

#include <vector>
#include <memory>
#include <iostream>

#include "model/entities.hpp"
#include "model/model.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"



namespace sc{

ftxui::Component model_time_renderer(Model& model){
    return ftxui::Renderer([&]{ 
        return ftxui::text(model.get_time()) | ftxui::border;
        });
}


// ftxui::Component RenderPanel(Model& mod){
//   using namespace ftxui;
//   auto nodeinfo = RenderNodeInfoPanel(mod);
//       auto logo = Renderer([] {return text("logo") | center;});
//   //auto lanepanel = RenderLanePanel(mod);
//   int left_size = 40;
//   return Container::Horizontal({std::move(logo), Renderer([] { return separator(); }),/*lanepanel*/std::move(nodeinfo)});
// }

class NavigationBase : public ftxui::ComponentBase{
public:
  Game* game;
  ftxui::Component router;
  ftxui::Component button = ftxui::Button("testbutton", []{}, ftxui::ButtonOption());
  ftxui::Element nodeinfocolumn;
  ftxui::Element nodeinfo;
  ftxui::Element nodepanel;
  std::string depart = "depart";

  NavigationBase(Game& game_){
    router = ftxui::Container::Vertical({});
    this->game = &game_;
  }

  ftxui::Element Render() override{
    DetachAllChildren();
    RenderLanePanel(game->getModel());
        router.get()->Add(button);

    Add(router);
    RenderNodeInfoPanel(game->getModel());
    return nodepanel | ftxui::border;
  }

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

  ftxui::Element RenderNodeInfo(const ent::Node& node){
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

  void RenderNodeInfoPanel(Model& mod){
    using namespace ftxui;
    nodeinfocolumn = RenderNodeColumn();
    nodeinfo = RenderNodeInfo(mod.get_current_node());
    nodepanel = hflow({nodeinfocolumn, nodeinfo, router.get()->Render() | borderDouble}) | border | yflex;
  }  

  ftxui::Component RenderLaneLine(const ent::Lane& lane, std::function<void()> on_click){
    using namespace ftxui;
    return Container::Horizontal({
        Button(depart, [&]{game->getModel().move_with_lane(lane); depart = "act";}),
        Renderer([&]{return filler();}),
        
        Renderer([&]{
          return text(lane.start.name + " to " + lane.end.name) | center;
        }),
      });
  }

  void RenderLanePanel(Model& mod){
    using namespace ftxui;
    const std::vector<ent::Lane>& entities = mod.get_current_lanes();
    router.get()->DetachAllChildren();
    for(const ent::Lane& i : entities){
      router.get()->Add(RenderLaneLine(i, []{}));
    }
  }

};

// class NavigationBase : public ftxui::ComponentBase{
// private:
//   Game& game;

//   int selected_ = 0;
//   int size_ = 0;
//   ftxui::Box box_;
//   bool Focusable() const final { return true; }

// public:
//   ftxui::Element Render() final{
//     using namespace ftxui;
//     auto focused = Focused() ? focus : ftxui::select;
//     auto style = Focused() ? inverted : nothing;

//     ftxui::Element background = ComponentBase::Render();
//     background->ComputeRequirement();
//     size_ = background->requirement().min_y;
//     return dbox({
//             std::move(background),
//             vbox({
//                 text(L"") | size(HEIGHT, EQUAL, selected_),
//                 text(L"") | style | focused,
//             }),
//         }) |
//         vscroll_indicator | yframe | yflex | reflect(box_);
//     }
//     NavigationBase(Game& game_):
//       game(game_)
//     {Add(RenderPanel(game.getModel()));}
// };


ftxui::Component Navigation(Game& game) {
  return ftxui::Make<NavigationBase>(game);
  // /return RenderPanel(game.getModel());
  //return fxtui::Renderer([&]{return });
}

}