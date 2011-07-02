#include "osufileparser.h"

OsuFileParser::OsuFileParser(QString file_name)
{

}

void OsuFileParser::AddSpinner(QString spinner_string)
{
    // array indicates:
    //   [0]: it's a spinner (= 4)
    //   [1]: initialization time
    //   [2]: x
    //   [3]: y
}

void OsuFileParser::AddSlider(QString slider_string)
{
    // array indicates:
    //   [0]: it's a slider (= 2)
    //   [1]: initialization time
    //   [2]: x
    //   [3]: y
    // slider then calls MousePress, until you hit [0] = 3
    //   and then it calls MouseRelease
    // until then, arrays are structured as:
    //   [0]: it's a slider continuation (= 0)
    //   [1]: when to hover it
    //   [2]: x
    //   [3]: y
}

void OsuFileParser::AddHitPoint(QString hit_point_string)
{
    // array indicates:
    //   [0]: it's a hit point (= 1)
    //   [1]: initialization time
    //   [2]: x
    //   [3]: y

    int hit_points[] = { 1, 2, 3, 4};
    std::vector<int> hit_positions(hit_points, hit_points + sizeof(hit_points) / sizeof(hit_points[0]));
    hit_marks_.push_back(hit_positions);
}
