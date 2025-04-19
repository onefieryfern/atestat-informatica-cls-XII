#include "VisualSorter.h"
#include <stack>
#include <utility>
#include <vector>

void VisualSorter::quicksort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    auto& pseudoStack { m_state.sortingVars };

    struct Partition
    {
        size_t lo;
        size_t hi;
    };

    // Get stack from the pseudo-stack
    std::stack<Partition> stack {};
    while (!pseudoStack.empty())
    {
        Partition part {};
        part.lo = pseudoStack.back(); pseudoStack.pop_back();
        part.hi = pseudoStack.back(); pseudoStack.pop_back();

        stack.push(part);
    }

    // One sorting pass
    if (!stack.empty())
    {
        const size_t lo { stack.top().lo };
        const size_t hi { stack.top().hi };
        stack.pop();

        std::vector<size_t> workingIndexes {};
        for (size_t i = lo; i <= hi; ++i) workingIndexes.push_back(i);

        // Subpartition the current partition
        size_t iPivot {};
        {
            const int pivot = vector.at(hi);
            size_t iNewPivot { lo };

            for (size_t j = lo; j < hi; ++j)
            {
                // Save initial state
                m_state.generatedSteps.push({ vector, { workingIndexes, { iNewPivot, j, hi } }, { m_barColours.auxiliary, m_barColours.selected } });

                if (vector.at(j) <= pivot)
                {
                    std::swap(vector.at(iNewPivot), vector.at(j));
                    ++iNewPivot;

                    // Save new state
                    m_state.generatedSteps.push({ vector, { workingIndexes, { iNewPivot, j }, { hi } }, { m_barColours.auxiliary, m_barColours.actedOn, m_barColours.selected } });
                }
            }

            // Save initial state
            m_state.generatedSteps.push({ vector, { workingIndexes, { iNewPivot, hi } }, { m_barColours.auxiliary, m_barColours.selected } });

            std::swap(vector.at(iNewPivot), vector.at(hi));

            // Save new state
            m_state.generatedSteps.push({ vector, { workingIndexes, { iNewPivot, hi } }, { m_barColours.auxiliary, m_barColours.actedOn } });

            iPivot = iNewPivot;
        }

        if (iPivot != 0 && iPivot - 1 > lo)
            stack.push({ lo, iPivot - 1 });
        if (iPivot + 1 < hi)
            stack.push({ iPivot + 1, hi });
    }

    // Mark as done
    if (stack.empty())
        m_state.method = none;

    // Save current stack in the persistent pseudo-stack
    while (!stack.empty())
    {
        pseudoStack.push_back(stack.top().hi);
        pseudoStack.push_back(stack.top().lo);

        stack.pop();
    }
}
