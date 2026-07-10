//
// Created by Harry Skerritt on 10/07/2026.
//

#ifndef PROGRESSTRACKER_H
#define PROGRESSTRACKER_H
#include "../utils/Element.h"
#include <map>
#include <vector>

struct ProgressLog {
    bool onm_complete;
    bool am_complete;
    bool aem_complete;
    bool h_complete;
    bool ng_complete;
    bool om_complete;
    bool a_complete;
    bool ree_complete;
    bool tm_complete;
};

struct GroupStats {
    int total_elements;
    std::vector<int> collected_elements;
    bool is_complete = false;
    bool achievement_triggered = false;
};

class ProgressTracker {
public:
    ProgressTracker();

    void trackElement(int atomic_number);
    ProgressLog getProgressLog();
    bool checkJustCompleted(ElementType type);

private:
    std::map<ElementType, GroupStats> group_tracker;
};



#endif //PROGRESSTRACKER_H
