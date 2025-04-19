#include "VisualSorter.h"
#include <utility>
#include <vector>

void VisualSorter::heapsort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };

    auto& start { m_state.sortingVars.at(0) };
    auto& end { m_state.sortingVars.at(1) };

    if (end > 1)
    {
        if (start > 0)
            --start;
        else
        {
            --end;

            // Save initial state
            m_state.generatedSteps.push({ vector, {{ 0, end }}, { m_barColours.selected } });

            std::swap(vector.at(0), vector.at(end));

            // Save new state
            m_state.generatedSteps.push({ vector, {{ 0, end }}, { m_barColours.actedOn } });
        }

        for (size_t root { start }; 2 * root + 1 < end; )
        {
            size_t child { 2 * root + 1 };

            // Save current heap indexes in a vector to be highlighted later
            std::vector<size_t> heapIndexes {};
            for (size_t i = start; i < end; ++i) heapIndexes.push_back(i);

            // Save initial state
            m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_barColours.auxiliary, m_barColours.selected } });

            if (child + 1 < end && vector.at(child) < vector.at(child + 1))
                ++child;

            // Save new initial state
            m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_barColours.auxiliary, m_barColours.selected } });

            if (vector.at(root) < vector.at(child))
            {
                std::swap(vector.at(root), vector.at(child));

                // Save new state
                m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_barColours.auxiliary, m_barColours.actedOn } });

                root = child;
            }
            else
                break;
        }
    }

    // Mark if done
    if (end <= 1)
        m_state.method = none;
}
