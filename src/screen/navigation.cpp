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
  ftxui::Element nodeinfocolumn;
  ftxui::Element nodeinfo;
  ftxui::Element nodepanel;

  NavigationBase(Game& game_){
    router = ftxui::Container::Vertical({});
    Add(router);
    this->game = &game_;
  }

  ftxui::Element Render() override{
    RenderLanePanel(game->getModel());
    RenderNodeInfoPanel(game->getModel());
    return nodepanel;
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
      text(node.name + " (" + std::to_string(node.id) + ")"), //TODO - for debug purpose
      separator(),
      text(node.corp.name),
      text(node.pref.name),
      text(std::to_string(node.order_level)),
      text(std::to_string(node.tech_level))   
    }) |
    yflex;
  }

  void RenderNodeInfoPanel(Model& mod){
    using namespace ftxui;
    nodeinfocolumn = RenderNodeColumn();
    nodeinfo = RenderNodeInfo(mod.get_current_node());
    nodepanel = hbox({hflow({nodeinfocolumn, nodeinfo}), router->Render()}) | border | yflex;
  }  

  ftxui::Component RenderLaneLine(const ent::Lane& lane, std::function<void()> on_click){
    using namespace ftxui;
    return Container::Horizontal({
        Button("Depart", [&]{game->getModel().move_with_lane(lane);}),
        Renderer([&]{return filler();}),
        
        Renderer([&]{
          return text(lane.getContextedText(game->getModel().get_current_node())) | center;
        }),
      });
  }

  void RenderLanePanel(Model& mod){
    using namespace ftxui;
    const std::vector<ent::Lane>& entities = mod.get_current_lanes();
    router->DetachAllChildren();
    for(const ent::Lane& i : entities){
      router->Add(RenderLaneLine(i, []{}));
    }
  }

};

ftxui::Component Navigation(Game& game) {
  return ftxui::Make<NavigationBase>(game);

}

}