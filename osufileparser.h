#ifndef OSUFILEPARSER_H
#define OSUFILEPARSER_H

#include <QDebug>
#include <vector>
#include <QString>
#include <QStringList>

struct HitPointDetails
{
    int type;
    int x;
    int y;
    int time;
    int duration;
};


class OsuFileParser
{
    std::vector< HitPointDetails > hit_marks_;
public:
    OsuFileParser(QString file_name);
    void AddHitPoint(QString hit_point_string);
    void AddSlider(QString slider_string);
    void AddSpinner(QString spinner_string);
    void TraceVector();
private:
};

#endif // OSUFILEPARSER_H
