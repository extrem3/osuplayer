#ifndef OSUFILEPARSER_H
#define OSUFILEPARSER_H

#include <QDebug>
#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>

struct WindowDimensions
{
    int x;
    int y;
    int width;
    int height;
};

const double kWindowWidthPercentage = 512.0;
const double kWindowHeightPercentage = 384.0;

struct HitPointDetails
{
    int type;
    double x;
    double y;
    int time;
};

class OsuFileParser
{
public:
    OsuFileParser();
    void ParseFile(QString file_name);
    void SetWindowSize(WindowDimensions osu_window_dimensions);
    std::vector<HitPointDetails> GetParsedFile();
    void TraceVector(std::vector<HitPointDetails> song);
    int GetAudioDelay();
private:
    WindowDimensions osu_window_dimensions_;
    std::vector< HitPointDetails > hit_marks_;
    int audio_in_delay_;
    void AddHitPoint(QString hit_point_string);
    void AddSlider(QString slider_string);
    void AddSpinner(QString spinner_string);
    int DetermineLineType(QString line, bool hit_points_section_found);
    int SetRelativeX(double x);
    int SetRelativeY(double y);
};

#endif // OSUFILEPARSER_H
