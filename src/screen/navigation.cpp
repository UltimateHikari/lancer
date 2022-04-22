#include "navigation.hpp"

#include <vector>
#include <memory>
#include <iostream>

#include "model/entities.hpp"
#include "model/model.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"



namespace sc{

ftxui::Component model_time_renderer(Model& model){
    return ftxui::Renderer([&]{ 
        return ftxui::text(model.get_time()) | ftxui::border;
        });
}

//   ftxui::Component RenderLaneLine(ent::Lane& lane, std::function<void()> on_click){
//     using namespace ftxui;
//     return Container::Horizontal({
//       Renderer([&]{return hbox({
//         text(lane.start.name),
//         separator(),
//         text(lane.end.name),
//       }) |
//       xflex;}),
//       Button("fly", on_click)
//       });
//   }

// ftxui::Component RenderLanePanel(Model& mod){
//   using namespace ftxui;
//   auto lanes = mod.get_current_lanes();
//       return model_time_renderer(mod);
//   Components rendered;
//   for(auto& i : lanes){
//     rendered.push_back(RenderLaneLine(i, []{/*TODO answer sth*/}));
//   }
//   return Container::Vertical({rendered});
// }



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
  ftxui::Component lanes;
  ftxui::Element nodeinfocolumn;
  ftxui::Element nodeinfo;
  ftxui::Element nodepanel;

  NavigationBase(Game& game_){
    this->game = &game_;
  }

  ftxui::Element Render() override{
    RenderNodeInfoPanel(game->getModel());
    //return ftxui::text(game->getModel().get_time()) | ftxui::border;
    // lanes = ftxui::Container::Vertical({});
    // //lanes.get()->Add();
    
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
    //nodeinfo = RenderNodeInfo(mod.get_current_node());
    nodepanel = hflow({nodeinfocolumn});
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