#include "VisualSorter.h"
#include <utility>
#include <vector>

void VisualSorter::cycle_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    const size_t len { vector.size() };

    auto& cycleStart { m_state.sortingVars.at(0) };

    // One sorting pass
    size_t itemIndex { cycleStart };
    size_t newIndex { cycleStart };

    for (size_t i = cycleStart + 1; i < len; ++i)
    {
        // Save initial state
        m_state.generatedSteps.push({ vector, {{ itemIndex, newIndex }, { i } }, { m_barColours.auxiliary, m_barColours.selected } });

        if (vector.at(i) < vector.at(itemIndex))
        {
            ++newIndex;

            // Save new state
            m_state.generatedSteps.push({ vector, {{ itemIndex, newIndex }, { i } }, { m_barColours.auxiliary, m_barColours.selected } });
        }
    }

    // Check if cycle is already complete
    if (newIndex == cycleStart)
    {
        if (cycleStart + 1 < len - 1)
            ++cycleStart;
        else
            m_state.method = none;

        return;
    }

    while (vector.at(itemIndex) == vector.at(newIndex))
    {
        // Save initial state
        m_state.generatedSteps.push({ vector, { { itemIndex }, {newIndex } }, { m_barColours.auxiliary, m_barColours.selected } });

        ++newIndex;

        // Save new state
        m_state.generatedSteps.push({ vector, { { itemIndex }, {newIndex } }, { m_barColours.auxiliary, m_barColours.selected } });
    }

    // Save initial state
    m_state.generatedSteps.push({ vector, { { itemIndex, newIndex } }, { m_barColours.selected } });

    std::swap(vector.at(newIndex), vector.at(itemIndex));

    // Save new state
    m_state.generatedSteps.push({ vector, { { itemIndex, newIndex } }, { m_barColours.actedOn } });

    // Save initial state
    m_state.generatedSteps.push({ vector, { { cycleStart, newIndex } }, { m_barColours.auxiliary } });
    while (newIndex != cycleStart)
    {
        newIndex = cycleStart;
        for (size_t i = cycleStart + 1; i < len; ++i)
        {
            // Save initial state
            m_state.generatedSteps.push({ vector, {{ itemIndex, newIndex }, { i } }, { m_barColours.auxiliary, m_barColours.selected } });

            if (vector.at(i) < vector.at(itemIndex))
            {
                ++newIndex;

                // Save new state
                m_state.generatedSteps.push({ vector, {{ itemIndex, newIndex }, { i } }, { m_barColours.auxiliary, m_barColours.selected } });
            }
        }
        if (newIndex != cycleStart)
        {
            while (vector.at(itemIndex) == vector.at(newIndex))
            {
                // Save initial state
                m_state.generatedSteps.push({ vector, { { itemIndex }, { newIndex } }, { m_barColours.auxiliary, m_barColours.selected } });

                ++newIndex;

                // Save new state
                m_state.generatedSteps.push({ vector, { { itemIndex }, { newIndex } }, { m_barColours.auxiliary, m_barColours.selected } });
            }
        }

        // Save initial state
        m_state.generatedSteps.push({ vector, { { itemIndex, newIndex } }, { m_barColours.selected } });

        std::swap(vector.at(newIndex), vector.at(itemIndex));

        // Save new state
        m_state.generatedSteps.push({ vector, { { itemIndex, newIndex } }, { m_barColours.actedOn } });
    }

    // Prepare for next step or mark as done
    if (cycleStart + 1 < len - 1)
        ++cycleStart;
    else
        m_state.method = none;
}
