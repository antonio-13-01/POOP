#include "RouteFactory.h"
#include "DatabaseManager.h"
#include <iostream>

std::vector<Route*> RouteFactory::LoadAllRoutes() {
    auto& db = DatabaseManager::getInstance();


    struct RawRoute { int id; std::string name; int dir; };
    std::vector<RawRoute> tempBuffer;

    {
        auto result = db.executeQuery("SELECT route_id, route_name, route_direction FROM Route");
        while (result.next()) {
            tempBuffer.push_back({
                result.get<int>(0),
                result.get<std::string>(1),
                result.get<int>(2)
                });
        }
    }

    std::vector<Route*> routes;
    for (const auto& data : tempBuffer) {
        Route* newRoute = new Route(data.id, data.name, data.dir);

        
        LoadStopsForRoute(data.id, newRoute);

        routes.push_back(newRoute);
    }
    return routes;
}

void RouteFactory::LoadStopsForRoute(int route_id, Route* route) {
    auto& db = DatabaseManager::getInstance();
    nanodbc::statement stmt(db.getConnection());

   
    nanodbc::prepare(stmt, "SELECT stop_info_id, station_id, arrival_minutes, departure_minutes "
        "FROM StopInfo WHERE route_id = ? ORDER BY arrival_minutes ASC");

    stmt.bind(0, &route_id);
    auto result = nanodbc::execute(stmt);

    while (result.next()) {
        StopInfo* stop = new StopInfo(
            result.get<int>(0), // stop_info_id
            route_id,           // route_id
            result.get<int>(1), // station_id
            result.get<int>(2), // arrival_minutes
            result.get<int>(3)  // departure_minutes
        );
        route->addStop(stop);
    }
}
Route* RouteFactory::LoadRouteFromDB(int route_id) {
    auto& db = DatabaseManager::getInstance();

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt, "SELECT route_name, route_direction FROM Route WHERE route_id = ?");
    stmt.bind(0, &route_id);

    auto result = nanodbc::execute(stmt);
    if (result.next()) {
        std::string name = result.get<std::string>(0);
        int direction = result.get<int>(1);

        Route* route = new Route(route_id, name, direction);
        LoadStopsForRoute(route_id, route);
        return route;
    }
    return nullptr;
}