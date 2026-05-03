#include "Route.h"
#include "StopInfo.h"
#include <vector>
#include <string>

class RouteFactory {
public:
    // Încarcă toate rutele disponibile în sistem
    static std::vector<Route*> LoadAllRoutes();


    // Încarcă o rută specifică după ID
    static Route* LoadRouteFromDB(int route_id);

private:
    // Helper pentru a încărca punctele de oprire (StopInfo) pentru o rută
    static void LoadStopsForRoute(int route_id, Route* route);
};