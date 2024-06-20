#include "simulation.h"
#include <algorithm>
#include <conio.h>

namespace stochastic {
    [[maybe_unused]] void showDelays(const std::vector<reaction>& R){
        std::cout << "Delays: ";
        for (const auto &r : R) {
            std::cout << r.delay << " ";
        }
        std::cout << std::endl;
    }

    void simulation::run(const int T) {
        bool fullRun = false;

        t = 0;
        while (t <= T) {
            auto R = vessel.getReactions();
//            showDelays(R);
            for(auto &r : R)  r.update(vessel.getTable());
            auto r = std::min_element(std::begin(R), std::end(R), [](const auto &a, const auto &b) { return a.delay < b.delay; });

            t += r->delay;

            if (std::all_of(std::begin(r->input), std::end(r->input), [this](const auto& reactor){ return vessel.getTableValue(reactor->name) > 0; })){
                for (auto &reactor: r->input)  vessel.setTableIncrease(reactor->name, -1);
                for (auto &reactor: r->product)  vessel.setTableIncrease(reactor->name, +1);
            }

            if (vessel.getTableRecordHistory()) vessel.addTableHistory(t);
            // shows state + user actions
            if (!fullRun) {
                std::cout << "time " << t << r->show() << std::endl;
                vessel.showTable();
                char ch = _getch();
                if (ch == 'q') break;
                else if (ch == 'g') fullRun = true;
            }
            else
                std::cout << "time " << t << r->show() << std::endl;
        }
    }

    template<typename Observer>
    void simulation::run(double T, Observer& observer) {
        bool fullRun = false;

        t = 0;
        while (t <= T) {
            auto R = vessel.getReactions();
//            showDelays(R);
            for(auto &r : R)  r.update(vessel.getTable());
            auto r = std::min_element(std::begin(R), std::end(R), [](const auto &a, const auto &b) { return a.delay < b.delay; });

            t += r->delay;

            if (std::all_of(std::begin(r->input), std::end(r->input), [this](const auto& reactor){ return vessel.getTableValue(reactor->name) > 0; })){
                for (auto &reactor: r->input)  vessel.setTableIncrease(reactor->name, -1);
                for (auto &reactor: r->product)  vessel.setTableIncrease(reactor->name, +1);
            }

            //show states + observer
            if (!fullRun) {
                std::cout << "time " << t << r->show() << std::endl;
                vessel.showTable();
                char ch = _getch();
                if (ch == 'q') break;
                else if (ch == 'g') fullRun = true;
            }
            else
                std::cout << "time " << t << r->show() << std::endl;

            observer(vessel);
        }
    }

    void simulation::runNoPrint(int T) {
        t = 0;
        while (t <= T) {
            auto R = vessel.getReactions();
//            showDelays(R);
            for(auto &r : R)  r.update(vessel.getTable());
            auto r = std::min_element(std::begin(R), std::end(R), [](const auto &a, const auto &b) { return a.delay < b.delay; });

            t += r->delay;

            if (std::all_of(std::begin(r->input), std::end(r->input), [this](const auto& reactor){ return vessel.getTableValue(reactor->name) > 0; })){
                for (auto &reactor: r->input)  vessel.setTableIncrease(reactor->name, -1);
                for (auto &reactor: r->product)  vessel.setTableIncrease(reactor->name, +1);
            }
        }
    }

    template<typename Observer>
    void simulation::runNoPrint(double T, Observer& observer) {
        t = 0;
        while (t <= T) {
            auto R = vessel.getReactions();
//            showDelays(R);
            for(auto &r : R)  r.update(vessel.getTable());
            auto r = std::min_element(std::begin(R), std::end(R), [](const auto &a, const auto &b) { return a.delay < b.delay; });

            t += r->delay;

            if (std::all_of(std::begin(r->input), std::end(r->input), [this](const auto& reactor){ return vessel.getTableValue(reactor->name) > 0; })){
                for (auto &reactor: r->input)  vessel.setTableIncrease(reactor->name, -1);
                for (auto &reactor: r->product)  vessel.setTableIncrease(reactor->name, +1);
            }
            observer(vessel);
        }
    }
}