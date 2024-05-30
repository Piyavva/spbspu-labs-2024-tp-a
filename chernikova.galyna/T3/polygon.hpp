#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <functional>
#include <delimiter.hpp>
#include <streamGuard.hpp>

namespace chernikova
{
  struct Point
  {
    Point() : x(0), y(0)
    {}
    int x;
    int y;

    bool operator==(const Point& point) const
    {
      return x == point.x && y == point.y;
    }

    bool operator<=(const Point& point) const
    {
      return x <= point.x && y <= point.y;
    }

    bool operator>=(const Point& point) const
    {
      return x >= point.x && y >= point.y;
    }

    bool operator<(const Point& point) const
    {
      return x < point.x && y < point.y;
    }

    bool operator>(const Point& point) const
    {
      return x > point.x && y > point.y;
    }
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::ostream& operator<<(std::ostream& out, const Point& obj);
  std::ostream& operator<<(std::ostream& out, const Polygon& obj);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);

  using Predicat = bool (*) (const Polygon&);
  using ComparatorArea = double (*) (double, const Polygon&);
  using ComparatorVertexes = size_t(*) (double, const Polygon&);

  void getAreaByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat);
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getExtremumArea(const std::vector< Polygon >& polygons, std::ostream& out, ComparatorArea comparator);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getExtremumVertexes(const std::vector< Polygon >& polygons, std::ostream& out, ComparatorVertexes comparator);
  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat);
  void getCountEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);

  double calcArea(const Point& left, const Point& right);
  double getArea(const Polygon& polygon);
  double sumArea(double cur, const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isNecessaryVertex(const Polygon& polygon, size_t count);
  double chooseGreaterArea(double cur, const Polygon& polygon);
  size_t chooseGreaterVertexes(double cur, const Polygon& polygon);
  double chooseLessArea(double cur, const Polygon& polygon);
  size_t chooseLessVertexes(double cur, const Polygon& polygon);

  void echo(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void intersections(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void rightShapes(const std::vector< Polygon >& polygons, std::ostream& out);

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs);
  Polygon duplicator(std::vector< Polygon >& polygons, const Polygon& polygon, const Polygon& desiredPolygon);
  bool hasIntersection(const Polygon& lhs, const Polygon& rhs);
  bool checkRightAngle(const Polygon& polygon, size_t i);
  bool isRightAngle(const Point& p, const Polygon& polygon);
  bool hasRightAngle(const Polygon& polygon);
}

#endif