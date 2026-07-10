//
// Created by Harry Skerritt on 10/07/2026.
//

#include "ProgressTracker.h"

#include "../UI/Achievement/AchievementManager.h"

ProgressTracker::ProgressTracker() {
    group_tracker[ElementType::OTHER_NON_METAL]    = { 11, {}, false };
    group_tracker[ElementType::ALKALI_METAL]       = { 6, {}, false };
    group_tracker[ElementType::ALKALI_EARTH_METAL] = { 6, {}, false };
    group_tracker[ElementType::HALOGEN]            = { 6, {}, false };
    group_tracker[ElementType::NOBLE_GAS]          = { 7, {}, false };
    group_tracker[ElementType::OTHER_METAL]        = { 14, {}, false };
    group_tracker[ElementType::ACTINOID]           = { 15, {}, false };
    group_tracker[ElementType::LANTHANIDE]         = { 17, {}, false };
    group_tracker[ElementType::TRANSITION_METAL]   = { 36, {}, false };
}


void ProgressTracker::trackElement(int atomic_number) {
    Element e = PeriodicTable[atomic_number];
    ElementType type = e.type;

    if (group_tracker.find(type) != group_tracker.end()) {
        auto& stats = group_tracker[type];

        auto it = std::find(stats.collected_elements.begin(), stats.collected_elements.end(), atomic_number);
        if (it == stats.collected_elements.end()) {
            stats.collected_elements.push_back(atomic_number);
        }

        if (!stats.is_complete && stats.collected_elements.size() >= stats.total_elements) {
            stats.is_complete = true;
        }
    }
}

bool ProgressTracker::checkJustCompleted(const ElementType type) {
    auto& stats = group_tracker[type];

    if (stats.is_complete && !stats.achievement_triggered) {
        stats.achievement_triggered = true;
        return true;
    }
    return false;
}

ProgressLog ProgressTracker::getProgressLog() {
    ProgressLog progress;
    progress.onm_complete = group_tracker[ElementType::OTHER_NON_METAL].is_complete;
    progress.am_complete = group_tracker[ElementType::ALKALI_METAL].is_complete;
    progress.aem_complete = group_tracker[ElementType::ALKALI_EARTH_METAL].is_complete;
    progress.h_complete = group_tracker[ElementType::HALOGEN].is_complete;
    progress.ng_complete = group_tracker[ElementType::NOBLE_GAS].is_complete;
    progress.om_complete = group_tracker[ElementType::OTHER_METAL].is_complete;
    progress.a_complete = group_tracker[ElementType::ACTINOID].is_complete;
    progress.ree_complete = group_tracker[ElementType::LANTHANIDE].is_complete;
    progress.tm_complete = group_tracker[ElementType::TRANSITION_METAL].is_complete;

    return progress;
}
