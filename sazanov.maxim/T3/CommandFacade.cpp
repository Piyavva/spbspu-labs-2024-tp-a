#include "CommandFacade.hpp"
#include <vector>
#include <algorithm>
#include "CommandFunctors.hpp"

sazanov::CommandFacade::CommandFacade(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out) :
  polygons_(polygons),
  in_(in),
  out_(out)
{

  using namespace std::placeholders;
  commands_["AREA"] = std::bind(GetTotalPolygonsArea{getAreaSubCommands()}, polygons_, _1, _2);
  commands_["MAX"] = std::bind(GetMaxValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["MIN"] = std::bind(GetMinValue{getMaxMinSubCommands()}, polygons_, _1, _2);
}

sazanov::CommandFacade::AreaSubCommands sazanov::CommandFacade::getAreaSubCommands()
{
  AreaSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(AccumulateArea{}, _1, _2, true);
  subCommands["EVEN"] = std::bind(AccumulateArea{}, _1, _2, false);
  subCommands["MEAN"] = std::bind(AccumulateMeanArea{polygons_.size()}, _1, _2);
  return subCommands;
}

sazanov::CommandFacade::MaxMinSubCommands sazanov::CommandFacade::getMaxMinSubCommands()
{
  MaxMinSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["AREA"] = std::pair<Comparator, OutputValueFunctor>(AreaComparator{}, OutputArea{});
  subCommands["VERTEXES"] = std::pair<Comparator, OutputValueFunctor>(VertexComparator{}, OutputVertex{});
  return subCommands;
}

void sazanov::CommandFacade::nextCommand()
{
  std::string commandKey;
  std::string subCommandKey;
  std::cin >> commandKey >> subCommandKey;
  try
  {
    commands_.at(commandKey);
    CommandFunctor& command = commands_[commandKey];
    command(subCommandKey, std::cout);
  }
  catch (...)
  {
    /*
    try
    {
      AccumulateFunctor accumulateWithVertexes = AccumulateAreaWithNumOfVertexes{std::stoull(subCommandKey)};
      CommandFunctor& command = commands_[commandKey];
      command(polygons_, &accumulateWithVertexes, std::cout);

    }
     */
    throw std::exception();
  }
}
